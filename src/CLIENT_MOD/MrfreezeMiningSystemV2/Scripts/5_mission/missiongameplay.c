modded class MissionGameplay {
    void MissionGameplay() {
        GetRPCManager().AddRPC("MrfreezeMiningRP", "MrfreezeMiningRPConfigBatch", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("MrfreezeMiningRP", "MrfreezeMiningRPCraftingTimes", this, SingleplayerExecutionType.Client);
        LoggingUtility.LogToFileFM("[MissionGameplay] RPC Manager for FreezeMining initialized.", true);
    }

    void MrfreezeMiningRPConfigBatch(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        if (type == CallType.Client) {
            Param1<array<ref Param2<string, string>>> data;
            if (!ctx.Read(data)) return;

            array<ref Param2<string, string>> configDataArray = data.param1;
            foreach (auto item : configDataArray) {
                string enabledType = item.param1;
                string actionText = item.param2;
                g_FreezeMiningClientConfig.Set(enabledType, actionText);
                LoggingUtility.LogToFileFM("[MissionGameplay] Updated client config for node type " + enabledType + " with action text: " + actionText, true);
            }
        }
    }

    void MrfreezeMiningRPCraftingTimes(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        if (type == CallType.Client) {
            Param1<ref FreezeCraftingTimesData> data;
            if (!ctx.Read(data)) return;

            FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.Cast(GetPlugin(FreezeCraftingTimesConfig));
            if (craftConfig) {
                craftConfig.ReceiveFromServer(data.param1);
                LoggingUtility.LogToFileFM("[MissionGameplay] Received crafting times from server", true);
            }
        }
    }
}
