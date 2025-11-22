class FreezeFurnace_Kit extends ItemBase
{
	ref protected EffectSound m_DeployLoopSound;

	override void EEInit()
	{
		super.EEInit();
	}

	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner) 
	{
		super.OnItemLocationChanged(old_owner, new_owner);
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (IsDeploySound())
		{
			PlayDeploySound();
		}

		if (CanPlayDeployLoopSound())
		{
			PlayDeployLoopSound();
		}

		if (m_DeployLoopSound && !CanPlayDeployLoopSound())
		{
			StopDeployLoopSound();
		}
	}


	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}

	//================================================================
	// ADVANCED PLACEMENT
	//================================================================

	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		super.OnPlacementComplete(player, position, orientation);
		
		if (GetGame().IsServer())
		{
			EntityAI kitItem = EntityAI.Cast(GetGame().CreateObjectEx("FreezeFurnace", position, ECE_PLACE_ON_SURFACE));
			kitItem.SetPosition(position);
			kitItem.SetOrientation(orientation);
		}

		SetIsPlaceSound(true);
	}

	override bool IsDeployable()
	{
		return true;
	}

	override string GetDeploySoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}

	override string GetLoopDeploySoundset()
	{
		return "BarbedWire_Deploy_loop_SoundSet";
	}

	void PlayDeployLoopSound()
	{
		if (!GetGame().IsDedicatedServer())
		{
			m_DeployLoopSound = SEffectManager.PlaySound(GetLoopDeploySoundset(), GetPosition());
		}
	}

	void StopDeployLoopSound()
	{
		if (!GetGame().IsDedicatedServer() && m_DeployLoopSound)
		{
			m_DeployLoopSound.SoundStop();
			delete m_DeployLoopSound;
		}
	}
}

