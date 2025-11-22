class FreezeCraftingTimesData
{
    ref map<string, int> FurnaceTimes;
    ref map<string, int> GrindStoneTimes;
    ref map<string, int> AnvilTimes;
    ref map<string, int> ExtendedTimes;
    ref map<string, int> PickaxeTimes;

    void FreezeCraftingTimesData()
    {
        FurnaceTimes = new map<string, int>();
        GrindStoneTimes = new map<string, int>();
        AnvilTimes = new map<string, int>();
        ExtendedTimes = new map<string, int>();
        PickaxeTimes = new map<string, int>();
    }
}

class FreezeCraftingTimesConfig extends PluginBase
{
    private static const string FILE_PATH = "$profile:FreezeMining\\Mining\\FMS_Crafting.json";
    private ref FreezeCraftingTimesData m_Data;
    private bool m_ConfigLoaded = false;
    
    // Performance optimization: Cache plugin reference to avoid repeated GetPlugin() calls
    private static FreezeCraftingTimesConfig cachedPlugin = null;

    void FreezeCraftingTimesConfig()
    {
        m_Data = new FreezeCraftingTimesData();
        
        // Only load config on server (client receives via RPC)
        if (GetGame().IsDedicatedServer())
        {
            LoadConfig();
        }
    }

    override void OnInit()
    {
        LoggingUtility.LogToFileFM("[Freeze_Mining] FreezeCraftingTimesConfig::OnInit()", true);
        
        // Config already loaded in constructor, just log
        if (m_ConfigLoaded)
        {
            LoggingUtility.LogToFileFM("[Freeze_Mining] Config was already loaded in constructor", true);
        }
    }

    void LoadConfig()
    {
        if (m_ConfigLoaded)
            return;

        LoggingUtility.EnsureDirectoriesExist();

        if (FileExist(FILE_PATH))
        {
            JsonFileLoader<FreezeCraftingTimesData>.JsonLoadFile(FILE_PATH, m_Data);

            if (m_Data)
            {
                m_ConfigLoaded = true;
                LoggingUtility.LogToFileFM("[Freeze_Mining] Loaded FMS_Crafting.json successfully", true);
                LoggingUtility.LogToFileFM("[Freeze_Mining] - Furnace Recipes: " + m_Data.FurnaceTimes.Count(), true);
                LoggingUtility.LogToFileFM("[Freeze_Mining] - GrindStone Recipes: " + m_Data.GrindStoneTimes.Count(), true);
                LoggingUtility.LogToFileFM("[Freeze_Mining] - Anvil Recipes: " + m_Data.AnvilTimes.Count(), true);
                LoggingUtility.LogToFileFM("[Freeze_Mining] - Extended Recipes: " + m_Data.ExtendedTimes.Count(), true);
                LoggingUtility.LogToFileFM("[Freeze_Mining] - Pickaxe Recipes: " + m_Data.PickaxeTimes.Count(), true);
            }
            else
            {
                LoggingUtility.LogToFileFM("[Freeze_Mining] ERROR: Failed to parse FMS_Crafting.json", true);
                m_Data = new FreezeCraftingTimesData();
                CreateDefaultConfig();
                m_ConfigLoaded = true;
            }
        }
        else
        {
            LoggingUtility.LogToFileFM("[Freeze_Mining] FMS_Crafting.json not found, creating default...", true);
            CreateDefaultConfig();
            m_ConfigLoaded = true;
        }
    }

    void CreateDefaultConfig()
    {
        m_Data = new FreezeCraftingTimesData();

        // Furnace Times (8 ore smelting recipes)
        m_Data.FurnaceTimes.Insert("SmeltStone", 5);
        m_Data.FurnaceTimes.Insert("SmeltCopper", 5);
        m_Data.FurnaceTimes.Insert("SmeltGold", 5);
        m_Data.FurnaceTimes.Insert("SmeltSilver", 5);
        m_Data.FurnaceTimes.Insert("SmeltTin", 5);
        m_Data.FurnaceTimes.Insert("SmeltIron", 5);
        m_Data.FurnaceTimes.Insert("SmeltSulphur", 5);
        m_Data.FurnaceTimes.Insert("SmeltUranium", 5);

        // GrindStone Times (8 recipes)
        m_Data.GrindStoneTimes.Insert("CraftAmber", 4);
        m_Data.GrindStoneTimes.Insert("CraftAmethyst", 4);
        m_Data.GrindStoneTimes.Insert("CraftAquamarine", 4);
        m_Data.GrindStoneTimes.Insert("CraftFancyColourDiamond", 4);
        m_Data.GrindStoneTimes.Insert("CraftIolite", 4);
        m_Data.GrindStoneTimes.Insert("CraftJade", 4);
        m_Data.GrindStoneTimes.Insert("CraftRuby", 4);
        m_Data.GrindStoneTimes.Insert("CraftTurquoise", 4);

        // Anvil Times (12 recipes: 6 basic ingots + 1 general + 5 special bars)
        m_Data.AnvilTimes.Insert("CraftCopperIngot", 4);
        m_Data.AnvilTimes.Insert("CraftGoldIngot", 4);
        m_Data.AnvilTimes.Insert("CraftSilverIngot", 4);
        m_Data.AnvilTimes.Insert("CraftTinIngot", 4);
        m_Data.AnvilTimes.Insert("CraftIronIngot", 4);
        m_Data.AnvilTimes.Insert("CraftUraniumIngot", 4);
        m_Data.AnvilTimes.Insert("CraftSulphurPowder", 4);
        m_Data.AnvilTimes.Insert("CraftAdamantite", 4);
        m_Data.AnvilTimes.Insert("CraftCobalt", 4);
        m_Data.AnvilTimes.Insert("CraftCrimant", 4);
        m_Data.AnvilTimes.Insert("CraftEnchanted", 4);
        m_Data.AnvilTimes.Insert("CraftEridium", 4);

        // Extended Times (27 recipes)
        m_Data.ExtendedTimes.Insert("Tier1_CraftBronzeFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftCompositeFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftCrystalFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftElectrumFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftPrismaticFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftRubyFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftSteelFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier1_CraftVoidFlawed", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftBronzeStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftCompositeStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftCrystalStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftElectrumStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftPrismaticStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftRubyStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftSteelStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier2_CraftVoidStandard", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftBronzePerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftCompositePerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftCrystalPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftElectrumPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftPrismaticPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftRubyPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftSteelPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier3_CraftVoidPerfect", 4);
        m_Data.ExtendedTimes.Insert("Tier4_CraftAscendant", 4);
        m_Data.ExtendedTimes.Insert("Tier4_CraftCelestial", 4);
        m_Data.ExtendedTimes.Insert("Tier4_CraftInfinity", 4);
        m_Data.ExtendedTimes.Insert("Tier4_CraftTitanforge", 4);
        m_Data.ExtendedTimes.Insert("Tier5_CraftBloodmetal", 4);
        m_Data.ExtendedTimes.Insert("Tier5_CraftVoidsteel", 4);
        m_Data.ExtendedTimes.Insert("Tier6_CraftNexus", 4);

        // Pickaxe Times (3 recipes)
        m_Data.PickaxeTimes.Insert("CraftT1ReinforcedPickaxe", 4);
        m_Data.PickaxeTimes.Insert("CraftT2CrystalforgePickaxe", 4);
        m_Data.PickaxeTimes.Insert("CraftT3FusioncorePickaxe", 4);

        SaveConfig();
        LoggingUtility.LogToFileFM("[Freeze_Mining] Created default FMS_Crafting.json with all recipe times", true);
    }

    void SaveConfig()
    {
        // Only save on server
        if (!GetGame().IsDedicatedServer())
            return;

        LoggingUtility.EnsureDirectoriesExist();
        
        JsonFileLoader<FreezeCraftingTimesData>.JsonSaveFile(FILE_PATH, m_Data);
        
        if (FileExist(FILE_PATH))
        {
            LoggingUtility.LogToFileFM("[Freeze_Mining] Successfully saved FMS_Crafting.json to: " + FILE_PATH, true);
        }
        else
        {
            LoggingUtility.LogToFileFM("[Freeze_Mining] ERROR: Failed to save FMS_Crafting.json - file does not exist after save attempt", true);
        }
    }

    // Send config to client via RPC
    void SendToClient(PlayerIdentity identity)
    {
        if (!GetGame().IsServer() || !m_ConfigLoaded)
            return;

        auto params = new Param1<ref FreezeCraftingTimesData>(m_Data);
        GetRPCManager().SendRPC("MrfreezeMiningRP", "MrfreezeMiningRPCraftingTimes", params, true, identity);
        LoggingUtility.LogToFileFM("[FreezeCraftingTimesConfig] Sent crafting times to client", true);
    }

    // Receive config from server (client side)
    void ReceiveFromServer(FreezeCraftingTimesData data)
    {
        if (GetGame().IsServer())
            return;

        m_Data = data;
        m_ConfigLoaded = true;
        
        // Populate global map for easy access
        g_FreezeCraftingTimes.Clear();
        
        for (int i = 0; i < data.FurnaceTimes.Count(); i++)
        {
            g_FreezeCraftingTimes.Insert(data.FurnaceTimes.GetKey(i), data.FurnaceTimes.GetElement(i));
        }
        for (int j = 0; j < data.GrindStoneTimes.Count(); j++)
        {
            g_FreezeCraftingTimes.Insert(data.GrindStoneTimes.GetKey(j), data.GrindStoneTimes.GetElement(j));
        }
        for (int k = 0; k < data.AnvilTimes.Count(); k++)
        {
            g_FreezeCraftingTimes.Insert(data.AnvilTimes.GetKey(k), data.AnvilTimes.GetElement(k));
        }
        for (int l = 0; l < data.ExtendedTimes.Count(); l++)
        {
            g_FreezeCraftingTimes.Insert(data.ExtendedTimes.GetKey(l), data.ExtendedTimes.GetElement(l));
        }
        for (int m = 0; m < data.PickaxeTimes.Count(); m++)
        {
            g_FreezeCraftingTimes.Insert(data.PickaxeTimes.GetKey(m), data.PickaxeTimes.GetElement(m));
        }
        
        LoggingUtility.LogToFileFM("[FreezeCraftingTimesConfig] Received " + g_FreezeCraftingTimes.Count() + " crafting times from server", true);
    }

    // Get animation length for a recipe
    // JSON values are in SECONDS, this converts to m_AnimationLength
    // Formula: m_AnimationLength = seconds * 0.25 (each unit = 4 seconds)
    // Example: 60 seconds = 15 units, 4 seconds = 1 unit, 1 second = 0.25 units
    float GetAnimationLength(string recipeClassName)
    {
        int seconds = 4; // default seconds

        if (m_Data.FurnaceTimes.Contains(recipeClassName))
        {
            seconds = m_Data.FurnaceTimes.Get(recipeClassName);
        }
        else if (m_Data.GrindStoneTimes.Contains(recipeClassName))
        {
            seconds = m_Data.GrindStoneTimes.Get(recipeClassName);
        }
        else if (m_Data.AnvilTimes.Contains(recipeClassName))
        {
            seconds = m_Data.AnvilTimes.Get(recipeClassName);
        }
        else if (m_Data.ExtendedTimes.Contains(recipeClassName))
        {
            seconds = m_Data.ExtendedTimes.Get(recipeClassName);
        }
        else if (m_Data.PickaxeTimes.Contains(recipeClassName))
        {
            seconds = m_Data.PickaxeTimes.Get(recipeClassName);
        }

        // Convert seconds to m_AnimationLength
        // Formula: 1 second = 0.25 animation units
        float animationLength = seconds * 0.25;

        return animationLength;
    }

    // Get raw seconds value (for display or other purposes)
    int GetCraftTimeSeconds(string recipeClassName)
    {
        if (m_Data.FurnaceTimes.Contains(recipeClassName))
            return m_Data.FurnaceTimes.Get(recipeClassName);
        
        if (m_Data.GrindStoneTimes.Contains(recipeClassName))
            return m_Data.GrindStoneTimes.Get(recipeClassName);
        
        if (m_Data.AnvilTimes.Contains(recipeClassName))
            return m_Data.AnvilTimes.Get(recipeClassName);
        
        if (m_Data.ExtendedTimes.Contains(recipeClassName))
            return m_Data.ExtendedTimes.Get(recipeClassName);
        
        if (m_Data.PickaxeTimes.Contains(recipeClassName))
            return m_Data.PickaxeTimes.Get(recipeClassName);

        return 4; // default if recipe not found in config
    }
    
    // Performance optimization: Get cached plugin reference (avoids repeated GetPlugin() calls)
    static FreezeCraftingTimesConfig GetCached()
    {
        if (!cachedPlugin)
        {
            cachedPlugin = FreezeCraftingTimesConfig.Cast(GetPlugin(FreezeCraftingTimesConfig));
        }
        return cachedPlugin;
    }
}

