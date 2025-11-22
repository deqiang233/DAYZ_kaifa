modded class MissionGameplay
{
    void MissionGameplay() { }

    override void OnInit()
    {
        super.OnInit();
        GetRPCManager().AddRPC("BS_HackedCrate", "BSHC_PlaySoundOnClientObject", this, SingeplayerExecutionType.Client); 
        GetRPCManager().AddRPC("BSHC_Notif_RPC", "Client_ShowStandardNotification", this, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", this, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("BSHC_Notif_RPC", "Client_ShowWarningNotification", this, SingeplayerExecutionType.Client);
        GetRPCManager().AddRPC("BSHC_Notif_RPC", "Client_ShowSimpleWarningNotification", this, SingeplayerExecutionType.Client);
    }

    void BSHC_PlaySoundOnClientObject(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
    {
        if (type != CallType.Client || !target) return;
        Param1<string> data;
        if (!ctx.Read(data)) return;
        string soundSetToPlay = data.param1;
        BSHC_Helper.GetInstance().BSHC_PlaySoundOnObject(soundSetToPlay, target); 
    }

    void Client_ShowStandardNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) return;
        Param2<string, string> data;
        if (!ctx.Read(data)) return;
        CreateNotification(data.param1, data.param2);
    }

    void Client_ShowSimpleNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) return;
        Param1<string> data;
        if (!ctx.Read(data)) return;
        CreateNotification(data.param1);
    }

    void Client_ShowWarningNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) return;
        Param3<string, string, string> data;
        if (!ctx.Read(data)) return;
        CreateNotification(data.param1, data.param3, data.param2);
    }

    void Client_ShowSimpleWarningNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) return;
        Param2<string, string> data;
        if (!ctx.Read(data)) return;
        CreateNotification(data.param1, "", data.param2);
    }

    void CreateNotification(string messageKeyWithHash, string locationName = "", string timeStr = "")
    {
        string messageKey = messageKeyWithHash;
        messageKey.Replace("#", "");
        
        StringLocaliser title = new StringLocaliser("STR_BSHC_Notification_Title");
        StringLocaliser message;

        if (timeStr != "" && locationName != "")
            message = new StringLocaliser(messageKey, timeStr, locationName);
        else if (timeStr != "" && locationName == "")
            message = new StringLocaliser(messageKey, timeStr);
        else if (locationName != "")
            message = new StringLocaliser(messageKey, locationName);
        else
            message = new StringLocaliser(messageKey);

        #ifdef EXPANSIONUI
        ExpansionNotification(title, message, "Hacked Crate", ARGB(255, 230, 0, 0)).Create();
        #else
        NotificationSystem.GetInstance().CreateNotification(title, message, "BS_HackedCrate/gui/newcrate.edds", 15);
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
        BSHC_Helper.GetInstance().BSHC_PlaySoundOnObject("BastardosNotification_SoundSet", player);
        }
        #endif
    }
}