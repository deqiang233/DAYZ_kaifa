class FreezeFurnace extends ItemBase
{
    private bool m_FurnaceState = false; // Tracks if the furnace is on or off
    ref protected Effect m_Smoke;       // Smoke effect
    ref protected EffectSound m_SoundLoop; // Looping sound effect

	void FreezeFurnace()
	{
		RegisterNetSyncVariableBool("m_FurnaceState");
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (GetGame().IsDedicatedServer())
		{
			return;
		}

		if (m_FurnaceState)
		{
			StartLoopSound();
			StartParticleEffect();
		}
		else
		{
			StopLoopSound();
			StopParticleEffect();
		}
	}

    void ~FreezeFurnace()
    {
        if (m_SoundLoop)
        {
            m_SoundLoop.SoundStop();
            delete m_SoundLoop;
        }

        if (m_Smoke)
        {
            delete m_Smoke;
        }
    }
	void StartLoopSound()
	{
		if (GetGame().IsDedicatedServer())
		{
			return;
		}

		if (!m_SoundLoop)
		{
			m_SoundLoop = SEffectManager.PlaySound("FreezeFurnace_On_SoundSet", GetPosition(), 0.0, 0.0, true);

			if (m_SoundLoop)
			{
				m_SoundLoop.SetAutodestroy(false);
			}
		}
	}

	void Stop()
	{
		if (m_SoundLoop) {
			m_SoundLoop.Stop();
			m_SoundLoop = null;
		}
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).RemoveByName(this, "ProcessAndCraftBars"); 
	}

    void StopLoopSound()
    {
        if (GetGame().IsDedicatedServer())
        {
            return;
        }

        if (m_SoundLoop)
        {
            m_SoundLoop.SoundStop();
            delete m_SoundLoop;
            m_SoundLoop = null;
        }
    }

    void StartParticleEffect()
    {
        if (GetGame().IsDedicatedServer())
        {
            return;
        }

        if (!m_Smoke)
        {
            vector local_pos = "0.3 1.8 0.4";  // Y value doubled to 1.7-1.8 to move smoke higher for chimney
            vector local_ori = "270 0 0";
            m_Smoke = new EffGeneratorSmoke();
            SEffectManager.PlayOnObject(m_Smoke, this, local_pos, local_ori);
        }
    }

    void StopParticleEffect()
    {
        if (GetGame().IsDedicatedServer())
        {
            return;
        }

        if (m_Smoke)
        {
            delete m_Smoke;
            m_Smoke = null;
        }
    }
    void SwitchOnServer()
    {
        // Only sync if state actually changed
        if (!m_FurnaceState)
        {
            m_FurnaceState = true;
            SetSynchDirty();
        }

        LoggingUtility.LogDebug("[FreezeFurnace] Furnace started");
    }

    void SwitchOffServer()
    {
        // Only sync if state actually changed
        if (m_FurnaceState)
        {
            m_FurnaceState = false;
            SetSynchDirty();
        }

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).RemoveByName(this, "ProcessAndCraftBars");
    }


	bool IsFurnaceOn()
	{
		return m_FurnaceState;
	}

	void SetFurnaceActive(bool state)
	{
		// Only sync if state actually changed
		if (m_FurnaceState != state)
		{
			m_FurnaceState = state;
			SetSynchDirty();
		}
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
		return !m_FurnaceState;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnOffFurnace);
	}
};

class FreezeFurnace_Static extends FreezeFurnace
{
	
}

