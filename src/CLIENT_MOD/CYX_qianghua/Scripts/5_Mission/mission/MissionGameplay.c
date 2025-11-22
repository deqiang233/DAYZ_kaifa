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
        if (GetGame().GetUIManager().GetMenu())
        {
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            if (player)
            {
                player.MessageImportant("请先关闭当前界面");
            }
            return;
        }

        m_EnhanceMenu = new EnhanceMenu();
        GetGame().GetUIManager().ShowScriptedMenu(m_EnhanceMenu, null);
    }
}

