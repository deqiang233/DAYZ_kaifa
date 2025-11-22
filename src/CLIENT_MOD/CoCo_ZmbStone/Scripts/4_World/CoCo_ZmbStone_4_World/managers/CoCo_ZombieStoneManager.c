class CoCo_ZombieStoneManager
{
	ZombieBase m_ZombieBase;
	private DayZInfectedInputController zombieBaseInputController;
	
	bool isThrowingStone;
	vector zombiePosition;
	vector zombieDirection;
	vector previousPos;
	
	private int mindState;
	
	void CoCo_ZombieStoneManager()
	{
		if (GetGame().IsDedicatedServer())
		{
			// 确保配置已加载
			CoCo_ZmbStone_Config.LoadConfig();
			
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetTheInputController, 10, false);
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckThrowStone, 1000, false);
		}
	}
	
	private void GetTheInputController()
	{
		if (m_ZombieBase)
			zombieBaseInputController = m_ZombieBase.GetInputController();
	}
	
	void CheckThrowStone()
	{
		if (m_ZombieBase && m_ZombieBase.IsAlive() && !IsCrawler())
		{
			if (CoCo_ZmbStone_Config.Enabled == 1 && CanThrowStones() && m_ZombieBase.m_ActualTarget)
			{
				mindState = m_ZombieBase.GetMindStateSynced();
				if (mindState >= 2) // CHASE or FIGHT state
				{
					vector targetPosition = m_ZombieBase.m_ActualTarget.GetPosition();
					zombiePosition = m_ZombieBase.GetPosition();
					float targetDistSq = vector.DistanceSq(targetPosition, zombiePosition);
					
					if (targetDistSq > CoCo_ZmbStone_Config.ThrowDistanceMin * CoCo_ZmbStone_Config.ThrowDistanceMin && targetDistSq < CoCo_ZmbStone_Config.ThrowDistanceMax * CoCo_ZmbStone_Config.ThrowDistanceMax && !PlayerIsInCar(m_ZombieBase.m_ActualTarget))
					{
						vector zombiePositionAdjust = zombiePosition;
						zombiePositionAdjust[1] = zombiePositionAdjust[1] + 0.3;
						
						vector targetPositionAdjust = targetPosition;
						targetPositionAdjust[1] = targetPositionAdjust[1] + 0.7;
						
						if (!RaycastPlayer(zombiePositionAdjust, targetPositionAdjust) && FacingTheTarget(targetPosition, CoCo_ZmbStone_Config.ThrowDistanceMax))
						{
							if (CoCo_ZmbStone_Config.OnlyIfPlayerOnObstacle == 0 || PlayerIsOnObstacle(targetPosition))
							{
								isThrowingStone = true;
								previousPos = zombiePosition;
								TriggerStoneAttackAnimation();
								GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnStone, 500, false);
								GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FinishThrowingStone, 1000, false);
							}
						}
					}
				}
			}
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckThrowStone, CoCo_ZmbStone_Config.ThrowRate * 1000 + Math.RandomFloatInclusive(0, 1000), false);
		}
	}
	
	void FinishThrowingStone()
	{
		isThrowingStone = false;
	}
	
	bool IsCrawler()
	{
		// 检查僵尸是否是爬行状态
		if (m_ZombieBase)
		{
			return m_ZombieBase.IsCrawling();
		}
		return false;
	}
	
	bool CanThrowStones()
	{
		// 可以通过配置文件或僵尸类型判断
		return CoCo_ZmbStone_Config.DefaultZombieCanThrow >= 1;
	}
	
	bool PlayerIsInCar(EntityAI theZombieTarget)
	{
		if (theZombieTarget)
		{
			PlayerBase thePlayerBase = PlayerBase.Cast(theZombieTarget);
			if(thePlayerBase && thePlayerBase.IsInVehicle())
			{
				return true;
			}
			if(theZombieTarget.IsTransport())
			{
				Transport theTransport = Transport.Cast(theZombieTarget);
				if (theTransport)
				{
					for (int i = 0; i < theTransport.CrewSize(); ++i)
					{
						if (theTransport.CrewMember(i))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	
	bool PlayerIsOnObstacle(vector targetPosition)
	{
		if (targetPosition[1] > zombiePosition[1])
		{
			float targetGroundHeigth = GetGame().SurfaceY(targetPosition[0], targetPosition[2]);
			if (targetPosition[1] > targetGroundHeigth + 0.8)
			{
				return true;
			}
		}
		return false;
	}
	
	void TriggerStoneAttackAnimation()
	{
		int attackType = Math.RandomIntInclusive(0, 1);
		m_ZombieBase.m_ActualAttackType = m_ZombieBase.GetDayZInfectedType().ChooseAttack(DayZInfectedAttackGroupType.FIGHT, 0, 0);
		DayZInfectedCommandAttack dayZInfectedCommandAttackTest = m_ZombieBase.StartCommand_Attack(NULL, attackType, 1);
		
		PlayerBase thePlayerBase = PlayerBase.Cast(m_ZombieBase.m_ActualTarget);
		if (thePlayerBase)
		{
			CoCo_PlayerStoneHandler handler = GetPlayerStoneHandler(thePlayerBase);
			if (handler)
			{
				handler.isTargetByStones++;
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(handler.UpdateIsTargetByStone, 2000, false);
			}
		}
	}
	
	CoCo_PlayerStoneHandler GetPlayerStoneHandler(PlayerBase player)
	{
		if (!player)
			return null;
			
		// 获取或创建PlayerStoneHandler
		return player.GetCoCo_PlayerStoneHandler();
	}
	
	string nameOfStone = "CoCo_ThrownStone";
	EntityAI theObjectToThrow;
	void SpawnStone()
	{
		zombieDirection = m_ZombieBase.GetDirection();
		zombiePosition = m_ZombieBase.GetPosition();
		
		vector StonePosition = SetStonePosition();
		theObjectToThrow = EntityAI.Cast(GetGame().CreateObject(nameOfStone, StonePosition, false, false));
		CoCo_ThrownStone theStone = CoCo_ThrownStone.Cast(theObjectToThrow);
		if (theStone)
		{
			theStone.coco_IsThrowStone = true;
			
			// 根据僵尸类型获取伤害值并设置到石头上
			string zombieType = m_ZombieBase.GetType();
			array<float> damage = CoCo_ZmbStone_Config.GetDamageForZombie(zombieType);
			if (damage.Count() >= 3)
			{
				theStone.coco_DamageHealth = damage[0];
				theStone.coco_DamageShock = damage[1];
				theStone.coco_KeepMinimumHealth = damage[2];
			}
			
			theStone.coco_BleedChance = CoCo_ZmbStone_Config.GetBleedChanceForZombie(zombieType);
		}
		if (theObjectToThrow)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ApplyForce, 100, false, theObjectToThrow);
		}
	}
	
	vector SetStonePosition()
	{
		vector StonePosition = zombiePosition;
		StonePosition[1] = StonePosition[1] + 1.8; // 僵尸头部高度
		StonePosition = StonePosition + (zombieDirection * 0.2);
		return StonePosition;
	}
	
	void ApplyForce(EntityAI theStone)
	{
		vector force;
		if (m_ZombieBase.m_ActualTarget)
		{
			vector tagetPos = m_ZombieBase.m_ActualTarget.GetPosition() + "0 1.7 0";
			force = ((tagetPos - theStone.GetPosition()).Normalized()) * CoCo_ZmbStone_Config.ThrowForce;
		}
		else
		{
			force = zombieDirection * CoCo_ZmbStone_Config.ThrowForce;
		}
		force[1] = force[1] + CoCo_ZmbStone_Config.ThrowForce * 0.04; // 添加向上的力
		
		InventoryItem theStoneInv = InventoryItem.Cast(theStone);
		if (theStoneInv)
		{
			theStoneInv.ThrowPhysically(NULL, force);
		}
	}
	
	private bool FacingTheTarget(vector targetPosition, float maxDistance)
	{
		zombiePosition = m_ZombieBase.GetPosition();
		float targetDistSq = vector.DistanceSq(targetPosition, zombiePosition);
		float maxDistanceToTargetSq = maxDistance * maxDistance;
		
		if (targetDistSq < maxDistanceToTargetSq)
		{
			zombieDirection = m_ZombieBase.GetDirection();
			vector inFrontOfZombie = zombiePosition + zombieDirection * maxDistance;
			float distFrontOfZombieToPlayerSq = vector.DistanceSq(inFrontOfZombie, targetPosition);
			
			if (distFrontOfZombieToPlayerSq < maxDistanceToTargetSq)
			{
				return true;
			}
		}
		return false;
	}
	
	private bool RaycastPlayer(vector zombiePosition2, vector playerPosition)
	{
		vector decalZombieHeight = "0 1.5 0";
		vector decalPlayerHeight = "0 1.0 0";
		zombiePosition2 += decalZombieHeight;
		playerPosition += decalPlayerHeight;
		
		float hitFraction;
		vector hitPosition, hitNormal;
		Object hitObject;
		int contactComponent;
		
		PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.BUILDING|PhxInteractionLayers.DOOR|PhxInteractionLayers.VEHICLE|PhxInteractionLayers.ITEM_LARGE|PhxInteractionLayers.FENCE;
		
		bool hit = DayZPhysics.RayCastBullet(zombiePosition2, playerPosition, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction);
		return hit;
	}
	
	void EOnPostFrame(IEntity other, int extra)
	{
		if (m_ZombieBase && m_ZombieBase.IsAlive() && isThrowingStone == true)
		{
			if (previousPos != vector.Zero)
			{
				if (!zombieBaseInputController)
					GetTheInputController();
				if (zombieBaseInputController)
				{
					float zedVel2 = zombieBaseInputController.GetMovementSpeed();
					if (zedVel2 <= 1.8)
						m_ZombieBase.SetPosition(previousPos);
				}
			}
		}
	}
}

