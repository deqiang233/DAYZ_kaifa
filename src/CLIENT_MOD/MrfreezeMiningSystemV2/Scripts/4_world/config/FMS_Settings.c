class FreezeCraftingSettings
{
    bool EnableLogs = true;
    bool EnableDebug = false;
    int KeepLogDays = 7;
    int EnableVanillaRockMining = 0;
    int EnableGemCuttingMiniGame = 0;
    bool EnableFurnace = true;
    bool EnableGrindingStone = true;
    bool EnableAnvil = true;
    float PropaneCanisterUsage = 1.0;
    float GrindingWheelUsage = 1.0;
    float AnvilHammerDamage = 0.5;

    void FreezeCraftingSettings() {}

    static const string FILE_PATH = "$profile:FreezeMining\\FMS_Settings.json";
    
    // Performance optimization: Cache settings to avoid repeated file reads
    private static FreezeCraftingSettings cachedSettings = null;
    private static bool settingsCacheLoaded = false;

    static FreezeCraftingSettings Load()
    {
        // Return cached settings if already loaded
        if (settingsCacheLoaded && cachedSettings)
        {
            return cachedSettings;
        }

        FreezeCraftingSettings settings = new FreezeCraftingSettings();

        if (GetGame().IsDedicatedServer())
        {
            if (FileExist(FILE_PATH))
            {
                JsonFileLoader<FreezeCraftingSettings>.JsonLoadFile(FILE_PATH, settings);

                if (settings == null)
                    settings = new FreezeCraftingSettings();
            }
            else
            {
                settings.Save();
            }
        }

        // Cache the loaded settings
        cachedSettings = settings;
        settingsCacheLoaded = true;

        return settings;
    }
    
    // Method to invalidate cache if settings need to be reloaded (for future use)
    static void InvalidateCache()
    {
        cachedSettings = null;
        settingsCacheLoaded = false;
    }

    void Save()
    {
        if (GetGame().IsDedicatedServer())
        {
            LoggingUtility.EnsureDirectoriesExist();
            JsonFileLoader<FreezeCraftingSettings>.JsonSaveFile(FILE_PATH, this);
        }
    }
}
