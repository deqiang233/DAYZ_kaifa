class FreezeAnvil extends ItemBase
{    
    ref protected EffectSound m_SoundLoop;
    private bool m_IsForging = false;

    void FreezeAnvil()
    {
        RegisterNetSyncVariableBool("m_IsForging");
    }

    void ~FreezeAnvil()
    {
        if (m_SoundLoop) {
            m_SoundLoop.SoundStop();
            delete m_SoundLoop;
        }
    }

    bool IsForging()
    {
        return m_IsForging;
    }

    void SetForging(bool state)
    {
        // Always sync to ensure sound restarts properly when crafting multiple items
        if (m_IsForging != state)
        {
            m_IsForging = state;
            SetSynchDirty();
        }
        else if (state == true)
        {
            // Force sync even if already true to restart sound when crafting multiple items
            SetSynchDirty();
        }
    }


    override bool CanReleaseAttachment(EntityAI attachment)
    {
        return !m_IsForging;
    }

    // Play the sound loop
    void StartLoopSound()
    {
        if (GetGame().IsDedicatedServer())
        {
            return;
        }

        if (!m_SoundLoop)
        {
            m_SoundLoop = SEffectManager.PlaySound("FreezeAnvil_On_SoundSet", GetPosition(), 0.0, 0.0, true);

            if (m_SoundLoop)
            {
                m_SoundLoop.SetAutodestroy(false);
            }
        }
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
        }
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();

        if (GetGame().IsDedicatedServer())
        {
            return;
        }

        if (m_IsForging)
        {
            // Always restart sound to ensure it plays when crafting multiple items
            StopLoopSound(); // Stop existing sound first
            StartLoopSound(); // Then start fresh
        }
        else
        {
            StopLoopSound();
        }
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent)) { return false; }        
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutIntoHands(parent))
        {
            return false;
        }
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }

    void Base_Destroy()
    {
        // delete object
        GetGame().ObjectDelete(this);
    }
    
    bool IsFacingFront(PlayerBase player, string selection)
    {
        vector metal_pos = GetPosition();
        vector player_pos = player.GetPosition();
        vector metal_dir = GetDirection();
        
        vector metal_player_dir = player_pos - metal_pos;
        metal_player_dir.Normalize();
        metal_dir.Normalize();
        
        if (metal_dir.Length() != 0)
        {
            float dot = vector.Dot(metal_player_dir, metal_dir);
            
            if (dot > 0)
            {
                return true;
            }
        }
        return false;
    }
    
    bool IsFacingBack(PlayerBase player, string selection)
    {
        return !IsFacingFront(player, selection);
    }
    
    bool HasProperDistance(string selection, PlayerBase player)
    {
        if (MemoryPointExists(selection))
        {
            vector selection_pos = ModelToWorld(GetMemoryPointPos(selection));
            float distance = vector.Distance(selection_pos, player.GetPosition());
            if (distance >= 1.3)
            {
                return false;
            }
        }
        return true;
    }
}

class FreezeAnvil_Static extends FreezeAnvil
{
    // Additional implementation if needed
}

