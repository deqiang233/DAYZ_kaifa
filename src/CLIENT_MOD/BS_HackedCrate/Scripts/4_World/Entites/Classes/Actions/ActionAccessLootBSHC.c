class ActionAccessLootBSHC: ActionInteractBase
{
    void ActionAccessLootBSHC()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE; 
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.LootCorpse; 
        m_Text = "#STR_BSHC_Action_AccessLoot"; 
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTSelf; 
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
   {
    Object target_object = target.GetObject();
    if (!target_object) return false;

    HackedCrate_Base crate = HackedCrate_Base.Cast(target_object);
    if (crate)
    {
        CrateSettings crate_settings = crate.GetCrateSettings(); 
        if (crate_settings && !crate_settings.RequireAccessAction) {
            return false; 
        }

        return crate.HasBeenLooted() && crate.IsOpen() && !crate.m_LootAccessActionDone;
      }
    return false;
   }

    override void OnStartServer(ActionData action_data)
    {
    }

    override void OnEndServer(ActionData action_data)
    {
        HackedCrate_Base crate = HackedCrate_Base.Cast(action_data.m_Target.GetObject());
        if (crate && crate.HasBeenLooted() && crate.IsOpen() && !crate.m_LootAccessActionDone)
        {
            crate.m_LootAccessActionDone = true;
            crate.UpdateInventoryLock(); // ESTO ES PARA DESBLOQUEAR EL INVENTARIO NO TOCAR
            crate.SetSynchDirty();
            BSHC_Log.GetInstance().Info("Player " + action_data.m_Player.GetIdentity().GetName() + " accessed loot in HackedCrate: " + crate.GetPosition().ToString());
        }
    }

    // Opcional: NO TOCAR 
    /*
    override void OnEndClient(ActionData action_data)
    {
        HackedCrate_Base crate = HackedCrate_Base.Cast(action_data.m_Target.GetObject());
        if (crate && crate.m_LootAccessActionDone)
        {
            // Lógica para abrir la interfaz de inventario de la caja en el cliente
            GetGame().GetUIManager().ShowScriptedWidget(true, EUiElementsIDs.WindowInventory); // Ejemplo, puede necesitar ajuste
            InspectItem(action_data.m_Player, crate); // Esta función podría ayudar
        }
    }

    void InspectItem(PlayerBase player, ItemBase item) // NO TOCAR
    {
        if (GetGame().GetUIManager().GetMenu() == NULL && item)
        {
            GetGame().GetUIManager().ShowInventory(NULL, item);
        }
    }
    */
}