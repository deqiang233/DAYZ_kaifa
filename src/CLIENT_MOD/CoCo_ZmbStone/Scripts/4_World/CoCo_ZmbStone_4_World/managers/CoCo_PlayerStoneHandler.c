class BleedingSourcesManagerBase;

class CoCo_PlayerStoneHandler
{
	PlayerBase m_PlayerBase;
	int isTargetByStones;
	protected static ref array<string> s_BleedingSelections;
	
	void CoCo_PlayerStoneHandler()
	{
		isTargetByStones = 0;
	}
	
	void UpdateIsTargetByStone()
	{
		isTargetByStones--;
		if (isTargetByStones < 0)
			isTargetByStones = 0;
	}
	
	void OnStoneHit(EntityAI stone)
	{
		if (!m_PlayerBase || !m_PlayerBase.IsAlive())
			return;
			
		CoCo_ThrownStone theStone = CoCo_ThrownStone.Cast(stone);
		if (theStone && theStone.coco_IsThrowStone == true)
		{
			theStone.coco_IsThrowStone = false;
			isTargetByStones = 0;
			
			// 从石头对象读取伤害值，如果未设置（-1）则使用默认配置
			float damageHealth = theStone.coco_DamageHealth;
			float damageShock = theStone.coco_DamageShock;
			float keepMinimumHealth = theStone.coco_KeepMinimumHealth;
			float bleedChance = theStone.coco_BleedChance;
			
			// 如果伤害值未设置（为-1），使用默认配置
			if (damageHealth < 0)
				damageHealth = CoCo_ZmbStone_Config.DamageHealth;
			if (damageShock < 0)
				damageShock = CoCo_ZmbStone_Config.DamageShock;
			if (keepMinimumHealth < 0)
				keepMinimumHealth = CoCo_ZmbStone_Config.KeepMinimumHealth;
			if (bleedChance < 0)
				bleedChance = CoCo_ZmbStone_Config.BleedChance;
			
			// 应用伤害
			float currentShock = m_PlayerBase.GetHealth("", "Shock");
			float newShock = currentShock - damageShock;
			if (newShock < 0)
				newShock = 0;
			m_PlayerBase.SetHealth("", "Shock", newShock);
			
			float currentHealth = m_PlayerBase.GetHealth();
			float newHealth = currentHealth - damageHealth;
			if (newHealth < keepMinimumHealth)
				newHealth = Math.Min(keepMinimumHealth, currentHealth);
			m_PlayerBase.SetHealth(newHealth);
			
			TryApplyBleeding(bleedChance);
		}
	}
	
	protected void TryApplyBleeding(float bleedChance)
	{
		if (bleedChance <= 0)
			return;
		
		float roll = Math.RandomFloatInclusive(0.0, 1.0);
		if (roll > bleedChance)
			return;
		
		BleedingSourcesManagerBase bleedingManager = m_PlayerBase.GetBleedingManagerServer();
		if (!bleedingManager)
			return;
		
		string selection = GetRandomBleedingSelection();
		if (selection == "")
			return;
		
		bleedingManager.AttemptAddBleedingSourceBySelection(selection);
	}
	
	protected static string GetRandomBleedingSelection()
	{
		EnsureBleedingSelections();
		
		if (!s_BleedingSelections || s_BleedingSelections.Count() == 0)
			return "";
		
		int index = Math.RandomInt(0, s_BleedingSelections.Count());
		return s_BleedingSelections.Get(index);
	}
	
	protected static void EnsureBleedingSelections()
	{
		if (s_BleedingSelections)
			return;
		
		s_BleedingSelections = new array<string>();
		s_BleedingSelections.Insert("RightToeBase");
		s_BleedingSelections.Insert("RightFoot");
		s_BleedingSelections.Insert("LeftToeBase");
		s_BleedingSelections.Insert("LeftFoot");
		s_BleedingSelections.Insert("RightUpLegRoll");
		s_BleedingSelections.Insert("RightUpLeg");
		s_BleedingSelections.Insert("RightLegRoll");
		s_BleedingSelections.Insert("RightLeg");
		s_BleedingSelections.Insert("LeftUpLegRoll");
		s_BleedingSelections.Insert("LeftUpLeg");
		s_BleedingSelections.Insert("LeftLegRoll");
		s_BleedingSelections.Insert("LeftLeg");
		s_BleedingSelections.Insert("RightForeArmRoll");
		s_BleedingSelections.Insert("LeftForeArmRoll");
		s_BleedingSelections.Insert("RightForeArm");
		s_BleedingSelections.Insert("RightArmRoll");
		s_BleedingSelections.Insert("RightArm");
		s_BleedingSelections.Insert("RightShoulder");
		s_BleedingSelections.Insert("LeftForeArm");
		s_BleedingSelections.Insert("LeftArmRoll");
		s_BleedingSelections.Insert("LeftArm");
		s_BleedingSelections.Insert("LeftShoulder");
		s_BleedingSelections.Insert("Spine3");
		s_BleedingSelections.Insert("Spine2");
		s_BleedingSelections.Insert("Spine1");
		s_BleedingSelections.Insert("Spine");
		s_BleedingSelections.Insert("RightHand");
		s_BleedingSelections.Insert("LeftHand");
	}
}

