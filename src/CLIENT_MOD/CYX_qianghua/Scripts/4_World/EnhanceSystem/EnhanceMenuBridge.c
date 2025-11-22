class EnhanceMenuBridge
{
    protected static bool IsEnhanceMenu(UIScriptedMenu menu)
    {
        if (!menu)
        {
            return false;
        }

        typename menuType = menu.Type();
        if (!menuType)
        {
            return false;
        }

        return menuType.ToString() == "EnhanceMenu";
    }

    protected static UIScriptedMenu GetActiveMenu()
    {
        UIManager ui = GetGame().GetUIManager();
        if (!ui)
        {
            return null;
        }

        UIScriptedMenu menu = ui.GetMenu();
        if (IsEnhanceMenu(menu))
        {
            return menu;
        }

        return null;
    }

    static void HandleEnhanceResult(bool success, string message)
    {
        UIScriptedMenu menu = GetActiveMenu();
        if (!menu)
        {
            return;
        }

        Param2<bool, string> payload = new Param2<bool, string>(success, message);
        GetGame().GameScript.CallFunction(menu, "OnEnhanceResultRPC", null, payload);
    }

    static void HandleInfoResponse(EnhanceDisplayInfo info)
    {
        UIScriptedMenu menu = GetActiveMenu();
        if (!menu)
        {
            return;
        }

        Param1<ref EnhanceDisplayInfo> payload = new Param1<ref EnhanceDisplayInfo>(info);
        GetGame().GameScript.CallFunction(menu, "OnInfoResponseRPC", null, payload);
    }
}

