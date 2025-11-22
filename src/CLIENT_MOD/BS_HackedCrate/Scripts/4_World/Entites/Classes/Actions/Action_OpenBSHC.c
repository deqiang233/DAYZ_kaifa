class ActionOpenBSHC: ActionInteractBase 
{
    void ActionOpenBSHC()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.OpenHood;
        m_Text = "#STR_BSHC_Action_HackCrate"; 
    }

    override string GetText()
    {
        return m_Text;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object target_object = target.GetObject();
        if (target_object && target_object.IsInherited(HackedCrate_Base)) 
        {
            HackedCrate_Base ntarget = HackedCrate_Base.Cast(target_object);
            if (ntarget && !ntarget.IsOpen() && !ntarget.IsTimerStarted()) 
            {
                return true;
            }
        }
        return false;
    }

override void OnExecuteServer( ActionData action_data )
{
    PlayerBase player = PlayerBase.Cast(action_data.m_Player);
    if (!player) return;

    Object targetObject = action_data.m_Target.GetObject();
    if (!targetObject) return;

    HackedCrate_Base hackedCrate;
    if (Class.CastTo(hackedCrate, targetObject))
    {
        CrateSettings settings = hackedCrate.GetCrateSettings();
        if (settings)
        {
            hackedCrate.BSHC_StartCountdown();
        }
    }
}

    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);
    }

     override void OnEndClient(ActionData action_data)
     {
          super.OnEndClient(action_data);
     }
}
