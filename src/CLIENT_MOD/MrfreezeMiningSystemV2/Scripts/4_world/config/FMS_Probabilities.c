class FreezeItemProbability {
    string item;
    int probability;

    void FreezeItemProbability(string item, int prob) {
        this.item = item;
        this.probability = prob;
    }
}

class FreezeMinableItemConfig {
    string actionText;
    int max_mine = 6;
    ref array<string> enabledTypes;
    ref array<ref FreezeItemProbability> itemsProbabilities;


    void FreezeMinableItemConfig() {
        this.enabledTypes = new array<string>();
        this.itemsProbabilities = new ref array<ref FreezeItemProbability>();
    }

    array<ref FreezeItemProbability> getProbabilities() {
        return this.itemsProbabilities;
    }

    bool hasType(string type) {
        return this.enabledTypes.Find(type) > -1;
    }
}

class FreezeMiningConfig extends PluginBase
{
    ref array<ref FreezeMinableItemConfig> MRFRMINE = new ref array<ref FreezeMinableItemConfig>();
    const static ref map<string, int> mineCount = new map<string, int>();
    private const static string FileFolder = "$profile:FreezeMining\\Mining\\";
    private const static string FilePath = FileFolder + "FMS_Probabilities.json";

    override void OnInit()
    {
        LoggingUtility.LogToFileFM("[Freeze_Mining] FreezeMiningConfig::OnInit()", true);

        if (GetGame().IsDedicatedServer())
        {
            FreezeCraftingSettings.Load();
            LoadConfig();
            SendConfigToAllClients();
        }
    }


    int GetMaxMineForNode(string nodeType) {
        for (int i = 0; i < MRFRMINE.Count(); i++) {
            FreezeMinableItemConfig config = MRFRMINE.Get(i);
            if (config.hasType(nodeType)) {
                if (config.max_mine > 0) {
                    return config.max_mine;
                } else {
                    return 6;
                }
            }
        }
        return 6;
    }

    void LoadConfig() {
        LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Started loading config | Please Wait", true);
        LoggingUtility.EnsureDirectoriesExist();

        if (!FileExist(FilePath)) {
            LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Config file not found, initializing new config.", true);
            Init();
            SaveConfig();
        } else {
            JsonFileLoader<FreezeMiningConfig>.JsonLoadFile(FilePath, this);

            int itemCount = MRFRMINE.Count();
            LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Number of minable items loaded: " + itemCount.ToString(), true);

            for (int i = 0; i < MRFRMINE.Count(); i++) {
                FreezeMinableItemConfig config = MRFRMINE.Get(i);
                for (int j = 0; j < config.enabledTypes.Count(); j++) {
                    string enabledType = config.enabledTypes.Get(j);
                    g_FreezeMiningClientConfig.Set(enabledType, config.actionText);
                }
            }

            LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Finished loading config | Good to Go!", true);
        }
    }

    void Init()
    {
        LoggingUtility.LogToFileFM("[Freeze_Mining] Initializing default mining configurations...", true);
        this.CheckFolder();

        ref FreezeMinableItemConfig Coppercfg = new FreezeMinableItemConfig();
        Coppercfg.actionText = "Mine for Copper Ore";
        Coppercfg.enabledTypes = {"FreezeNode_copper"};
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_copper", 70));
        Coppercfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Coppercfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Copper Ore.", true);

        ref FreezeMinableItemConfig Sulphurcfg = new FreezeMinableItemConfig();
        Sulphurcfg.actionText = "Mine for Sulphur Ore";
        Sulphurcfg.enabledTypes = {"FreezeNode_sulphur"};
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_sulphur", 70));
        Sulphurcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Sulphurcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Sulphur Ore.", true);

        ref FreezeMinableItemConfig Goldcfg = new FreezeMinableItemConfig();
        Goldcfg.actionText = "Mine for Gold Ore";
        Goldcfg.enabledTypes = {"FreezeNode_gold"};
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_gold", 70));
        Goldcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Goldcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Gold Ore.", true);

        ref FreezeMinableItemConfig Silvercfg = new FreezeMinableItemConfig();
        Silvercfg.actionText = "Mine for Silver Ore";
        Silvercfg.enabledTypes = {"FreezeNode_silver"};
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_silver", 70));
        Silvercfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Silvercfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Silver Ore.", true);

        ref FreezeMinableItemConfig Tincfg = new FreezeMinableItemConfig();
        Tincfg.actionText = "Mine for Tin Ore";
        Tincfg.enabledTypes = {"FreezeNode_tin"};
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_tin", 70));
        Tincfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Tincfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Tin Ore.", true);

        ref FreezeMinableItemConfig Stonecfg = new FreezeMinableItemConfig();
        Stonecfg.actionText = "Mine for Stone";
        Stonecfg.enabledTypes = {"FreezeNode_stone"};
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 50));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_copper", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_silver", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_tin", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_iron", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_uranium", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 10));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Stonecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        this.MRFRMINE.Insert(Stonecfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Stone Ore.", true);

        ref FreezeMinableItemConfig Uraniumcfg = new FreezeMinableItemConfig();
        Uraniumcfg.actionText = "Mine for Uranium Ore";
        Uraniumcfg.enabledTypes = {"FreezeNode_uranium"};
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_uranium", 70));
        Uraniumcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Uraniumcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Uranium Ore.", true);

        ref FreezeMinableItemConfig Ambercfg = new FreezeMinableItemConfig();
        Ambercfg.actionText = "Mine for Raw Amber Gem";
        Ambercfg.enabledTypes = {"FreezeNode_AmberGemNode"};
        Ambercfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 70));
        Ambercfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Ambercfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Amber Gem.", true);

        ref FreezeMinableItemConfig Amethystcfg = new FreezeMinableItemConfig();
        Amethystcfg.actionText = "Mine for Raw Amethyst Gem";
        Amethystcfg.enabledTypes = {"FreezeNode_AmethystGemNode"};
        Amethystcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 70));
        Amethystcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Amethystcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Anethyst Gem.", true);

        ref FreezeMinableItemConfig Aquamrinecfg = new FreezeMinableItemConfig();
        Aquamrinecfg.actionText = "Mine for Raw Aquamarine Gem";
        Aquamrinecfg.enabledTypes = {"FreezeNode_AquamarineGemNode"};
        Aquamrinecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 70));
        Aquamrinecfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Aquamrinecfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Aquamarine Gem.", true);

        ref FreezeMinableItemConfig FancyColourDiamondcfg = new FreezeMinableItemConfig();
        FancyColourDiamondcfg.actionText = "Mine for Raw Fancy Colour Diamond Gem";
        FancyColourDiamondcfg.enabledTypes = {"FreezeNode_FancyColourDiamondGemNode"};
        FancyColourDiamondcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 70));
        FancyColourDiamondcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(FancyColourDiamondcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Fancy Colour Diamond Gem.", true);

        ref FreezeMinableItemConfig Iolitecfg = new FreezeMinableItemConfig();
        Iolitecfg.actionText = "Mine for Raw Iolite Gem";
        Iolitecfg.enabledTypes = {"FreezeNode_IoliteGemNode"};
        Iolitecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 70));
        Iolitecfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Iolitecfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Iolite Gem.", true);

        ref FreezeMinableItemConfig Jadecfg = new FreezeMinableItemConfig();
        Jadecfg.actionText = "Mine for Raw Jade Gem";
        Jadecfg.enabledTypes = {"FreezeNode_JadeGemNode"};
        Jadecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 70));
        Jadecfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Jadecfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Jade Gem.", true);

        ref FreezeMinableItemConfig Rubycfg = new FreezeMinableItemConfig();
        Rubycfg.actionText = "Mine for Raw Ruby Gem";
        Rubycfg.enabledTypes = {"FreezeNode_RubyGemNode"};
        Rubycfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 70));
        Rubycfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Rubycfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Ruby Gem.");

        ref FreezeMinableItemConfig Turquoisecfg = new FreezeMinableItemConfig();
        Turquoisecfg.actionText = "Mine for Raw Turquoise Gem";
        Turquoisecfg.enabledTypes = {"FreezeNode_TurquoiseGemNode"};
        Turquoisecfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 70));
        Turquoisecfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Turquoisecfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Raw Turquoise Gem.", true);

        ref FreezeMinableItemConfig Ironcfg = new FreezeMinableItemConfig();
        Ironcfg.actionText = "Mine for Iron Ore";
        Ironcfg.enabledTypes = {"FreezeNode_iron"};
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amber", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Amethyst", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Aquamarine", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_FancyColourDiamond", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Iolite", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Jade", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Ruby", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("FreezeGem_Turquoise", 0));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("Freezestone_iron", 70));
        Ironcfg.itemsProbabilities.Insert(new FreezeItemProbability("Stone", 30));
        this.MRFRMINE.Insert(Ironcfg);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Configured Iron Ore (All loaded).", true);
        LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Default mining configurations populated.", true);
    }

    map<string, int> getProbabilities() {
        FreezeVanillaRockConfig vanillaConfig = FreezeVanillaRockConfig.Cast(GetPlugin(FreezeVanillaRockConfig));
        if (vanillaConfig && vanillaConfig.IsEnabled())
        {
            return vanillaConfig.GetProbabilities();
        }
        return new map<string, int>();
    }

    void SaveConfig() {
        LoggingUtility.EnsureDirectoriesExist();
        JsonFileLoader<FreezeMiningConfig>.JsonSaveFile(FilePath, this);
        LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Saved mining config to file with " + MRFRMINE.Count().ToString() + " items.", true);
        for (int i = 0; i < MRFRMINE.Count(); i++) {
            FreezeMinableItemConfig config = MRFRMINE.Get(i);
            LoggingUtility.LogToFileFM("[Freeze_MiningCfg] Saving Item: " + config.actionText + " with " + config.itemsProbabilities.Count().ToString() + " probabilities.", true);
        }
    }

    void sendToClient(PlayerIdentity identity) {
        LoggingUtility.LogToFileFM("[Freeze_Mining] Sending batch configuration to client...", true);

        array<ref Param2<string, string>> configDataArray = new array<ref Param2<string, string>>();

        foreach (FreezeMinableItemConfig config : MRFRMINE) {
            foreach (string enabledType : config.enabledTypes) {
                configDataArray.Insert(new Param2<string, string>(enabledType, config.actionText));
            }
        }

        GetRPCManager().SendRPC("MrfreezeMiningRP", "MrfreezeMiningRPConfigBatch", new Param1<array<ref Param2<string, string>>>(configDataArray), true, identity);
        LoggingUtility.LogToFileFM("[Freeze_Mining] Batch configuration sent to client.", true);
    }

    void SendConfigToAllClients() {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) {
            return;
        }

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        if (players.Count() == 0) {
            LoggingUtility.LogToFileFM("[Freeze_Mining] No players connected. Skipping config send.", true);
            return;
        }

        foreach (Man player : players) {
            PlayerIdentity identity = player.GetIdentity();

            if (identity) {
                sendToClient(identity);
            } else {
                LoggingUtility.LogToFileFM("[Freeze_Mining] Skipped sending config to a player without a valid identity.", true);
            }
        }
    }


    array<ref FreezeItemProbability> getBuildingProbabilities(string buildingType) {
        for (int i = 0; i < this.MRFRMINE.Count(); i++)
        {
            FreezeMinableItemConfig config = this.MRFRMINE.Get(i);
            if (config.hasType(buildingType)) {
                return config.getProbabilities();
            }
        }

        return null;
    }

    ref FreezeMinableItemConfig getItemConfig(string buildingType) {
        for (int i = 0; i < this.MRFRMINE.Count(); i++)
        {
            FreezeMinableItemConfig config = this.MRFRMINE.Get(i);
            if (config.hasType(buildingType)) {
                return config;
            }
        }

        return null;
    }

    bool hasType(string itemType) {
        for (int i = 0; i < this.MRFRMINE.Count(); i++)
        {
            FreezeMinableItemConfig config = this.MRFRMINE.Get(i);
            if (config.hasType(itemType)) {
                return true;
            }
        }

        return false;
    }

    string GetText(string itemType) {
        for (int i = 0; i < this.MRFRMINE.Count(); i++)
        {
            FreezeMinableItemConfig config = this.MRFRMINE.Get(i);
            if (config.hasType(itemType)) {
                return config.actionText;
            }
        }

        return "Default Action";
    }

    static void CheckFolder() {
        if (!FileExist(FreezeMiningConfig.FileFolder)) {
            if (!FileExist("$profile:\\FreezeMining\\")) {
                MakeDirectory("$profile:\\FreezeMining\\");
            }
            LoggingUtility.LogToFileFM("[Freeze_Mining] Did not find profile folder, creating it.", true);
            MakeDirectory(FreezeMiningConfig.FileFolder);
        }
        LoggingUtility.LogToFileFM("[Freeze_Mining] Profile folder check complete.", true);
    }
};
