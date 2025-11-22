class FreezeVanillaRockData
{
    ref map<string, int> VanillaRockProbabilities;

    void FreezeVanillaRockData()
    {
        VanillaRockProbabilities = new map<string, int>();
    }
}

class FreezeVanillaRockConfig extends PluginBase
{
    private const static string FileFolder = "$profile:FreezeMining\\Mining\\";
    private const static string FilePath = FileFolder + "FMS_VanillaRock.json";
    private bool m_Enabled = false;
    private ref FreezeVanillaRockData m_Data;

    void FreezeVanillaRockConfig()
    {
        m_Data = new FreezeVanillaRockData();
    }

    override void OnInit()
    {
        if (GetGame().IsDedicatedServer())
        {
            LoggingUtility.LogToFileFM("[FreezeVanillaRock] Initializing vanilla rock mining config...", true);
            LoadConfig();
            
            FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
            if (settings)
            {
                m_Enabled = (settings.EnableVanillaRockMining == 1);
                LoggingUtility.LogToFileFM("[FreezeVanillaRock] Vanilla rock mining enabled: " + m_Enabled.ToString(), true);
            }
        }
    }

    void LoadConfig()
    {
        LoggingUtility.LogToFileFM("[FreezeVanillaRock] Loading vanilla rock config...", true);

        if (!FileExist(FilePath))
        {
            LoggingUtility.LogToFileFM("[FreezeVanillaRock] Config not found, creating default config.", true);
            CreateDefaultConfig();
            SaveConfig();
        }
        else
        {
            JsonFileLoader<FreezeVanillaRockData>.JsonLoadFile(FilePath, m_Data);
            LoggingUtility.LogToFileFM("[FreezeVanillaRock] Config loaded with " + m_Data.VanillaRockProbabilities.Count().ToString() + " items.", true);
        }
    }

    void SaveConfig()
    {
        if (!GetGame().IsDedicatedServer())
        {
            return;
        }

        FreezeMiningConfig.CheckFolder();
        JsonFileLoader<FreezeVanillaRockData>.JsonSaveFile(FilePath, m_Data);
        LoggingUtility.LogToFileFM("[FreezeVanillaRock] Config saved to file.", true);
    }

    void CreateDefaultConfig()
    {
        m_Data.VanillaRockProbabilities.Set("Stone", 50);
        m_Data.VanillaRockProbabilities.Set("SmallStone", 10);
        m_Data.VanillaRockProbabilities.Set("Freezestone_iron", 12);
        m_Data.VanillaRockProbabilities.Set("Freezestone_copper", 12);
        m_Data.VanillaRockProbabilities.Set("Freezestone_tin", 12);
        m_Data.VanillaRockProbabilities.Set("Freezestone_silver", 10);
        m_Data.VanillaRockProbabilities.Set("Freezestone_gold", 10);
        m_Data.VanillaRockProbabilities.Set("Freezestone_sulphur", 12);
        m_Data.VanillaRockProbabilities.Set("Freezestone_uranium", 16);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Amber", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Amethyst", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Aquamarine", 5);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Turquoise", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Jade", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Ruby", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_Iolite", 4);
        m_Data.VanillaRockProbabilities.Set("FreezeGem_FancyColourDiamond", 4);
        
        LoggingUtility.LogToFileFM("[FreezeVanillaRock] Default vanilla rock probabilities created.", true);
    }

    bool IsEnabled()
    {
        return m_Enabled;
    }

    map<string, int> GetProbabilities()
    {
        return m_Data.VanillaRockProbabilities;
    }
};

