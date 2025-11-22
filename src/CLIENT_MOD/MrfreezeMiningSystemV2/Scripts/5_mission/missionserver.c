modded class MissionServer {
    FreezeMiningConfig m_FreezeMiningConfig;
    FreezeCraftingTimesConfig m_FreezeCraftingTimesConfig;

    override void OnInit() {
        super.OnInit();

        this.m_FreezeMiningConfig = FreezeMiningConfig.Cast(GetPlugin(FreezeMiningConfig));
        if (this.m_FreezeMiningConfig) {
            this.m_FreezeMiningConfig.LoadConfig();
            LoggingUtility.LogToFileFM("[MissionServer] FreezeMiningConfig initialized and loaded.", true);
        } else {
            LoggingUtility.LogToFileFM("[MissionServer] ERROR: Failed to initialize FreezeMiningConfig.", true);
        }

        this.m_FreezeCraftingTimesConfig = FreezeCraftingTimesConfig.Cast(GetPlugin(FreezeCraftingTimesConfig));
        if (this.m_FreezeCraftingTimesConfig) {
            LoggingUtility.LogToFileFM("[MissionServer] FreezeCraftingTimesConfig initialized.", true);
        }
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
        super.InvokeOnConnect(player, identity);

        if (m_FreezeMiningConfig) {
            m_FreezeMiningConfig.sendToClient(identity);
            LoggingUtility.LogToFileFM("[MissionServer] Sent mining configuration to client: " + identity.GetName(), true);
        } else {
            LoggingUtility.LogToFileFM("[MissionServer] ERROR: Failed to send mining configuration to client: " + identity.GetName(), true);
        }

        if (m_FreezeCraftingTimesConfig) {
            m_FreezeCraftingTimesConfig.SendToClient(identity);
            LoggingUtility.LogToFileFM("[MissionServer] Sent crafting times to client: " + identity.GetName(), true);
        }
    }
}