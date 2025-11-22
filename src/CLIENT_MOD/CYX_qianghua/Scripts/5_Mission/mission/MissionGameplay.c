modded class MissionGameplay
{
    private ref EnhanceMenu m_EnhanceMenu;

    override void OnInit()
    {
        super.OnInit();
    }

    override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);

        if (!GetGame().IsClient())
        {
            return;
        }

        if (key == KeyCode.KC_RBRACKET)
        {
            TryOpenEnhanceMenu();
        }
    }

    private void TryOpenEnhanceMenu()
    {
        UIManager ui = GetGame().GetUIManager();
        if (!ui)
        {
            Print("[CYX_ENHANCE] ERROR: UIManager is null");
            return;
        }
        
        if (ui.GetMenu())
        {
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            if (player)
            {
                player.MessageImportant("请先关闭当前界面");
            }
            return;
        }

        Print("[CYX_ENHANCE] Creating new EnhanceMenu instance");
        m_EnhanceMenu = new EnhanceMenu();
        
        if (!m_EnhanceMenu)
        {
            Print("[CYX_ENHANCE] ERROR: Failed to create EnhanceMenu instance");
            return;
        }
        
        Print("[CYX_ENHANCE] Showing EnhanceMenu");
        ui.ShowScriptedMenu(m_EnhanceMenu, null);
        
        // 验证菜单是否成功打开
        if (ui.GetMenu() == m_EnhanceMenu)
        {
            Print("[CYX_ENHANCE] Menu successfully opened");
        }
        else
        {
            Print("[CYX_ENHANCE] WARNING: Menu may not have opened correctly");
        }
    }
}

