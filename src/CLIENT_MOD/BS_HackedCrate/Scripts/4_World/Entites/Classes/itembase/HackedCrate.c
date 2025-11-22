enum EHCNotificationType
{
    START,
    END,
    DESPAWN
}
static ref array<HackedCrate_Base> g_ActiveHackedCrates = new array<HackedCrate_Base>;
class HCLocation
{
    string Position;
    string Rotation;
    string LocationName;

    void HCLocation(string pos = "", string rot = "", string locName = "") 
    {
        Position = pos;
        Rotation = rot;
        LocationName = locName; 
    }

    vector GetPosition()
    {
        return Position.ToVector();
    }

    vector GetRotation()
    {
        return Rotation.ToVector();
    }
        string GetLocationName() 
    {
        if (LocationName == "") return "an unknown location"; 
        return LocationName;
    }
}
class CrateSettings
{
    string ConfigUniqueID;
    bool UseExpansionMapMarker;
    bool UseAdvancedGroupsMapMarker;
    bool StaticSpawns; 
    int ActiveCrateCount;
    bool AutoRefresh;
    int RefreshInterval;
    string CrateType;
    ref array<string> LootCategoriesToUse;
    bool UseCrateNotifications;
    string CrateSpawnNotification_Key;
    string CrateStartNotification_Key;
    string CrateEndNotification_Key;
    string CrateDespawnNotification_Key;
    string CrateWarningNotification_Key;
    string CrateSpawnNotification_Key_Located;
    string CrateWarningNotification_Key_Located;
    string CrateStartNotification_Key_Located;
    string CrateEndNotification_Key_Located;
    string CrateDespawnNotification_Key_Located;
    bool EnableSpawnNotification;       
    bool EnableStartNotification;       
    bool EnableEndNotification;         
    bool EnableDespawnNotification; 
    bool ShowLocationInNotifications;
    int WarningTimeMinutes;              // Tiempo en minutos para la advertencia (0 para desactivar)
    bool IgnorePlayerCheckOnWarnedSpawn; // Si es 'true', la caja aparecerá incluso si hay jugadores cerca después de la advertencia.
    string ExpansionMarkerColor;      
    string AdvancedGroupsMarkerColor;
    bool MarkerEnable2D;              
    bool MarkerEnable3D;
    bool EnableMarkerHackingProgress; // Opción para el porcentaje
    bool EnableMarkerUnlockedStatus;  // Opción para el estado "Desbloqueado"       
    bool RequireAccessAction;
    int CountdownTime;
    ref array<ref HCLocation> CrateLocations;
    int AutoDespawnTimeMinutes;
    int MaxLifetimeMinutes_NotTouched;
    int MinPlayersToSpawnCrate;
    bool EnablePlayerNearbyCheck;
    float PlayerNearbyCheckRadius;
    bool SpawnAIOnHackStart;
    ref array<string> AISpawnTypes;
    int MinAIToSpawn;
    int MaxAIToSpawn;
    float AISpawnRadiusMin;
    float AISpawnRadiusMax;
    bool SpawnAIOnCrateSpawn;
    bool UseAIWaves;
    int NumberOfAIWaves;
    float TimeBetweenAIWavesSeconds;
    ref array<string> AIWaveSpawnTypes;
    int MinAIToSpawnPerWave;
    int MaxAIToSpawnPerWave;
    float AIWaveSpawnRadiusMin;
    float AIWaveSpawnRadiusMax;
    float AIWaveInitialDelaySeconds;
    string lb_preset_name;
    string MarkerDisplayName;  // 自定义地图标记显示名称，如果为空则使用默认字符串键

    void CrateSettings()
    {
        ConfigUniqueID = "";
        CrateLocations = new array<ref HCLocation>;
        LootCategoriesToUse = new array<string>;
        UseExpansionMapMarker = true;
        UseAdvancedGroupsMapMarker = true;
        StaticSpawns = false;
        ActiveCrateCount = 1;
        AutoRefresh = false;
        RefreshInterval = 3600;
        CrateType = "BS_Hacked_Crate";
        UseCrateNotifications = true; 
        EnableSpawnNotification = true;
        EnableStartNotification = true;
        EnableEndNotification = true;
        EnableDespawnNotification = true;
        CrateSpawnNotification_Key = "#STR_BSHC_Notification_Spawn_Default";
        CrateStartNotification_Key = "#STR_BSHC_Notification_Start_Default";
        CrateEndNotification_Key = "#STR_BSHC_Notification_End_Default";
        CrateDespawnNotification_Key = "#STR_BSHC_Notification_Despawn_Default";
        CrateWarningNotification_Key = "#STR_BSHC_Notification_Warning_Default";
        CrateSpawnNotification_Key_Located = "#STR_BSHC_Notification_Spawn_Located";
        CrateWarningNotification_Key_Located = "#STR_BSHC_Notification_Warning_Located";
        CrateStartNotification_Key_Located = "#STR_BSHC_Notification_Start_Located";
        CrateEndNotification_Key_Located = "#STR_BSHC_Notification_End_Located";
        CrateDespawnNotification_Key_Located = "#STR_BSHC_Notification_Despawn_Located";
        ShowLocationInNotifications = true;
        WarningTimeMinutes = 10; // Por defecto, una advertencia de 10 minutos
        IgnorePlayerCheckOnWarnedSpawn = true; // Por defecto, la caja aparecerá sí o sí
        ExpansionMarkerColor = "255,255,0,0";      
        AdvancedGroupsMarkerColor = "255,255,0,0"; // Formato ARGB,Espero que estos locos entiendan qeu es formato ARGB Y NO RGB
        MarkerEnable2D = true;       // activar y desactivar marcadores qliados 2d/3d
        MarkerEnable3D = true;
        EnableMarkerHackingProgress = true;
        EnableMarkerUnlockedStatus = true;   
        RequireAccessAction = true;
        CountdownTime = 900;
        AutoDespawnTimeMinutes = 20;
        MinPlayersToSpawnCrate = 0;
        EnablePlayerNearbyCheck = true; // Por defecto activado
        PlayerNearbyCheckRadius = 10.0; // Radio por defecto
        SpawnAIOnHackStart = false;
        AISpawnTypes = new array<string>;
        MinAIToSpawn = 0;
        MaxAIToSpawn = 0;
        AISpawnRadiusMin = 5.0;
        AISpawnRadiusMax = 15.0;
        SpawnAIOnCrateSpawn = false;
        UseAIWaves = false;
        NumberOfAIWaves = 3;
        TimeBetweenAIWavesSeconds = 120.0;
        AIWaveSpawnTypes = new array<string>;
        MinAIToSpawnPerWave = 2;
        MaxAIToSpawnPerWave = 4;
        AIWaveSpawnRadiusMin = 10.0;
        AIWaveSpawnRadiusMax = 25.0;
        AIWaveInitialDelaySeconds = 5.0;
        lb_preset_name = "";
        MarkerDisplayName = "";  // 默认为空，使用默认字符串键
    }


    void LoadSettings(string filePath)
    {
        if (FileExist(filePath))
        {
            JsonFileLoader<CrateSettings>.JsonLoadFile(filePath, this);
        }
    }

    void SaveSettings(string filePath)
    {
        JsonFileLoader<CrateSettings>.JsonSaveFile(filePath, this);
    }
}
class BSHCGlobalServerSettings
{
    int ServerStartGracePeriod;
    int PeriodicTickIntervalSeconds;

    void BSHCGlobalServerSettings()
    {
        ServerStartGracePeriod = 5;      
        PeriodicTickIntervalSeconds = 3600; 
    }

    static ref BSHCGlobalServerSettings Load(string filePath)
    {
        ref BSHCGlobalServerSettings settings = new BSHCGlobalServerSettings();
        if (FileExist(filePath))
        {
            BSHC_Log.GetInstance().Info("[BSHCGlobalServerSettings] Loading from: " + filePath);
            JsonFileLoader<BSHCGlobalServerSettings>.JsonLoadFile(filePath, settings);
            if (!settings) { 
                 BSHC_Log.GetInstance().Error("[BSHCGlobalServerSettings] JsonLoadFile returned null for: " + filePath + ". Creating default instance.");
                 settings = new BSHCGlobalServerSettings(); 
                 settings.Save(filePath); 
            }
        }
        else
        {
            BSHC_Log.GetInstance().Info("[BSHCGlobalServerSettings] File not found: " + filePath + ". Saving default global settings.");
            settings.Save(filePath); 
        }
        return settings;
    }

    void Save(string filePath)
    {
        BSHC_Log.GetInstance().Info("[BSHCGlobalServerSettings] Saving to: " + filePath);
        JsonFileLoader<BSHCGlobalServerSettings>.JsonSaveFile(filePath, this);
    }
}
class CrateManagement
{
    ref array<ref CrateSettings> CrateConfigs; 
    int ServerStartGracePeriod;               
    int PeriodicTickIntervalSeconds;           

    void CrateManagement()
    {
        CrateConfigs = new array<ref CrateSettings>;
        ServerStartGracePeriod = 5;
        PeriodicTickIntervalSeconds = 3600;
        BSHC_Log.GetInstance().Info("CrateManagement instance created with default grace period and tick interval.");
    }

    CrateSettings CreateDefaultCrateSettings(
        bool forStaticSpawn, 
        string crateTypeToUse,
        int activeCount, 
        array<ref HCLocation> locations 
    )
    {
        ref CrateSettings settings = new CrateSettings();

        settings.StaticSpawns = forStaticSpawn; 
        settings.CrateType = crateTypeToUse;
        settings.CrateLocations = locations;

        settings.UseExpansionMapMarker = true;
        settings.UseAdvancedGroupsMapMarker = true;
        //settings.UseCrateNotifications = true;
        settings.ExpansionMarkerColor = "255,255,0,0";
        settings.AdvancedGroupsMarkerColor = "255,255,0,0";
        settings.MarkerEnable2D = true;
        settings.MarkerEnable3D = true;
        settings.CountdownTime = 900;
        settings.AutoDespawnTimeMinutes = 30; 
        settings.MinPlayersToSpawnCrate = 1;  

        if (forStaticSpawn) {
            settings.CrateSpawnNotification_Key = "#STR_BSHC_Notification_Spawn_Default"; 
            settings.CrateStartNotification_Key = "#STR_BSHC_Notification_Start_Default";
            settings.CrateEndNotification_Key = "#STR_BSHC_Notification_End_Default";
            settings.CrateDespawnNotification_Key = "#STR_BSHC_Notification_Despawn_Default";
            settings.ActiveCrateCount = 1; 
            settings.AutoRefresh = false; 
            settings.RefreshInterval = 7200;
            settings.LootCategoriesToUse.Insert("DefaultMedical");
            settings.MinPlayersToSpawnCrate = 0;
            settings.EnablePlayerNearbyCheck = true; 
            settings.PlayerNearbyCheckRadius = 15.0; 
        } else { 
            settings.CrateSpawnNotification_Key = "#STR_BSHC_Notification_Spawn_Default";
            settings.CrateStartNotification_Key = "#STR_BSHC_Notification_Start_Default";
            settings.CrateEndNotification_Key = "#STR_BSHC_Notification_End_Default";
            settings.CrateDespawnNotification_Key = "#STR_BSHC_Notification_Despawn_Default";
            settings.EnableSpawnNotification = true;   
            settings.EnableStartNotification = true;   
            settings.EnableEndNotification = true;     
            settings.EnableDespawnNotification = true; 
            settings.ActiveCrateCount = activeCount;
            settings.EnablePlayerNearbyCheck = true; 
            settings.PlayerNearbyCheckRadius = 15.0; 
            settings.AutoRefresh = true;
            settings.RefreshInterval = 3600;
            settings.LootCategoriesToUse.Insert("DefaultArmaments");
            settings.LootCategoriesToUse.Insert("DefaultMedical");
        }
        settings.SpawnAIOnCrateSpawn = true;
        settings.AISpawnTypes.Insert("ZmbM_SoldierNormal");
        settings.MinAIToSpawn = 1;
        settings.MaxAIToSpawn = 3;
        settings.AISpawnRadiusMin = 10;
        settings.AISpawnRadiusMax = 25;
        
        settings.UseAIWaves = false;
        settings.NumberOfAIWaves = 3;         
        settings.TimeBetweenAIWavesSeconds = 60.0; 
        settings.MinAIToSpawnPerWave = 2;    
        settings.MaxAIToSpawnPerWave = 3; 
        settings.AIWaveSpawnRadiusMin = 10.0;
        settings.AIWaveSpawnRadiusMax = 20.0;
        settings.AIWaveInitialDelaySeconds = 10.0; 
        settings.AIWaveSpawnTypes.Insert("ZmbM_HermitSkinny_Beige"); 
        settings.AIWaveSpawnTypes.Insert("ZmbM_FarmerFat_Green");    
        settings.AIWaveSpawnTypes.Insert("Animal_UrsusArctos");  
        
        return settings;
    }

   array<ref HCLocation> CreateDefaultLocationsForDynamic()
    {
    array<ref HCLocation> locations = new array<ref HCLocation>;
    locations.Insert(new HCLocation("4732.430176 338.968994 10350.200195", "0.0 0.0 0.0", "Airfield"));
    locations.Insert(new HCLocation("4553.689941 317.975006 8352.099609", "0.0 0.0 0.0", "VMC"));
    return locations;
    }

    array<ref HCLocation> CreateDefaultLocationForStatic()
    {
    array<ref HCLocation> locations = new array<ref HCLocation>;
    locations.Insert(new HCLocation("2471.820068 193.177002 5114.220215", "0.0 0.0 0.0", "Zelenogorks"));
    return locations;
    }
}

class CrateConfigManager
{
    private static ref CrateManagement m_StaticCrateManagement;
    private ref CrateManagement m_InstanceCrateManagement;

    void CrateConfigManager()
    {
        m_InstanceCrateManagement = new CrateManagement();
    }

    void SetStaticManagement(CrateManagement mgmt)
    {
        m_StaticCrateManagement = mgmt;
        if (m_StaticCrateManagement) BSHC_Log.GetInstance().Info("[CrateConfigManager] Static CrateManagement has been set.");
        else BSHC_Log.GetInstance().Error("[CrateConfigManager] Attempted to set NULL Static CrateManagement.");
    }

    static CrateManagement GetLoadedCrateManagement()
    {
        if (!m_StaticCrateManagement) {
        }
        return m_StaticCrateManagement;
    }

    CrateManagement GetCrateManagement()
    {
        return m_InstanceCrateManagement;
    }

   void LoadOrCreateConfigs()
   {
    string configDir = "$profile:\\Bastardo_HC";
    string globalSettingsPath = configDir + "\\BS_Global_settings.json";
    string staticCratesPath = configDir + "\\BS_Static_crates.json";
    string dynamicCratesPath = configDir + "\\BS_Dynamic_crates.json";

    if (!FileExist(configDir))
    {
        MakeDirectory(configDir);
    }

    bool globalExists = FileExist(globalSettingsPath);
    bool staticExists = FileExist(staticCratesPath);
    bool dynamicExists = FileExist(dynamicCratesPath);

    if (!globalExists || !staticExists || !dynamicExists)
    {
        SaveDefaultAllConfigs(globalSettingsPath, staticCratesPath, dynamicCratesPath);
        globalExists = FileExist(globalSettingsPath);
        staticExists = FileExist(staticCratesPath);
        dynamicExists = FileExist(dynamicCratesPath);
    }

    if (globalExists) {
        ref BSHCGlobalServerSettings globalCfg = BSHCGlobalServerSettings.Load(globalSettingsPath);
        if (globalCfg && m_InstanceCrateManagement)
        {
            m_InstanceCrateManagement.ServerStartGracePeriod = globalCfg.ServerStartGracePeriod;
            m_InstanceCrateManagement.PeriodicTickIntervalSeconds = globalCfg.PeriodicTickIntervalSeconds;
        }
    }

    if (m_InstanceCrateManagement)
    {
        m_InstanceCrateManagement.CrateConfigs.Clear();
    }

    // --- LÓGICA PARA CAJAS ESTÁTICAS ---
    if (staticExists) {
        ref array<ref CrateSettings> staticCrateList = new array<ref CrateSettings>;
        JsonFileLoader<array<ref CrateSettings>>.JsonLoadFile(staticCratesPath, staticCrateList);
        if (staticCrateList)
        {
            foreach (CrateSettings setting : staticCrateList)
            {
                if (setting) {
                    
                    if (setting.CountdownTime <= 0) setting.CountdownTime = 900;
                    if (setting.WarningTimeMinutes < 0) setting.WarningTimeMinutes = 10;
                    if (setting.MaxLifetimeMinutes_NotTouched < 0) setting.MaxLifetimeMinutes_NotTouched = 180;
                    
                    if (setting.CrateDespawnNotification_Key == "") setting.CrateDespawnNotification_Key = "#STR_BSHC_Notification_Despawn_Default";
                    if (setting.CrateWarningNotification_Key == "") setting.CrateWarningNotification_Key = "#STR_BSHC_Notification_Warning_Default";
                    if (setting.CrateSpawnNotification_Key_Located == "") setting.CrateSpawnNotification_Key_Located = "#STR_BSHC_Notification_Spawn_Located";
                    if (setting.CrateWarningNotification_Key_Located == "") setting.CrateWarningNotification_Key_Located = "#STR_BSHC_Notification_Warning_Located";
                    if (setting.CrateStartNotification_Key_Located == "") setting.CrateStartNotification_Key_Located = "#STR_BSHC_Notification_Start_Located";
                    if (setting.CrateEndNotification_Key_Located == "") setting.CrateEndNotification_Key_Located = "#STR_BSHC_Notification_End_Located";
                    if (setting.CrateDespawnNotification_Key_Located == "") setting.CrateDespawnNotification_Key_Located = "#STR_BSHC_Notification_Despawn_Located";
                    if (setting.ExpansionMarkerColor == "") setting.ExpansionMarkerColor = "255,255,0,0";
                    if (setting.AdvancedGroupsMarkerColor == "") setting.AdvancedGroupsMarkerColor = "255,255,0,0";
                    
                    setting.StaticSpawns = true;
                    m_InstanceCrateManagement.CrateConfigs.Insert(setting);
                }
            }
            JsonFileLoader<array<ref CrateSettings>>.JsonSaveFile(staticCratesPath, staticCrateList);
            BSHC_Log.GetInstance().Info("[CrateConfigManager] Re-saved static_crates.json to include any new options.");
        }
    }

    if (dynamicExists) {
        ref array<ref CrateSettings> dynamicCrateList = new array<ref CrateSettings>;
        JsonFileLoader<array<ref CrateSettings>>.JsonLoadFile(dynamicCratesPath, dynamicCrateList);
        if (dynamicCrateList)
        {
            foreach (CrateSettings dynamic_setting : dynamicCrateList)
            {
                 if (dynamic_setting) {

                    if (dynamic_setting.CountdownTime <= 0) dynamic_setting.CountdownTime = 900;
                    if (dynamic_setting.WarningTimeMinutes < 0) dynamic_setting.WarningTimeMinutes = 10;
                    if (dynamic_setting.MaxLifetimeMinutes_NotTouched < 0) dynamic_setting.MaxLifetimeMinutes_NotTouched = 180;

                    if (dynamic_setting.CrateDespawnNotification_Key == "") dynamic_setting.CrateDespawnNotification_Key = "#STR_BSHC_Notification_Despawn_Default";
                    if (dynamic_setting.CrateWarningNotification_Key == "") dynamic_setting.CrateWarningNotification_Key = "#STR_BSHC_Notification_Warning_Default";
                    if (dynamic_setting.CrateSpawnNotification_Key_Located == "") dynamic_setting.CrateSpawnNotification_Key_Located = "#STR_BSHC_Notification_Spawn_Located";
                    if (dynamic_setting.CrateWarningNotification_Key_Located == "") dynamic_setting.CrateWarningNotification_Key_Located = "#STR_BSHC_Notification_Warning_Located";
                    if (dynamic_setting.CrateStartNotification_Key_Located == "") dynamic_setting.CrateStartNotification_Key_Located = "#STR_BSHC_Notification_Start_Located";
                    if (dynamic_setting.CrateEndNotification_Key_Located == "") dynamic_setting.CrateEndNotification_Key_Located = "#STR_BSHC_Notification_End_Located";
                    if (dynamic_setting.CrateDespawnNotification_Key_Located == "") dynamic_setting.CrateDespawnNotification_Key_Located = "#STR_BSHC_Notification_Despawn_Located";
                    if (dynamic_setting.ExpansionMarkerColor == "") dynamic_setting.ExpansionMarkerColor = "255,255,0,0";
                    if (dynamic_setting.AdvancedGroupsMarkerColor == "") dynamic_setting.AdvancedGroupsMarkerColor = "255,255,0,0";

                    dynamic_setting.StaticSpawns = false;
                    m_InstanceCrateManagement.CrateConfigs.Insert(dynamic_setting);
                 }
            }
            JsonFileLoader<array<ref CrateSettings>>.JsonSaveFile(dynamicCratesPath, dynamicCrateList);
            BSHC_Log.GetInstance().Info("[CrateConfigManager] Re-saved dynamic_crates.json to include any new options.");
        }
    }

    SetStaticManagement(m_InstanceCrateManagement);

    if (m_InstanceCrateManagement.CrateConfigs.Count() == 0)
      {
        BSHC_Log.GetInstance().Warning("[CrateConfigManager] No crate configurations loaded from static or dynamic files.");
      }
   }
    void SaveDefaultAllConfigs(string globalPath, string staticPath, string dynamicPath)
    {
        BSHC_Log.GetInstance().Info("[CrateConfigManager] Attempting to save default configurations...");

        if (!FileExist(globalPath)) {
            ref BSHCGlobalServerSettings defaultGlobal = new BSHCGlobalServerSettings();
            defaultGlobal.Save(globalPath);
            BSHC_Log.GetInstance().Info("[CrateConfigManager] Saved default global_settings.json");
        }

        if (!FileExist(staticPath)) {
            ref array<ref CrateSettings> defaultStaticCrates = new array<ref CrateSettings>;
            CrateSettings defaultStaticExample = m_InstanceCrateManagement.CreateDefaultCrateSettings(true, "BS_Hacked_Crate", 1, m_InstanceCrateManagement.CreateDefaultLocationForStatic());
            if (defaultStaticExample) {
                defaultStaticExample.ConfigUniqueID = "DefaultStaticEvent_Example1";
                defaultStaticExample.EnablePlayerNearbyCheck = true; // Valor explícito para el ejemplo
                defaultStaticExample.PlayerNearbyCheckRadius = 15.0; // Valor explícito para el ejemplo
                defaultStaticCrates.Insert(defaultStaticExample);
            }
            JsonFileLoader<array<ref CrateSettings>>.JsonSaveFile(staticPath, defaultStaticCrates);
            BSHC_Log.GetInstance().Info("[CrateConfigManager] Saved default static_crates.json (with one example).");
        }

        if (!FileExist(dynamicPath)) {
            ref array<ref CrateSettings> defaultDynamicCrates = new array<ref CrateSettings>;
            if (m_InstanceCrateManagement) { // Asegurarse que m_InstanceCrateManagement exista
                CrateSettings defaultDynamicExample = m_InstanceCrateManagement.CreateDefaultCrateSettings(false, "BS_Hacked_Crate", 2, m_InstanceCrateManagement.CreateDefaultLocationsForDynamic());
                if (defaultDynamicExample)
                {
                    defaultDynamicExample.ConfigUniqueID = "DefaultDynamicEvent_Example1"; // Asignar un ID de ejemplo
                    defaultDynamicExample.EnablePlayerNearbyCheck = true; // Valor explícito para el ejemplo
                    defaultDynamicExample.PlayerNearbyCheckRadius = 10.0; // Valor explícito para el ejemplo
                    defaultDynamicCrates.Insert(defaultDynamicExample);
                }
            } else {
                 BSHC_Log.GetInstance().Error("[CrateConfigManager] Cannot create default dynamic crate example because m_InstanceCrateManagement is null in SaveDefaultAllConfigs.");
            }
            JsonFileLoader<array<ref CrateSettings>>.JsonSaveFile(dynamicPath, defaultDynamicCrates);
            BSHC_Log.GetInstance().Info("[CrateConfigManager] Saved default dynamic_crates.json (with one example, if creation was successful).");
        }
    }
}
class CrateSpawner
{
    private ref CrateManagement m_CrateManagement;
    private ref array<vector> m_UsedLocationsOnCurrentSpawnPass;
    private ref map<string, int> m_PendingSpawnsByConfigID;

    void CrateSpawner(CrateManagement management)
    {
        m_CrateManagement = management;
        m_UsedLocationsOnCurrentSpawnPass = new array<vector>();
        m_PendingSpawnsByConfigID = new map<string, int>();
        BSHC_Log.GetInstance().Info("CrateSpawner instance created.");
    }
    void UpdateCrateManagement(CrateManagement new_management)
    {
        BSHC_Log.GetInstance().Info("CrateSpawner: CrateManagement settings are being updated live.");
        m_CrateManagement = new_management;
    }
    int CountActiveCratesByConfigID(string configIDToCount)
    {
    int count = 0;
    if (configIDToCount == "") {
        BSHC_Log.GetInstance().Warning("CountActiveCratesByConfigID: configIDToCount is empty. Returning 0.");
        return 0;
    }

    if (g_ActiveHackedCrates)
    {
        for (int i = g_ActiveHackedCrates.Count() - 1; i >= 0; i--)
        {
            HackedCrate_Base crate = g_ActiveHackedCrates.Get(i);
            if (crate)
            {
                if (crate.GetConfigUniqueID() == configIDToCount)
                {
                    count++;
                }
            }
        }
    }
    
    int pendingCount = 0;
    if (m_PendingSpawnsByConfigID.Find(configIDToCount, pendingCount))
    {
        count += pendingCount;
    }

    return count;
    }

    void SetupCrateSpawns()
    {
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Starting SetupCrateSpawns Pass -------------");

        if (m_UsedLocationsOnCurrentSpawnPass)
        {
            m_UsedLocationsOnCurrentSpawnPass.Clear();
        }
        else
        {
            m_UsedLocationsOnCurrentSpawnPass = new array<vector>();
        }

        if (!m_CrateManagement || !m_CrateManagement.CrateConfigs || m_CrateManagement.CrateConfigs.Count() == 0)
        {
            BSHC_Log.GetInstance().Error("CrateSpawner: SetupCrateSpawns - Critical config missing (No CrateConfigs loaded)! Cannot proceed.");
            return;
        }

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        int currentPlayerCount = players.Count();
        BSHC_Log.GetInstance().Info("CrateSpawner: Current server population: " + currentPlayerCount + " players.");

        foreach (CrateSettings specificSettings : m_CrateManagement.CrateConfigs)
        {
            if (!specificSettings)
            {
                BSHC_Log.GetInstance().Warning("CrateSpawner: Null CrateSettings entry in CrateManagement.CrateConfigs. Skipping.");
                continue;
            }

            BSHC_Log.GetInstance().Info("CrateSpawner: Processing ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "' (CrateType: '" + specificSettings.CrateType + "', StaticSpawns flag: " + specificSettings.StaticSpawns + ")");

            int minPlayersForThisCrate = specificSettings.MinPlayersToSpawnCrate;
            if (minPlayersForThisCrate > 0 && currentPlayerCount < minPlayersForThisCrate)
            {
                BSHC_Log.GetInstance().Info("CrateSpawner: Skipping ConfigUniqueID '" + specificSettings.ConfigUniqueID + "'. Players required: " + minPlayersForThisCrate + ", Current: " + currentPlayerCount);
                continue;
            }
            if (minPlayersForThisCrate > 0) BSHC_Log.GetInstance().Info("CrateSpawner: Player check PASSED for ConfigUniqueID '" + specificSettings.ConfigUniqueID + "' (" + currentPlayerCount + "/" + minPlayersForThisCrate + ").");
            else BSHC_Log.GetInstance().Info("CrateSpawner: No min player requirement for ConfigUniqueID '" + specificSettings.ConfigUniqueID + "'.");

            if (specificSettings.StaticSpawns)
            {
                BSHC_Log.GetInstance().Info("CrateSpawner: Handling STATIC for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");
                SpawnStaticCrates(specificSettings);
            }
            else
            {
                BSHC_Log.GetInstance().Info("CrateSpawner: Handling RANDOM for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");
                if (specificSettings.ConfigUniqueID == "") {
                     BSHC_Log.GetInstance().Error("CrateSpawner: ConfigUniqueID for a dynamic crate (CrateType: " + specificSettings.CrateType + ") is EMPTY. Cannot count accurately. Skipping this dynamic config.");
                     continue;
                }

                int existingCratesOfThisConfig = CountActiveCratesByConfigID(specificSettings.ConfigUniqueID);
                BSHC_Log.GetInstance().Info("CrateSpawner: ConfigUniqueID '" + specificSettings.ConfigUniqueID + "' - Existing: " + existingCratesOfThisConfig + ", Target Active: " + specificSettings.ActiveCrateCount);

                if (existingCratesOfThisConfig < specificSettings.ActiveCrateCount)
                {
                    int cratesToSpawnNow = specificSettings.ActiveCrateCount - existingCratesOfThisConfig;
                    BSHC_Log.GetInstance().Info("CrateSpawner: Attempting to spawn " + cratesToSpawnNow + " for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");
                    SpawnRandomCrates(specificSettings, cratesToSpawnNow);
                }
                else
                {
                    BSHC_Log.GetInstance().Info("CrateSpawner: Max ActiveCrateCount for ConfigUniqueID '" + specificSettings.ConfigUniqueID + "' met. No new random spawns.");
                }
            }
        }
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Finished SetupCrateSpawns Pass -------------");
    }
    void SetupInitialStaticCrates()
    {
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Starting IMMEDIATE STATIC Spawn Pass -------------");

        if (!m_CrateManagement || !m_CrateManagement.CrateConfigs) return;

        foreach (CrateSettings specificSettings : m_CrateManagement.CrateConfigs)
        {
            if (specificSettings && specificSettings.StaticSpawns)
            {
                BSHC_Log.GetInstance().Info("CrateSpawner: Processing IMMEDIATE STATIC for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");
                SpawnStaticCrates(specificSettings);
            }
        }
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Finished IMMEDIATE STATIC Spawn Pass -------------");
    }
        void SetupInitialDynamicCrates()
    {
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Starting INITIAL DYNAMIC Spawn Pass (Post-Grace) -------------");

        if (!m_CrateManagement || !m_CrateManagement.CrateConfigs) return;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        int currentPlayerCount = players.Count();
        BSHC_Log.GetInstance().Info("CrateSpawner: Current server population for dynamic spawn: " + currentPlayerCount + " players.");

        foreach (CrateSettings specificSettings : m_CrateManagement.CrateConfigs)
        {
            if (specificSettings && !specificSettings.StaticSpawns)
            {
                BSHC_Log.GetInstance().Info("CrateSpawner: Processing DYNAMIC for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");

                int minPlayersForThisCrate = specificSettings.MinPlayersToSpawnCrate;
                if (minPlayersForThisCrate > 0 && currentPlayerCount < minPlayersForThisCrate)
                {
                    BSHC_Log.GetInstance().Info("CrateSpawner: Skipping ConfigUniqueID '" + specificSettings.ConfigUniqueID + "'. Players required: " + minPlayersForThisCrate + ", Current: " + currentPlayerCount);
                    continue;
                }

                int existingCratesOfThisConfig = CountActiveCratesByConfigID(specificSettings.ConfigUniqueID);
                if (existingCratesOfThisConfig < specificSettings.ActiveCrateCount)
                {
                    int cratesToSpawnNow = specificSettings.ActiveCrateCount - existingCratesOfThisConfig;
                    BSHC_Log.GetInstance().Info("CrateSpawner: Attempting to spawn " + cratesToSpawnNow + " for ConfigUniqueID: '" + specificSettings.ConfigUniqueID + "'.");
                    SpawnRandomCrates(specificSettings, cratesToSpawnNow);
                }
            }
        }
        BSHC_Log.GetInstance().Info("CrateSpawner: ------------- Finished INITIAL DYNAMIC Spawn Pass -------------");
    }
   void SpawnRandomCrates(CrateSettings crateSettings, int numToSpawnThisPass)
   {
    if (!crateSettings) {
        BSHC_Log.GetInstance().Error("SpawnRandomCrates: Null crateSettings. Cannot spawn.");
        return;
    }
    
    BSHC_Log.GetInstance().Info("SpawnRandomCrates: Attempting to spawn " + numToSpawnThisPass + " of type '" + crateSettings.CrateType + "' with ConfigUniqueID '" + crateSettings.ConfigUniqueID + "'.");

    if (!crateSettings.CrateLocations || crateSettings.CrateLocations.Count() == 0) {
        BSHC_Log.GetInstance().Error("SpawnRandomCrates: No CrateLocations defined for CrateType: '" + crateSettings.CrateType + "', ConfigUniqueID '" + crateSettings.ConfigUniqueID + "'. Cannot spawn.");
        return;
    }

    array<ref HCLocation> availableLocations = new array<ref HCLocation>();
    foreach (HCLocation potentialLoc : crateSettings.CrateLocations)
    {
        bool isSpotTaken = false;

        if (g_ActiveHackedCrates)
        {
            foreach(HackedCrate_Base activeCrate : g_ActiveHackedCrates)
            {
                if(activeCrate && vector.Distance(activeCrate.GetPosition(), potentialLoc.GetPosition()) < 5.0)
                {
                    isSpotTaken = true;
                    // Log para depuración: informa qué punto se considera ocupado y por qué
                    BSHC_Log.GetInstance().Info("SpawnRandomCrates: Location " + potentialLoc.GetPosition().ToString() + " is considered occupied by an active crate at " + activeCrate.GetPosition().ToString());
                    break; 
                }
            }
        }

        if (isSpotTaken)
        {
            continue; // Si el punto está ocupado, saltamos al siguiente de la lista
        }

        // 3. Comprobar si ya la hemos usado en esta misma pasada de spawn.
        if (m_UsedLocationsOnCurrentSpawnPass.Find(potentialLoc.GetPosition()) > -1)
        {
            continue; // Saltar si ya fue seleccionado en esta misma ejecución
        }

        availableLocations.Insert(potentialLoc);
    }
    
    BSHC_Log.GetInstance().Info("SpawnRandomCrates: Found " + availableLocations.Count() + " available locations for ConfigUniqueID '" + crateSettings.ConfigUniqueID + "'.");
    

    int spawnedThisPass = 0;
    int attempts = 0;
    int maxAttempts = availableLocations.Count() * 2; // Límite de seguridad

    while (spawnedThisPass < numToSpawnThisPass && attempts < maxAttempts && availableLocations.Count() > 0)
    {
        attempts++;
        
        int randomIndex = Math.RandomInt(0, availableLocations.Count());
        HCLocation randomLocationDef = availableLocations.Get(randomIndex);

        if (!randomLocationDef) {
            BSHC_Log.GetInstance().Warning("SpawnRandomCrates: Could not get a valid random location definition.");
            continue;
        }

        availableLocations.Remove(randomIndex);

        string locName = randomLocationDef.GetLocationName();

        if (crateSettings.WarningTimeMinutes > 0)
        {
            BSHC_Log.GetInstance().Info("CrateSpawner: Sending spawn warning for '" + crateSettings.CrateType + "' at " + locName);
            
            string timeStr = crateSettings.WarningTimeMinutes.ToString();
            
            if (crateSettings.ShowLocationInNotifications)
            {
                GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowWarningNotification", new Param3<string, string, string>(crateSettings.CrateWarningNotification_Key_Located, timeStr, locName), true, null);
            }
            else
            {
                GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleWarningNotification", new Param2<string, string>(crateSettings.CrateWarningNotification_Key, timeStr), true, null);
            }
            
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SpawnCrateAfterWarning, crateSettings.WarningTimeMinutes * 60 * 1000, false, crateSettings, randomLocationDef);
            
            int currentPending = m_PendingSpawnsByConfigID.Get(crateSettings.ConfigUniqueID);
            m_PendingSpawnsByConfigID.Set(crateSettings.ConfigUniqueID, currentPending + 1);
            BSHC_Log.GetInstance().Info("CrateSpawner: Added to pending list for ConfigUniqueID '" + crateSettings.ConfigUniqueID + "'. New pending count: " + (currentPending + 1));
            
            m_UsedLocationsOnCurrentSpawnPass.Insert(randomLocationDef.GetPosition());
            spawnedThisPass++;
        }
        else
        {
            if (crateSettings.EnablePlayerNearbyCheck) {
                if (IsPlayerNearby(randomLocationDef.GetPosition(), crateSettings.PlayerNearbyCheckRadius)) {
                    BSHC_Log.GetInstance().Info("SpawnRandomCrates: Player nearby, skipping spawn for location " + randomLocationDef.GetPosition().ToString());
                    m_UsedLocationsOnCurrentSpawnPass.Insert(randomLocationDef.GetPosition());
                    continue; 
                }
            }

            vector pos = randomLocationDef.GetPosition();
            vector rot = randomLocationDef.GetRotation();
            Object crateObj = SpawnObject(crateSettings.CrateType, pos, rot);
            HackedCrate_Base hc_instance = HackedCrate_Base.Cast(crateObj);

            if (hc_instance) {
                hc_instance.SetCrateSettings_Instance(crateSettings); 
                hc_instance.SetSpawnLocationName(locName); 

                if (crateSettings.UseCrateNotifications) {
                    string key_to_use = crateSettings.CrateSpawnNotification_Key;
                    if (crateSettings.ShowLocationInNotifications)
                    {
                        key_to_use = crateSettings.CrateSpawnNotification_Key_Located;
                    }
                    SendCrateNotification(key_to_use, pos, locName, crateSettings);
                }

               if (crateSettings.SpawnAIOnCrateSpawn)
                {
                SpawnAIAroundCrate(hc_instance);
                }
                
                m_UsedLocationsOnCurrentSpawnPass.Insert(pos);

                if (g_ActiveHackedCrates) {
                    g_ActiveHackedCrates.Insert(hc_instance);
                }
                spawnedThisPass++;
            } else {
                BSHC_Log.GetInstance().Error("SpawnRandomCrates: SpawnObject FAILED to create '" + crateSettings.CrateType + "'.");
            }
        }
      }
   }

    
   void SpawnCrateAfterWarning(CrateSettings crateSettings, HCLocation locationDef)
   {
    int currentPending = m_PendingSpawnsByConfigID.Get(crateSettings.ConfigUniqueID);
    if (currentPending > 0)
    {
        m_PendingSpawnsByConfigID.Set(crateSettings.ConfigUniqueID, currentPending - 1);
    }
    BSHC_Log.GetInstance().Info("SpawnCrateAfterWarning: Timer finished. Spawning crate " + crateSettings.CrateType + ". Removed from pending list. New pending count: " + (currentPending - 1));

    if (crateSettings.EnablePlayerNearbyCheck && !crateSettings.IgnorePlayerCheckOnWarnedSpawn)
    {
        if (IsPlayerNearby(locationDef.GetPosition(), crateSettings.PlayerNearbyCheckRadius))
        {
            BSHC_Log.GetInstance().Warning("SpawnCrateAfterWarning: Player was nearby and IgnorePlayerCheckOnWarnedSpawn is false. Spawn cancelled for " + crateSettings.ConfigUniqueID);
            return;
        }
    }

    // --- LÓGICA DE SPAWN CORREGIDA ---
    vector pos = locationDef.GetPosition();
    vector rot = locationDef.GetRotation();
    string locName = locationDef.GetLocationName();

    Object crateObj = SpawnObject(crateSettings.CrateType, pos, rot);
    HackedCrate_Base hc_instance = HackedCrate_Base.Cast(crateObj);

    if (hc_instance)
    {
        hc_instance.SetCrateSettings_Instance(crateSettings); 
        hc_instance.SetSpawnLocationName(locName); 

        if (crateSettings.UseCrateNotifications && crateSettings.CrateSpawnNotification_Key != "")
        {
            string key_to_use = crateSettings.CrateSpawnNotification_Key;
            if (crateSettings.ShowLocationInNotifications)
            {
                key_to_use = crateSettings.CrateSpawnNotification_Key_Located;
            }
            SendCrateNotification(key_to_use, pos, locName, crateSettings);
        }

        SpawnAIAroundCrate(hc_instance);

        if (g_ActiveHackedCrates)
        {
            g_ActiveHackedCrates.Insert(hc_instance);
        }
    }
    else
      { 
        BSHC_Log.GetInstance().Error("SpawnCrateAfterWarning: Failed to spawn crate object after delay.");
      }
   }

  void SpawnStaticCrates(CrateSettings crateSettings)
  {
    if (!crateSettings || !crateSettings.CrateLocations || crateSettings.CrateLocations.Count() == 0) 
    {
        BSHC_Log.GetInstance().Warning("SpawnStaticCrates: Configuracion invalida o sin localizaciones para ConfigUniqueID: " + crateSettings.ConfigUniqueID);
        return;
    }

    BSHC_Log.GetInstance().Info("SpawnStaticCrates: Procesando " + crateSettings.CrateLocations.Count() + " localizaciones estaticas para ConfigUniqueID: '" + crateSettings.ConfigUniqueID + "'.");

    foreach (HCLocation locationDef : crateSettings.CrateLocations)
    {
        if (!locationDef) continue;

        vector spawnPos = locationDef.GetPosition();
        string locName = locationDef.GetLocationName();
        bool locationIsOccupied = false;

        if (g_ActiveHackedCrates)
        {
            foreach (HackedCrate_Base active_crate : g_ActiveHackedCrates)
            {
                if (active_crate && vector.Distance(active_crate.GetPosition(), spawnPos) < 1.0)
                {
                    // Si encontramos una caja a menos de 1 metro, consideramos el sitio ocupado.
                    locationIsOccupied = true;
                    break;
                }
            }
        }

        if (locationIsOccupied)
        {
            BSHC_Log.GetInstance().Info("SpawnStaticCrates: La ubicación " + spawnPos + " ya está ocupada por una caja activa. Omitiendo.");
            continue;
        }
        
        // Si llegamos aquí, el sitio está libre y podemos proceder.
        BSHC_Log.GetInstance().Info("SpawnStaticCrates: Ubicación " + spawnPos + " está libre. Intentando generar caja.");

        if (crateSettings.EnablePlayerNearbyCheck) {
            if (IsPlayerNearby(spawnPos, crateSettings.PlayerNearbyCheckRadius)) {
                BSHC_Log.GetInstance().Info("SpawnStaticCrates: Omitiendo spawn en " + spawnPos + " por jugador cercano.");
                continue;
            }
        }

        vector rot = locationDef.GetRotation();
        Object crateObj = SpawnObject(crateSettings.CrateType, spawnPos, rot);
        HackedCrate_Base hc_instance = HackedCrate_Base.Cast(crateObj);

        if (hc_instance) 
        {
            hc_instance.SetCrateSettings_Instance(crateSettings);
            hc_instance.SetSpawnLocationName(locName);

            if (crateSettings.UseCrateNotifications && crateSettings.EnableSpawnNotification) {
                string key_to_use = crateSettings.CrateSpawnNotification_Key;
                if (crateSettings.ShowLocationInNotifications)
                    key_to_use = crateSettings.CrateSpawnNotification_Key_Located;
                SendCrateNotification(key_to_use, spawnPos, locName, crateSettings);
            }

            if (crateSettings.SpawnAIOnCrateSpawn)
            {
                SpawnAIAroundCrate(hc_instance);
            }

            if (g_ActiveHackedCrates) {
                 g_ActiveHackedCrates.Insert(hc_instance);
            }
        }
      }
   }
    
    HCLocation GetRandomUnusedLocation(array<ref HCLocation> allConfiguredLocations)
    {
        if (!allConfiguredLocations || allConfiguredLocations.Count() == 0) return null;
        array<ref HCLocation> availableForThisPass = new array<ref HCLocation>();
        for (int i = 0; i < allConfiguredLocations.Count(); i++) {
            if (m_UsedLocationsOnCurrentSpawnPass.Find(allConfiguredLocations.Get(i).GetPosition()) == -1) {
                availableForThisPass.Insert(allConfiguredLocations.Get(i));
            }
        }
        if (availableForThisPass.Count() == 0) return null;
        int randomIndex = Math.RandomInt(0, availableForThisPass.Count());
        return availableForThisPass.Get(randomIndex);
    }
    
    bool IsCrateAlreadyAtLocation(vector position, float radius, string expectedType)
    {
        array<Object> nearbyObjects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(position, radius, nearbyObjects, null);

        for (int i = 0; i < nearbyObjects.Count(); i++)
        {
            Object obj = nearbyObjects.Get(i);
            if (obj && obj.GetType() == expectedType && obj.IsInherited(HackedCrate_Base))
            {
                HackedCrate_Base hc_base = HackedCrate_Base.Cast(obj);
                if (hc_base && !hc_base.IsPendingDespawn())
                {
                    return true;
                }
            }
        }
        return false;
    }

    void SpawnAIAroundCrate(HackedCrate_Base crateInstance)
    {
        if (!crateInstance || !crateInstance.GetCrateSettings()) return;

        CrateSettings settings = crateInstance.GetCrateSettings();
        if (!settings.SpawnAIOnCrateSpawn || settings.AISpawnTypes.Count() == 0 || settings.MaxAIToSpawn <= 0) return;

        vector cratePos = crateInstance.GetPosition();
        int numToSpawn = Math.RandomIntInclusive(settings.MinAIToSpawn, settings.MaxAIToSpawn);

        BSHC_Log.GetInstance().Info("[SpawnAIAroundCrate] They will be generated " + numToSpawn + " IA(s) next to the crate.");

        for (int i = 0; i < numToSpawn; i++)
        {
            string fullAiTypeString = settings.AISpawnTypes.GetRandomElement();
            string aiClassToSpawn = fullAiTypeString;
            bool isExpansionAI = false;
            string expansionParameterString = "";

            #ifdef EXPANSIONMODAI
            if (fullAiTypeString.Contains("|"))
            {
                TStringArray partsFromPipeSplit = new TStringArray;
                fullAiTypeString.Split("|", partsFromPipeSplit);

                if (partsFromPipeSplit.Count() > 1)
                {
                    aiClassToSpawn = partsFromPipeSplit[0]; // El nombre de la clase es la primera parte
                    expansionParameterString = partsFromPipeSplit[1]; // Los parámetros son la segunda parte
                    isExpansionAI = true;
                    BSHC_Log.GetInstance().Info("[SpawnAIAroundCrate] Expansion AI detected. Class: " + aiClassToSpawn + ", Params: " + expansionParameterString);
                }
            }
            #endif

            float randomAngle = Math.RandomFloat(0, Math.PI2);
            float randomRadius = Math.RandomFloat(settings.AISpawnRadiusMin, settings.AISpawnRadiusMax);
            vector spawnPos = cratePos + Vector(randomRadius * Math.Cos(randomAngle), 0, randomRadius * Math.Sin(randomAngle));
            spawnPos[1] = GetGame().SurfaceY(spawnPos[0], spawnPos[2]);
            
            Object aiObject = GetGame().CreateObject(aiClassToSpawn, spawnPos, false, true);

            if (aiObject)
            {
                BSHC_Log.GetInstance().Info("[SpawnAIAroundCrate] Success in generating" + aiClassToSpawn + " in " + spawnPos);
                crateInstance.AddTrackedAI(EntityAI.Cast(aiObject));
                #ifdef EXPANSIONMODAI
                if (isExpansionAI)
                {
                    DayZPlayerImplement aiPlayer = DayZPlayerImplement.Cast(aiObject);
                    if (aiPlayer && expansionParameterString != "")
                    {
                        BSHC_Log.GetInstance().Info("[SpawnAIAroundCrate] Applying Expansion Parameters to AI.");
                        ExpansionObjectSpawnTools.ProcessGear(aiPlayer, expansionParameterString);
                    }
                }
                #endif
            }
            else
            {
                BSHC_Log.GetInstance().Error("[SpawnAIAroundCrate] FAILURE to generate AI with class: " + aiClassToSpawn);
            }
        }
    }
    
    bool IsPlayerNearby(vector position, float radius)
    {
        array<Man> players = {}; 
        GetGame().GetPlayers(players);
        float radiusSq = radius * radius; 

        foreach (Man player : players)
        {
            PlayerBase pb = PlayerBase.Cast(player);
            if (pb && pb.IsAlive() && vector.DistanceSq(pb.GetPosition(), position) <= radiusSq)
            {
                return true; 
            }
        }
        return false; 
    }

    private void SendCrateNotification(string key_to_use, vector pos, string locationName, CrateSettings cs) 
    {
        if (cs && cs.EnableSpawnNotification && key_to_use != "")
        {
            GlobalNotification(key_to_use, locationName, cs); 
        }
    }

    private void GlobalNotification(string messageKey, string locationName, CrateSettings settings) 
    {
        if (!settings) return;

        array<Man> players = {};
        GetGame().GetPlayers(players);
        if (players.Count() == 0) return;

        foreach(Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if(player && player.GetIdentity())
            {
                if (settings.ShowLocationInNotifications)
                {
                    GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowStandardNotification", new Param2<string, string>(messageKey, locationName), true, player.GetIdentity());
                }
                else
                {
                    GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", new Param1<string>(messageKey), true, player.GetIdentity());
                }
            }
        }
        BSHC_Log.GetInstance().Info("CrateSpawner: Standard Notification RPC sent. Key: " + messageKey);
    }
    
    Object SpawnObject(string type, vector position, vector orientation)
    {
        Object obj = GetGame().CreateObjectEx(type, position, ECE_SETUP|ECE_UPDATEPATHGRAPH|ECE_CREATEPHYSICS);
        if (!obj)
        {
            BSHC_Log.GetInstance().Error("SpawnObject Failed: " + type + " at " + position.ToString());
            return null;
        }
        obj.SetPosition(position);
        obj.SetOrientation(orientation);
        obj.Update(); 
        obj.SetAffectPathgraph(true, false);
        if (obj.CanAffectPathgraph())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
        }
        return obj;
    }
}
class HackedCrate_Base extends Container_Base
{
    // --- Variables Miembro ---
    private string m_ConfigUniqueID_Persist;
    bool m_LootAccessActionDone;
    private ref Timer m_CountdownTimer;
    private int HC_CurrentTime;
    private bool m_HasBeenLooted;
    private bool BSHC_TimerStarted;
    private ref OpenableBehaviour m_Openable;
    private ref CrateSettings m_CrateSettings_Instance; 
    private string m_ExpansionMarkerUID = "";
    private string m_LoadedExpansionMarkerUID = "";
    private ref Timer m_MarkerRemovalTimer;
    private float m_MarkerRemovalRemainingTime_Persist;
    private float m_LoadedAutoDespawnRemainingTime;
    private ref Timer m_AutoDespawnTimer;
    private ref Timer m_MaxLifetimeTimer;
    private bool m_IsPendingDespawn;
    private ref Timer m_AIWaveTimer;
    private int m_CurrentAIWaveCount;
    private string m_SpawnLocationName;
    private ref array<EntityAI> m_SpawnedAI;

    #ifdef LBmaster_Groups
    private int m_BSHC_MyAdvancedGroupsMarkerUID = 0;
    #endif

    string lock_locked_tex_path = "BS_HackedCrate\\Rust\\data\\crate\\lock_locked_co.paa"; 
    string lock_unlocked_tex_path = "BS_HackedCrate\\Rust\\data\\crate\\lock_unlocked_co.paa"; 
    void HackedCrate_Base()
    {
        m_Openable = new OpenableBehaviour(false);
        m_ConfigUniqueID_Persist = "";
        RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
        RegisterNetSyncVariableBool("BSHC_TimerStarted");
        RegisterNetSyncVariableInt("HC_CurrentTime");
        RegisterNetSyncVariableBool("m_HasBeenLooted");
        RegisterNetSyncVariableBool("m_LootAccessActionDone");
        RegisterNetSyncVariableBool("m_IsPendingDespawn");
        m_CurrentAIWaveCount = 0;
        m_SpawnedAI = new array<EntityAI>;
        #ifdef LBmaster_Groups
        m_BSHC_MyAdvancedGroupsMarkerUID = 0;
        #endif
    }
    void AddTrackedAI(EntityAI ai_unit)
    {
    if (m_SpawnedAI)
    {
        m_SpawnedAI.Insert(ai_unit);
    }
    }
    string GetConfigUniqueID()
    {
        if (m_CrateSettings_Instance)
            return m_CrateSettings_Instance.ConfigUniqueID;
        return m_ConfigUniqueID_Persist;
    }
    string GetMarkerDisplayName()
    {
        CrateSettings currentSettings = GetCrateSettings();
        if (!currentSettings)
        {
            // 如果没有配置，使用默认值
            return "#STR_BSHC_HackedCrate_DisplayName";
        }
        
        // 如果配置中有自定义名称且不为空，使用它
        if (currentSettings.MarkerDisplayName != "")
        {
            return currentSettings.MarkerDisplayName;
        }
        
        // 否则根据CrateType使用默认字符串键
        string currentCrateType = currentSettings.CrateType;
        if (currentCrateType == "BS_Hacked_Crate")
        {
            return "#STR_BSHC_HackedCrate_DisplayName";
        }
        else if (currentCrateType == "BS_HackedCrateRust")
        {
            return "#STR_BSHC_HackedCrateRust_DisplayName";
        }
        
        // 默认值
        return "#STR_BSHC_HackedCrate_DisplayName";
    }
    static int BSHC_ParseColorFromString(string colorString, string defaultColorString = "255,255,0,0")
    {
    TStringArray colorParts = new TStringArray;
    colorString.Split(",", colorParts);
    if (colorParts.Count() == 4)
    {
        int a = colorParts[0].ToInt();
        int r = colorParts[1].ToInt();
        int g = colorParts[2].ToInt();
        int b = colorParts[3].ToInt();

        a = Math.Clamp(a, 0, 255);
        r = Math.Clamp(r, 0, 255);
        g = Math.Clamp(g, 0, 255);
        b = Math.Clamp(b, 0, 255);

        return ARGB(a, r, g, b);
    }

    BSHC_Log.GetInstance().Warning("BSHC_ParseColorFromString: Invalid color format '" + colorString + "'. Using default color'" + defaultColorString + "'.");
    defaultColorString.Split(",", colorParts);
    if (colorParts.Count() == 4)
    {
        int def_a = colorParts[0].ToInt();
        int def_r = colorParts[1].ToInt();
        int def_g = colorParts[2].ToInt();
        int def_b = colorParts[3].ToInt();
        return ARGB(Math.Clamp(def_a,0,255), Math.Clamp(def_r,0,255), Math.Clamp(def_g,0,255), Math.Clamp(def_b,0,255));
    }

    return ARGB(255, 255, 0, 0); // Rojo
    }
    private void AttemptToReacquireSettings()
    {
        if (m_CrateSettings_Instance) return; 

        string selfType = GetType();
        BSHC_Log.GetInstance().Info("HackedCrate_Base (" + selfType + "): Attempting to re-acquire CrateSettings. Persisted ConfigUniqueID is: '" + m_ConfigUniqueID_Persist + "'");

        CrateManagement staticManager = CrateConfigManager.GetLoadedCrateManagement();
        if (staticManager && staticManager.CrateConfigs)
        {
            if (m_ConfigUniqueID_Persist != "")
            {
                foreach (CrateSettings cs : staticManager.CrateConfigs)
                {
                    if (cs && cs.ConfigUniqueID == m_ConfigUniqueID_Persist)
                    {
                        SetCrateSettings_Instance(cs);
                        BSHC_Log.GetInstance().Info("HackedCrate_Base (" + selfType + "): Successfully re-acquired CrateSettings by persisted ConfigUniqueID '" + cs.ConfigUniqueID + "'.");
                        return;
                    }
                }
                BSHC_Log.GetInstance().Warning("HackedCrate_Base (" + selfType + "): Had a persisted ConfigUniqueID '" + m_ConfigUniqueID_Persist + "' but no matching config was found.");
            }
            else
            {
                BSHC_Log.GetInstance().Info("HackedCrate_Base (" + selfType + "): No persisted ConfigUniqueID. Attempting to find the FIRST DYNAMIC configuration to use as default...");
                foreach (CrateSettings cs_default : staticManager.CrateConfigs)
                {
                    if (cs_default && !cs_default.StaticSpawns)
                    {
                        SetCrateSettings_Instance(cs_default);
                        BSHC_Log.GetInstance().Info("HackedCrate_Base (" + selfType + "): Assigned the first dynamic config found ('" + cs_default.ConfigUniqueID + "') to this manually spawned crate.");
                        return; 
                    }
                }
                BSHC_Log.GetInstance().Warning("HackedCrate_Base (" + selfType + "): Could not find any dynamic configurations to assign as a default.");
            }
        }
        
        BSHC_Log.GetInstance().Info("HackedCrate_Base (" + selfType + "): No persisted ConfigUniqueID found. Settings will be assigned by the spawner.");
    }
    void SetSpawnLocationName(string locName)
    {
        m_SpawnLocationName = locName;
    } 
   void CreateExpansionMapMarker()
   {
    if (!GetGame().IsServer() || !this) {
        BSHC_Log.GetInstance().Error("CreateExpansionMapMarker: Condición inicial no cumplida (No es servidor o 'this' es null).");
        return;
    }

    CrateSettings currentSettings = GetCrateSettings(); 
    if (!currentSettings)
    {
        BSHC_Log.GetInstance().Error("CreateExpansionMapMarker: GetCrateSettings() devolvió NULL. No se pueden leer las opciones del marcador.");
        return;
    }

    if (!currentSettings.UseExpansionMapMarker) {
        BSHC_Log.GetInstance().Info("CreateExpansionMapMarker: Marcadores de Expansion (generales) desactivados para: " + GetType() + " según UseExpansionMapMarker.");
        return; 
    }

    if (!currentSettings.MarkerEnable2D && !currentSettings.MarkerEnable3D)
    {
        BSHC_Log.GetInstance().Info("CreateExpansionMapMarker: Marcadores de Expansion (2D y 3D unificados) específicos desactivados para: " + GetType() + " según MarkerEnable2D/3D.");
        return;
    }

    BSHC_Log.GetInstance().Info("EXP_DEBUG: Dentro de CreateExpansionMapMarker para " + GetType() + ". UseExpansionMapMarker es true.");

    #ifdef EXPANSIONMODNAVIGATION 
        BSHC_Log.GetInstance().Info("EXP_DEBUG: EXPANSIONMODNAVIGATION está definida.");

        ExpansionMarkerModule markerModule;
        if (!CF_Modules<ExpansionMarkerModule>.Get(markerModule))
        {
            BSHC_Log.GetInstance().Error("CreateExpansionMapMarker: CRÍTICO - Falló al obtener ExpansionMarkerModule.");
            return; 
        }

        // 使用GetMarkerDisplayName()从配置获取名称或使用默认值
        string markerName = GetMarkerDisplayName();

        vector markerPos = GetPosition();     
        int markerColor = BSHC_ParseColorFromString(currentSettings.ExpansionMarkerColor);
        bool createAs3D = currentSettings.MarkerEnable3D;

        BSHC_Log.GetInstance().Info("EXP_DEBUG: Intentando crear marcador Expansion con Nombre Clave: '" + markerName + "', Icono: Hacked Crate, Pos: " + markerPos.ToString() + ", Color: " + markerColor + ", Es3D: " + createAs3D);

        ExpansionMarkerData markerData = markerModule.CreateServerMarker(markerName, "Hacked Crate", markerPos, markerColor, createAs3D);

       if (markerData)
       {
           string uid = markerData.GetUID(); //
           BSHC_Log.GetInstance().Info("EXP_DEBUG: UID devuelto por markerData.GetUID(): '" + uid + "'"); //
           SetExpansionMarkerUID(uid); 
           BSHC_Log.GetInstance().Info("EXP_SUCCESS: Creado marcador de Expansion (UID guardado: " + m_ExpansionMarkerUID + ") en " + markerPos.ToString() + " para " + GetType()); //
       }
        else 
        {
            BSHC_Log.GetInstance().Error("EXP_FAIL: Falló al crear marcador de Expansion en " + markerPos.ToString() + ". CreateServerMarker retornó null.");
        }
    #else
        BSHC_Log.GetInstance().Info("EXP_DEBUG: EXPANSIONMODNAVIGATION NO está definida. No se creará marcador de Expansion.");
    #endif 
    }
    void SetExpansionMarkerUID(string uid)
    {
    if (GetGame().IsServer()) 
    {
        BSHC_Log.GetInstance().Info("SetExpansionMarkerUID: Setting m_ExpansionMarkerUID to '" + uid + "' for " + GetType() + "<" + GetID().ToString() + ">");
        m_ExpansionMarkerUID = uid;
       }
   }
    override void EEInit() {
        super.EEInit();

        if (GetGame().IsServer())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartMaxLifetimeTimer, 2000, false);
        }
        
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.DeferredEEInitLogic, 200, false);

        UpdateVisualState();     
        UpdateInventoryLock();   
    }
    void StartMaxLifetimeTimer()
    {
        if (!GetGame().IsServer()) return;

        CrateSettings settings = GetCrateSettings();
        if (settings && !settings.StaticSpawns && settings.MaxLifetimeMinutes_NotTouched > 0)
        {
            float lifetimeInSeconds = settings.MaxLifetimeMinutes_NotTouched * 60;
            
            if (!m_MaxLifetimeTimer)
                m_MaxLifetimeTimer = new Timer();
            
            m_MaxLifetimeTimer.Run(lifetimeInSeconds, this, "DeleteCrate", null, false);
            BSHC_Log.GetInstance().Info(GetType() + " " + GetID() + ": Max lifetime timer started for DYNAMIC crate. Will self-destruct in " + settings.MaxLifetimeMinutes_NotTouched + " minutes if not touched.");
        }
    }
   void DeferredEEInitLogic()
   {
    BSHC_Log.GetInstance().Info("DeferredEEInitLogic: START for " + GetType() + "<" + GetID().ToString() + ">. m_LoadedExpansionMarkerUID (should be from OnStoreLoad) is '" + m_LoadedExpansionMarkerUID + "'. Current m_ExpansionMarkerUID (active) is '" + m_ExpansionMarkerUID + "'");

    CrateSettings currentSettings = GetCrateSettings(); 
    if (!currentSettings) {
        BSHC_Log.GetInstance().Error("DeferredEEInitLogic: CRITICAL - Settings became NULL for " + GetType() + "<" + GetID().ToString() + ">. Aborting deferred logic.");
        return;
    }
    BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Settings acquired successfully for " + GetType() + "<" + GetID().ToString() + ">.");

    if (GetGame().IsServer() && currentSettings.UseExpansionMapMarker) {
        if (m_LoadedExpansionMarkerUID != "") {
            // Caja persistente con UID guardado. Usar ese.
            m_ExpansionMarkerUID = m_LoadedExpansionMarkerUID; 
            BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Using loaded UID '" + m_ExpansionMarkerUID + "' as active m_ExpansionMarkerUID for persistent crate " + GetType() + "<" + GetID().ToString() + ">. No new marker created.");
        } else {
            if (m_ExpansionMarkerUID == "") { // Solo crear si el UID activo aún no se ha establecido.
                 BSHC_Log.GetInstance().Info("DeferredEEInitLogic: m_ExpansionMarkerUID is empty. Calling CreateExpansionMapMarker for " + GetType() + "<" + GetID().ToString() + ">.");
                 CreateExpansionMapMarker(); 
            } else {
                 BSHC_Log.GetInstance().Info("DeferredEEInitLogic: m_ExpansionMarkerUID ('" + m_ExpansionMarkerUID + "') was already set. Not creating new marker for " + GetType() + "<" + GetID().ToString() + ">.");
            }
        }
    }
    
    #ifdef LBmaster_Groups
    if (GetGame().IsServer() && currentSettings.UseAdvancedGroupsMapMarker) {
        BSHC_Log.GetInstance().Info("DeferredEEInitLogic: AG DEBUG for " + GetType() + "<" + GetID().ToString() + ">");
        BSHC_CreateAdvancedGroupsMapMarker();
    }
    #endif

    if (m_HasBeenLooted) { 
        if (!currentSettings.RequireAccessAction) m_LootAccessActionDone = true;
    } else {
         m_LootAccessActionDone = false; 
    }
    BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Final m_LootAccessActionDone for " + GetType() + "<" + GetID().ToString() + "> is: " + m_LootAccessActionDone);
    
    // Reiniciar Timers
    if (GetGame().IsServer() && currentSettings) {
        if (BSHC_TimerStarted && HC_CurrentTime > 0) {
             if (!m_CountdownTimer) m_CountdownTimer = new Timer();
             if (!m_CountdownTimer.IsRunning()) {
                 m_CountdownTimer.Run(1, this, "UpdateDigitsDisplay", null, true);
                 BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Restarted CountdownTimer for " + GetType() + "<" + GetID().ToString() + "> with " + HC_CurrentTime + "s remaining.");
             }
        }
        
        if (m_IsPendingDespawn && m_LoadedAutoDespawnRemainingTime > 0) {
            StartAutoDespawnTimer(m_LoadedAutoDespawnRemainingTime);
        } else if (m_IsPendingDespawn && m_LoadedAutoDespawnRemainingTime <= 0 && m_HasBeenLooted) {
            BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Crate " + GetType() + "<" + GetID().ToString() + "> was pending despawn, timer expired, and was looted. Deleting now.");
            DeleteCrate(); 
            return; 
        }

        if (m_HasBeenLooted && m_ExpansionMarkerUID != "" && m_MarkerRemovalRemainingTime_Persist > 0 && currentSettings.UseExpansionMapMarker) {
            BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Rescheduling Expansion marker (UID: " + m_ExpansionMarkerUID + ") removal in " + m_MarkerRemovalRemainingTime_Persist + "s for " + GetType() + "<" + GetID().ToString() + ">");
            if (!m_MarkerRemovalTimer) m_MarkerRemovalTimer = new Timer(CALL_CATEGORY_SYSTEM);
            if (m_MarkerRemovalTimer.IsRunning()) m_MarkerRemovalTimer.Stop();
            m_MarkerRemovalTimer.Run(m_MarkerRemovalRemainingTime_Persist, this, "ScheduleRemoveExpansionMarker_FromTimer", null, false);
        } else if (m_HasBeenLooted && m_ExpansionMarkerUID != "" && m_MarkerRemovalRemainingTime_Persist <= 0 && currentSettings.UseExpansionMapMarker) {
            BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Looted crate " + GetType() + "<" + GetID().ToString() + "> marker (UID: " + m_ExpansionMarkerUID + ") removal timer had expired/not set. Attempting removal now.");
            RemoveExpansionMapMarker("DeferredEEInitImmediate");
        }
    }
    
    UpdateVisualState();      
    UpdateInventoryLock();  
    BSHC_Log.GetInstance().Info("DeferredEEInitLogic: FINISHED for " + GetType() + "<" + GetID().ToString() + ">");
    if (g_ActiveHackedCrates && g_ActiveHackedCrates.Find(this) == -1)
    {
        g_ActiveHackedCrates.Insert(this);
        BSHC_Log.GetInstance().Info("DeferredEEInitLogic: Re-added persistent crate " + GetType() + " to g_ActiveHackedCrates list.");
    }
   }
   #ifdef LBmaster_Groups
   void BSHC_CreateAdvancedGroupsMapMarker()
   {
    BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: BSHC_CreateAdvancedGroupsMapMarker call.");

    CrateSettings currentSettings = GetCrateSettings(); 
    if (!currentSettings)
    {
        BSHC_Log.GetInstance().Error("BSHC_AG_DEBUG: No se pudo obtener CrateSettings.");
        return;
    }

    // Comprobación general para marcadores de Advanced Groups
    if (!currentSettings.UseAdvancedGroupsMapMarker)
    {
        BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Marcadores AG (generales) desactivados para: " + GetType() + " según UseAdvancedGroupsMapMarker.");
        return;
    }

    if (!currentSettings.MarkerEnable2D && !currentSettings.MarkerEnable3D)
    {
        BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Marcadores AG (2D y 3D unificados) específicos desactivados para: " + GetType() + " según MarkerEnable2D/3D.");
        return;
    }

    if (m_BSHC_MyAdvancedGroupsMarkerUID != 0) {
         BSHC_Log.GetInstance().Warning("BSHC_AG_DEBUG: Marcador AG ya existe (UID: " + m_BSHC_MyAdvancedGroupsMarkerUID + "). No se creará uno nuevo."); //
         return;
    }

    string markerName = GetMarkerDisplayName();


    vector markerPos = GetPosition();
    string iconPath = "BS_HackedCrate/gui/iconcrate.paa";
    int color = BSHC_ParseColorFromString(currentSettings.AdvancedGroupsMarkerColor);

    BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Final Name of the Marker: '" + markerName + "'");

    bool showOnMap = currentSettings.MarkerEnable2D;
    bool showInWorld = currentSettings.MarkerEnable3D;

    BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Trying to create AG marker with name: " + markerName + ", Pos: " + markerPos.ToString() + ", Icon: " + iconPath + ", Color: " + color + ", ShowOnMap: " + showOnMap + ", ShowInWorld: " + showInWorld );

    if (LBStaticMarkerManager && LBStaticMarkerManager.Get) 
    {
        BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: LbstaticMarkerMerMer.get is accessible.");
        LBServerMarker serverMarker = LBStaticMarkerManager.Get.AddTempServerMarker(markerName, markerPos, iconPath, color, showOnMap, showInWorld);

        if (serverMarker)
        {
            m_BSHC_MyAdvancedGroupsMarkerUID = serverMarker.uid; //
            BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Created AG marker (UID: " + m_BSHC_MyAdvancedGroupsMarkerUID + ") for " + GetType()); //
        } else {
            //BSHC_Log.GetInstance().Error("BSHC_AG_DEBUG: Falló AddTempServerMarker (retornó null)");
        }
      } else {
        //BSHC_Log.GetInstance().Error("BSHC_AG_DEBUG: LBStaticMarkerManager o su instancia Get NO es accesible.");
      }
   } 
    void BSHC_RemoveAdvancedGroupsMapMarker()
    {
        BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: BSHC_RemoveAdvancedGroupsMapMarker called.");
        if (m_BSHC_MyAdvancedGroupsMarkerUID != 0)
        {
            BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: Eliminating AG UID marker: " + m_BSHC_MyAdvancedGroupsMarkerUID);
            if (LBStaticMarkerManager && LBStaticMarkerManager.Get)
            {
                bool success = LBStaticMarkerManager.Get.RemoveServerMarker(m_BSHC_MyAdvancedGroupsMarkerUID);
                if (success) {
                     BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: AG UID Marker" + m_BSHC_MyAdvancedGroupsMarkerUID + " successfully eliminated.");
                } else {
                     BSHC_Log.GetInstance().Warning("BSHC_AG_DEBUG: The elimination of MARKER agu uid failed " + m_BSHC_MyAdvancedGroupsMarkerUID + " From the manager.");
                }
            } else {
                BSHC_Log.GetInstance().Error("BSHC_AG_DEBUG: LBSTATICMARKERMERER or GET not accessible to eliminate marker.");
            }
            m_BSHC_MyAdvancedGroupsMarkerUID = 0; 
        } else {
            BSHC_Log.GetInstance().Info("BSHC_AG_DEBUG: There is no AG marker UID to eliminate.");
        }
    }
    #endif 
    bool IsPendingDespawn() 
    {
        return m_IsPendingDespawn;
    }
   void RemoveExpansionMapMarker(string callContext = "UnknownContext")
   {
    if (!GetGame().IsServer()) return;

    BSHC_Log.GetInstance().Info("EXP_REMOVE_DEBUG: Attempting RemoveExpansionMapMarker. Context: " + callContext + ". Current UID: '" + m_ExpansionMarkerUID + "' for " + GetType() + "<" + GetID().ToString() + ">");

    #ifdef EXPANSIONMODNAVIGATION //
        if (m_ExpansionMarkerUID != "")
        {
            ExpansionMarkerModule markerModule;
            if (!CF_Modules<ExpansionMarkerModule>.Get(markerModule))
            {
                 BSHC_Log.GetInstance().Error("EXP_REMOVE_DEBUG: Failed to get ExpansionMarkerModule for removal. Context: " + callContext + " for " + GetType() + "<" + GetID().ToString() + ">");
                 return; // Importante salir si no se puede obtener el módulo
            }
            BSHC_Log.GetInstance().Info("EXP_REMOVE_DEBUG: Calling markerModule.RemoveServerMarker with UID: '" + m_ExpansionMarkerUID + "'. Context: " + callContext + " for " + GetType() + "<" + GetID().ToString() + ">");
            markerModule.RemoveServerMarker(m_ExpansionMarkerUID); 
            BSHC_Log.GetInstance().Info("EXP_REMOVE_SUCCESS: Call to RemoveServerMarker performed. Marker should be removed. Context: " + callContext + " for " + GetType() + "<" + GetID().ToString() + ">");
        }
        else
        {
            BSHC_Log.GetInstance().Info("EXP_REMOVE_DEBUG: No m_ExpansionMarkerUID to remove. Context: " + callContext + " for " + GetType() + "<" + GetID().ToString() + ">");
        }
    #else
        BSHC_Log.GetInstance().Info("EXP_REMOVE_DEBUG: EXPANSIONMODNAVIGATION NOT defined. Cannot remove marker. Context: " + callContext + " for " + GetType() + "<" + GetID().ToString() + ">");
    #endif
    }
    void ScheduleRemoveExpansionMarker_FromTimer()
    {
    if (!GetGame().IsServer()) return;
    BSHC_Log.GetInstance().Info("ScheduleRemoveExpansionMarker_FromTimer: Timer expired for " + GetType() + "<" + GetID().ToString() + ">. Calling RemoveExpansionMapMarker.");
    RemoveExpansionMapMarker("MarkerRemovalTimer");
    }
    void SetTimerStarted(bool state) 
    { 
        if (BSHC_TimerStarted != state) 
        { 
            BSHC_TimerStarted = state; 
            SetSynchDirty(); 
        } 
    }
    bool IsTimerStarted() 
    { 
        return BSHC_TimerStarted; 
    }
    void SetHasBeenLooted(bool state) 
    {
         if (m_HasBeenLooted != state) { m_HasBeenLooted = state; if (GetGame().IsServer()) 
            SetSynchDirty(); } 
    }
    bool HasBeenLooted() 
    { 
        return m_HasBeenLooted; 
    }
   CrateSettings GetCrateSettings()
    {
    if (!m_CrateSettings_Instance) {
        BSHC_Log.GetInstance().Info("GetCrateSettings: m_CrateSettings_Instance is NULL for " + GetType() + "<" + GetID().ToString() + ">. Calling AttemptToReacquireSettings().");
        AttemptToReacquireSettings();
    }
    if (!m_CrateSettings_Instance) {
        BSHC_Log.GetInstance().Error("GetCrateSettings: m_CrateSettings_Instance is STILL NULL after AttemptToReacquireSettings() for " + GetType() + "<" + GetID().ToString() + ">.");
    }
       return m_CrateSettings_Instance;
    }
    int Digits(int number, int divisor)
    {
         if (divisor <= 0) return 0; 
         if (number < 0) number = 0;  
         if (divisor == 1) return number % 10;       
         if (divisor == 10) return (number / 10) % 10; 
         return 0; 
    }
    string GetDigitTexturePath(int digit)
    {
        if (digit < 0 || digit > 9)
        {
             return "BS_HackedCrate\\data\\reset.paa";
        }
        return string.Format("BS_HackedCrate\\data\\%1.paa", digit);
    }
    string GetSpacerTexturePath()
    {
        return "BS_HackedCrate\\data\\Colon.paa";
    }
    void SetInitialDisplayState()
    {
        SetObjectTexture(0, GetDigitTexturePath(0)); 
        SetObjectTexture(1, GetDigitTexturePath(0)); 
        SetObjectTexture(2, GetSpacerTexturePath()); 
        SetObjectTexture(3, GetDigitTexturePath(0)); 
        SetObjectTexture(4, GetDigitTexturePath(0)); 
    }
    void SetFinalDisplayState()
    {
        SetObjectTexture(0, "BS_HackedCrate\\Data\\D.paa"); 
        SetObjectTexture(1, "BS_HackedCrate\\Data\\O.paa"); 
        SetObjectTexture(2, "BS_HackedCrate\\data\\Colon.paa"); 
        SetObjectTexture(3, "BS_HackedCrate\\Data\\N.paa"); 
        SetObjectTexture(4, "BS_HackedCrate\\Data\\E.paa"); 
    }
   void SpawnInitialAIGroup()
   {
        if (!GetGame().IsServer())
        {
            return;
        }

        CrateSettings settings = GetCrateSettings();
        if (!settings || !settings.SpawnAIOnHackStart) // Asegurarse de que deba ejecutarse
        {
            return;
        }
        
        BSHC_Log.GetInstance().Info("HackedCrate (" + GetType() + "): Spawning initial AI group on hack start.");

        SpawnAIGroupNearCrate(
            settings.AISpawnTypes, 
            settings.MinAIToSpawn, 
            settings.MaxAIToSpawn, 
            settings.AISpawnRadiusMin, 
            settings.AISpawnRadiusMax, 
            "Initial AI Group",
        );
   }
    void BSHC_StartCountdown()
   {
    if (m_MaxLifetimeTimer && m_MaxLifetimeTimer.IsRunning())
    {
        m_MaxLifetimeTimer.Stop();
        BSHC_Log.GetInstance().Info(GetType() + " " + GetID() + ": Max lifetime timer stopped due to player interaction.");
    }

    CrateSettings currentSettings = GetCrateSettings();
    if (!currentSettings)
    {
        BSHC_Log.GetInstance().Error("BSHC_StartCountdown: Cannot start, CrateSettings are null for " + GetType());
        return;
    }

    if (BSHC_TimerStarted)
    {
        BSHC_Log.GetInstance().Info("BSHC_StartCountdown: BSHC_TimerStarted is already true for " + GetType() + ". Aborting to prevent re-start.");
        return;
    }

    HC_CurrentTime = currentSettings.CountdownTime;

    if (HC_CurrentTime <= 0)
    {
        BSHC_Log.GetInstance().Error("Invalid CountdownTime (<= 0) for " + GetType() + " from its CrateSettings. Value: " + HC_CurrentTime);
        return;
    }

    int initialMinutes = HC_CurrentTime / 60;
    int initialSeconds = HC_CurrentTime % 60;
    SetObjectTexture(0, GetDigitTexturePath(Digits(initialMinutes, 10)));
    SetObjectTexture(1, GetDigitTexturePath(Digits(initialMinutes, 1)));
    SetObjectTexture(2, GetSpacerTexturePath());
    SetObjectTexture(3, GetDigitTexturePath(Digits(initialSeconds, 10)));
    SetObjectTexture(4, GetDigitTexturePath(Digits(initialSeconds, 1)));

    if (GetGame().IsServer())
    {
        if (!m_CountdownTimer) m_CountdownTimer = new Timer();
        else if (m_CountdownTimer.IsRunning()) {
            m_CountdownTimer.Stop();
        }
        m_CountdownTimer.Run(1, this, "UpdateDigitsDisplay", null, true);

        SetTimerStarted(true);
        
        if (currentSettings.EnableMarkerHackingProgress)
        {
        string initialMarkerText = GetMarkerDisplayName() + " - #STR_BSHC_Marker_Hacking 0%";
        BSHC_UpdateExpansionMarkerText(initialMarkerText);
        BSHC_UpdateAdvancedGroupsMarkerText(initialMarkerText);
        }

        if (currentSettings.SpawnAIOnHackStart)
        {
            SpawnInitialAIGroup();
        }

        if (currentSettings.EnableStartNotification) 
        {
            BSHC_GlobalNotification(EHCNotificationType.START, m_SpawnLocationName, currentSettings); 
        }

        if (currentSettings.UseAIWaves && currentSettings.NumberOfAIWaves > 0)
        {
            m_CurrentAIWaveCount = 0;
            if (m_AIWaveTimer && m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop();
            if (!m_AIWaveTimer) m_AIWaveTimer = new Timer(CALL_CATEGORY_GAMEPLAY);

            float initialDelay = currentSettings.AIWaveInitialDelaySeconds;
            if (initialDelay <= 0)
            {
                ProcessNextAIWave();
            }
            else
            {
                m_AIWaveTimer.Run(initialDelay, this, "ProcessNextAIWave", null, false);
                BSHC_Log.GetInstance().Info(string.Format("HackedCrate %1: First AI wave scheduled in %2 seconds.", GetType(), initialDelay));
            }
        }
      }
   }
   void UpdateDigitsDisplay()
   {
    if (!BSHC_TimerStarted)
    {
        if (m_CountdownTimer && m_CountdownTimer.IsRunning())
        {
            m_CountdownTimer.Stop();
        }
        return;
    }
    if (HC_CurrentTime > 0)
    {
        int remainingMinutes = HC_CurrentTime / 60;
        int remainingSeconds = HC_CurrentTime % 60;

        SetObjectTexture(0, GetDigitTexturePath(Digits(remainingMinutes, 10)));
        SetObjectTexture(1, GetDigitTexturePath(Digits(remainingMinutes, 1)));
        SetObjectTexture(2, GetSpacerTexturePath());
        SetObjectTexture(3, GetDigitTexturePath(Digits(remainingSeconds, 10)));
        SetObjectTexture(4, GetDigitTexturePath(Digits(remainingSeconds, 1)));

        if (GetGame().IsServer())
        {
            CrateSettings settings = GetCrateSettings();
            if (settings && settings.EnableMarkerHackingProgress)
            {
                // La condición ahora usa un valor fijo de 5 segundos en lugar de leerlo de la config.
                if (HC_CurrentTime % 5 == 0)
                {
                    if (settings.CountdownTime > 0)
                    {
                        float totalTime = settings.CountdownTime;
                        float timeElapsed = totalTime - HC_CurrentTime;
                        int percentage = Math.Round((timeElapsed / totalTime) * 100);
                        
                        string markerText = GetMarkerDisplayName() + " - #STR_BSHC_Marker_Hacking " + percentage + "%";
                        BSHC_UpdateExpansionMarkerText(markerText);
                        BSHC_UpdateAdvancedGroupsMarkerText(markerText);
                    }
                }
            }

            HC_CurrentTime--;
            SetSynchDirty();
            GetRPCManager().SendRPC("BS_HackedCrate", "BSHC_PlaySoundOnClientObject", new Param1<string>("BastardosOpenBSHC_SoundSet"), true, null, this);
        }
    }
    else 
    {
        if (GetGame().IsServer())
        {
            if (m_CountdownTimer && m_CountdownTimer.IsRunning())
            {
                m_CountdownTimer.Stop();
            }

            if (BSHC_TimerStarted) 
            {
                SetTimerStarted(false);

                CrateSettings endSettings = GetCrateSettings();
                if (endSettings && endSettings.EnableMarkerUnlockedStatus)
                {
               string unlockedMarkerText = GetMarkerDisplayName() + " - #STR_BSHC_Marker_Unlocked";
               BSHC_UpdateExpansionMarkerText(unlockedMarkerText);
               BSHC_UpdateAdvancedGroupsMarkerText(unlockedMarkerText);
                }
                
                UnlockAndSpawnHCLoot();

                GetRPCManager().SendRPC("BS_HackedCrate", "BSHC_PlaySoundOnClientObject", new Param1<string>("BastardosFinishBSHC_SoundSet"), true, null, this);

                CrateSettings settingsForEndNotification = GetCrateSettings();
                if (settingsForEndNotification && settingsForEndNotification.EnableEndNotification)
                {
                    BSHC_GlobalNotification(EHCNotificationType.END, m_SpawnLocationName, settingsForEndNotification);
                }
                BSHC_Log.GetInstance().Info("Hack finished: " + GetType() + " at " + GetPosition().ToString());
            }
        }
        SetFinalDisplayState(); 
       }
    }
    private void SpawnAIGroupNearCrate(array<string> aiTypesToSpawnFromArgument, int minAICountFromArgument, int maxAICountFromArgument, float minRadiusFromArgument, float maxRadiusFromArgument, string logPrefix = "AI Spawn")
    {
    if (!GetGame().IsServer()) return;

    CrateSettings currentSettings = GetCrateSettings();
    if (!currentSettings) return;

    if (!aiTypesToSpawnFromArgument || aiTypesToSpawnFromArgument.Count() == 0 || maxAICountFromArgument <= 0) return;

    vector cratePos = GetPosition();
    int numToSpawn = Math.RandomIntInclusive(minAICountFromArgument, maxAICountFromArgument);

    BSHC_Log.GetInstance().Info(string.Format("%1 (%2): Attempting to spawn %3 AI(s)", logPrefix, GetType(), numToSpawn));

    for (int i = 0; i < numToSpawn; i++)
    {
        string fullAiTypeString = aiTypesToSpawnFromArgument.GetRandomElement();
        string aiClassToSpawn = fullAiTypeString;
        bool isExpansionAI = false;
        string expansionParameterString = "";

       #ifdef EXPANSIONMODAI
        if (fullAiTypeString.Contains("|"))
        {
            TStringArray partsFromPipeSplit = new TStringArray;
            fullAiTypeString.Split("|", partsFromPipeSplit);

            if (partsFromPipeSplit.Count() > 0)
            {
                aiClassToSpawn = partsFromPipeSplit[0];
                isExpansionAI = true;

                if (partsFromPipeSplit.Count() > 1 && partsFromPipeSplit[1] != "")
                {
                    expansionParameterString = partsFromPipeSplit[1];
                }
            }
        }
        #endif

        // --- LÓGICA DE POSICIÓN CORREGIDA ---
        float randomAngle = Math.RandomFloat(0, Math.PI2);
        float randomDist = Math.RandomFloat(minRadiusFromArgument, maxRadiusFromArgument);
        float offsetX = randomDist * Math.Cos(randomAngle);
        float offsetZ = randomDist * Math.Sin(randomAngle);
        vector spawnPos = cratePos + Vector(offsetX, 0, offsetZ);
        spawnPos[1] = GetGame().SurfaceY(spawnPos[0], spawnPos[2]);
        // --- FIN DE LA CORRECCIÓN ---

        Object aiObjectVanilla = GetGame().CreateObject(aiClassToSpawn, spawnPos, false, true);

        if (aiObjectVanilla)
        {
            m_SpawnedAI.Insert(EntityAI.Cast(aiObjectVanilla));

        #ifdef EXPANSIONMODAI
            if (isExpansionAI)
            {
                DayZPlayerImplement aiPlayer = DayZPlayerImplement.Cast(aiObjectVanilla);
                if (aiPlayer && expansionParameterString != "") {
                    ExpansionObjectSpawnTools.ProcessGear(aiPlayer, expansionParameterString);
                }
            }
        #endif
        }
        else
        {
            BSHC_Log.GetInstance().Error(string.Format("[%1 SPAWN_AI_FAILURE %2] CreateObject FAILED for class name '%3' at %4.", logPrefix.ToUpper(), GetType(), aiClassToSpawn, spawnPos.ToString()));
        }
       }
    }
    void ProcessNextAIWave()
    {
    CrateSettings currentSettings = GetCrateSettings();
    if (!currentSettings)
    {
        BSHC_Log.GetInstance().Error("ProcessNextAIWave (" + GetType() + "): Cannot process, CrateSettings are null.");
        if (m_AIWaveTimer && m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop(); // Detener timer si hay error
        return;
    }

    if (!GetGame().IsServer() || !currentSettings.UseAIWaves || BSHC_TimerStarted == false)
    {
        if (m_AIWaveTimer && m_AIWaveTimer.IsRunning())
        {
            m_AIWaveTimer.Stop();
            BSHC_Log.GetInstance().Info("ProcessNextAIWave (" + GetType() + "): AI Wave timer stopped due to conditions not met (Not server, UseAIWaves false, or main timer not started).");
        }
        return;
    }

    if (m_CurrentAIWaveCount < currentSettings.NumberOfAIWaves)
    {
        BSHC_Log.GetInstance().Info(string.Format("HackedCrate %1: Spawning AI Wave %2/%3", GetType(), m_CurrentAIWaveCount + 1, currentSettings.NumberOfAIWaves));
        
        SpawnAIGroupNearCrate(currentSettings.AIWaveSpawnTypes,
                              currentSettings.MinAIToSpawnPerWave,
                              currentSettings.MaxAIToSpawnPerWave,
                              currentSettings.AIWaveSpawnRadiusMin,
                              currentSettings.AIWaveSpawnRadiusMax,
                              "AI Wave"); 

        m_CurrentAIWaveCount++;
        if (m_CurrentAIWaveCount < currentSettings.NumberOfAIWaves)
        {
            if (!m_AIWaveTimer) m_AIWaveTimer = new Timer(CALL_CATEGORY_GAMEPLAY); 

            if (m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop();

            m_AIWaveTimer.Run(currentSettings.TimeBetweenAIWavesSeconds, this, "ProcessNextAIWave", null, false);
            BSHC_Log.GetInstance().Info(string.Format("HackedCrate %1: Next AI wave scheduled in %2 seconds.", GetType(), currentSettings.TimeBetweenAIWavesSeconds));
        }
        else
        {
            BSHC_Log.GetInstance().Info(string.Format("HackedCrate %1: All %2 AI waves spawned.", GetType(), currentSettings.NumberOfAIWaves));
            if (m_AIWaveTimer && m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop(); 
        }
    }
    else 
    {
        BSHC_Log.GetInstance().Info("ProcessNextAIWave (" + GetType() + "): Max AI waves already spawned or condition met to stop.");
        if (m_AIWaveTimer && m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop();
      }
    }
   void UnlockAndSpawnHCLoot()
   {
       if (!GetGame().IsServer()) return;

       CrateSettings currentCrateSettings = GetCrateSettings();

       if (!currentCrateSettings)
       {
           BSHC_Log.GetInstance().Error("UnlockAndSpawnHCLoot (" + GetType() + "): CRITICAL - Cannot unlock/spawn loot, CrateSettings are null!");
           if (m_Openable && !m_Openable.IsOpened()) {
                m_Openable.Open();
           }
           UpdateVisualState();
           SetFinalDisplayState();

           SetHasBeenLooted(true);
           m_LootAccessActionDone = true;
           GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
           HandlePostLootTimersAndDespawn();
           return;
       }

       if (m_Openable && !m_Openable.IsOpened()) {
           m_Openable.Open();
       }
       UpdateVisualState();
       SetFinalDisplayState();

       SetHasBeenLooted(true);

       if (currentCrateSettings.RequireAccessAction) {
           m_LootAccessActionDone = false;
           BSHC_Log.GetInstance().Info("Crate " + GetType() + " requires access action (RequireAccessAction: true). Loot access pending.");
       } else {
           m_LootAccessActionDone = true;
           BSHC_Log.GetInstance().Info("Crate " + GetType() + " does NOT require access action (RequireAccessAction: false). Loot will be accessible immediately after spawn.");
       }

       if (GetGame().IsServer()) {
           SetSynchDirty();
       }

       BSHC_Log.GetInstance().Info("Unlocking crate & attempting to spawn loot at " + GetPosition().ToString() + " for crate type: " + GetType());

       if (m_AIWaveTimer && m_AIWaveTimer.IsRunning())
       {
           m_AIWaveTimer.Stop();
           BSHC_Log.GetInstance().Info(string.Format("HackedCrate %1: AI wave system stopped due to crate unlock.", GetType()));
       }
         
       bool useNativeLoot = true; 

       #ifdef LBmaster_Rework
       if (currentCrateSettings.lb_preset_name != "")
       {
           useNativeLoot = false; // Desactivamos el loot nativo por ahora.
           BSHC_Log.GetInstance().Info(string.Format(" -> Detected LBmaster preset. Spawning '%1'...", currentCrateSettings.lb_preset_name));

           TStringArray presetsToSpawn = new TStringArray();
           presetsToSpawn.Insert(currentCrateSettings.lb_preset_name);

           array<LB_PresetBase> foundPresets = LB_PresetLoader.Get.FindPresets(presetsToSpawn);

           if (foundPresets && foundPresets.Count() > 0)
           {
               GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT); 
               LB_PresetBase.SpawnPresets(null, foundPresets, this);
               BSHC_Log.GetInstance().Info(string.Format(" -> Successfully spawned LBmaster preset '%1' into crate.", currentCrateSettings.lb_preset_name));
           }
           else
           {
               BSHC_Log.GetInstance().Error(string.Format(" -> ERROR: LBmaster preset '%1' not found in LootPresets.json! Falling back to native loot system.", currentCrateSettings.lb_preset_name));
               useNativeLoot = true;
           }
       }
       #endif

       if (useNativeLoot)
       {
           #ifndef LBmaster_Rework
           BSHC_Log.GetInstance().Info(" -> Using native LootCategoriesToUse system.");
           #endif

           ref BSHCLootPoolConfig globalLootConfig = BSHCGlobalConfig.GetConfig();
           if (!globalLootConfig || !globalLootConfig.AllDefinedCategories)
           {
               BSHC_Log.GetInstance().Error("UnlockAndSpawnHCLoot (" + GetType() + "): Global Loot Config (loot_pools.json) or its 'AllDefinedCategories' not found! No loot will be spawned.");
               HandlePostLootTimersAndDespawn();
               return;
           }

           if (!currentCrateSettings.LootCategoriesToUse || currentCrateSettings.LootCategoriesToUse.Count() == 0)
           {
               BSHC_Log.GetInstance().Warning("UnlockAndSpawnHCLoot (" + GetType() + "): No 'LootCategoriesToUse' defined in its CrateSettings. No loot will be spawned from pools.");
               HandlePostLootTimersAndDespawn();
               return;
           }

           GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
           BSHC_Log.GetInstance().Info("Temporarily unlocking inventory for loot spawn for " + GetType());

           BSHC_Log.GetInstance().Info("Spawning loot from JSON pools for crate: " + GetType() + ". Using defined LootCategoriesToUse: " + currentCrateSettings.LootCategoriesToUse.Count() + " categories.");

           foreach (string categoryNameToProcess : currentCrateSettings.LootCategoriesToUse)
           {
               BSHC_Log.GetInstance().Info("Processing category from CrateSettings: '" + categoryNameToProcess + "' for crate " + GetType());
               ref array<ref BSHCLootPool> poolsForThisCategory = globalLootConfig.AllDefinedCategories.Get(categoryNameToProcess);

               if (!poolsForThisCategory || poolsForThisCategory.Count() == 0)
               {
                   BSHC_Log.GetInstance().Warning("  - Category '" + categoryNameToProcess + "' not found in loot_pools.json or it's empty for crate " + GetType() + ". Skipping this category.");
                   continue;
               }

               BSHCLootPool selectedPool = LootScript.GetWeightedRandomLootPool(poolsForThisCategory);
               if (!selectedPool)
               {
                   BSHC_Log.GetInstance().Warning("  - No valid pool selected (or all pools have 0 weight/probability) for category '" + categoryNameToProcess + "' for crate " + GetType() + ". Skipping this category.");
                   continue;
               }

               BSHC_Log.GetInstance().Info("  - Selected Pool: '" + selectedPool.pool_name + "' (Weight/Probability: " + selectedPool.probability + ") for crate " + GetType());
               if (!selectedPool.items || selectedPool.items.Count() == 0)
               {
                   BSHC_Log.GetInstance().Warning("    - Pool '" + selectedPool.pool_name + "' is empty. No items to spawn from this pool for crate " + GetType());
                   continue;
               }

               int poolItemCount = selectedPool.items.Count();
               int minToSpawn = selectedPool.min_items;
               int maxToSpawn = selectedPool.max_items;

               if (minToSpawn < 0) minToSpawn = 0;
               if (maxToSpawn < 0) maxToSpawn = 0;
               if (minToSpawn > maxToSpawn && maxToSpawn > 0) minToSpawn = maxToSpawn;
               if (maxToSpawn == 0) minToSpawn = 0;

               minToSpawn = Math.Clamp(minToSpawn, 0, poolItemCount);
               maxToSpawn = Math.Clamp(maxToSpawn, minToSpawn, poolItemCount);
               
               BSHC_Log.GetInstance().Info("    - Pool Min/Max items for '" + selectedPool.pool_name + "': " + minToSpawn + "/" + maxToSpawn + " (Clamped for pool size " + poolItemCount + ")");
               int countToSpawn = 0;
               if (maxToSpawn > 0)
               {
                   countToSpawn = Math.RandomIntInclusive(minToSpawn, maxToSpawn);
               }
               BSHC_Log.GetInstance().Info("    - Calculated Count To Spawn from this pool '" + selectedPool.pool_name + "': " + countToSpawn);

               if (countToSpawn > 0)
               {
                   array<ref BSHCSpawnDefinition> itemsToSpawn = LootScript.GetWeightedRandomItemDefinitions(selectedPool.items, countToSpawn);
                   BSHC_Log.GetInstance().Info("    - Attempting to spawn " + itemsToSpawn.Count() + " weighted random items from pool '" + selectedPool.pool_name + "':");

                   for (int j = 0; j < itemsToSpawn.Count(); j++)
                   {
                       ref BSHCSpawnDefinition spawnDef = itemsToSpawn[j];
                       if (spawnDef && spawnDef.item_name != "")
                       {
                           BSHC_Log.GetInstance().Info(string.Format("      - Spawning Item %1/%2: %3 (Original Probability in Pool: %4) for crate %5", j + 1, itemsToSpawn.Count(), spawnDef.item_name, spawnDef.probability, GetType()));
                           EntityAI baseItem = GetInventory().CreateInInventory(spawnDef.item_name);
                           if (!baseItem)
                           {
                               BSHC_Log.GetInstance().Warning("        -> Failed to spawn '" + spawnDef.item_name + "' directly in inventory. Trying to spawn nearby on surface...");
                               vector itemPos = GetPosition() + Vector(Math.RandomFloat(-0.3, 0.3), 0.5, Math.RandomFloat(-0.3, 0.3));
                               baseItem = EntityAI.Cast(GetGame().CreateObjectEx(spawnDef.item_name, itemPos, ECE_PLACE_ON_SURFACE));
                           }

                           if (baseItem)
                           {
                               BSHC_Log.GetInstance().Info("        -> Spawned base item OK: " + baseItem.GetType());
                               if (spawnDef.attachments && spawnDef.attachments.Count() > 0)
                               {
                                   BSHC_Log.GetInstance().Info("        -> Attaching items to " + baseItem.GetType() + "...");
                                   foreach (string attachmentClassname : spawnDef.attachments)
                                   {
                                       if (attachmentClassname != "")
                                       {
                                           EntityAI attachedItem = baseItem.GetInventory().CreateAttachment(attachmentClassname);
                                           if (attachedItem)
                                           {
                                               BSHC_Log.GetInstance().Info("          + Attached OK: " + attachmentClassname);
                                           }
                                           else
                                           {
                                               BSHC_Log.GetInstance().Warning("          - Attachment FAILED for: " + attachmentClassname + " to " + baseItem.GetType());
                                           }
                                       }
                                   }
                               }
                           }
                           else
                           {
                               BSHC_Log.GetInstance().Error("        -> Spawn FAILED for base item: " + spawnDef.item_name + " even after trying nearby.");
                           }
                       }
                       else
                       {
                           BSHC_Log.GetInstance().Warning("      - Invalid or empty spawn definition selected by weighted choice from pool '" + selectedPool.pool_name + "'.");
                       }
                   }
               }
               else
               {
                   BSHC_Log.GetInstance().Info("    - Count to spawn is zero. No items processed for pool: " + selectedPool.pool_name);
               }
           }
       }
       
       UpdateInventoryLock();
       
       if (currentCrateSettings.RequireAccessAction) {
            BSHC_Log.GetInstance().Info("Inventory lock state re-evaluated for " + GetType() + ". Should be LOCKED if RequireAccessAction is true and action not yet performed.");
       } else {
            BSHC_Log.GetInstance().Info("Inventory lock state re-evaluated for " + GetType() + ". Should be UNLOCKED if RequireAccessAction is false.");
       }

       BSHC_Log.GetInstance().Info("Loot spawning process finished for crate at " + GetPosition().ToString());
       HandlePostLootTimersAndDespawn();
    }
    void HandlePostLootTimersAndDespawn()
    {

    CrateSettings currentSettings = GetCrateSettings();

    if (!currentSettings)
    {
        BSHC_Log.GetInstance().Error("HandlePostLootTimersAndDespawn (" + GetType() + "): CRITICAL - Cannot handle post-loot timers, CrateSettings are null! Attempting default despawn if possible.");
        return;
    }

    #ifdef EXPANSIONMODNAVIGATION
    if (currentSettings.UseExpansionMapMarker && m_ExpansionMarkerUID != "")
    {
        float delayMarkerRemovalSeconds = Math.RandomFloatInclusive(1200, 1800); // 20-30 minutos
        BSHC_Log.GetInstance().Info("HandlePostLootTimersAndDespawn (" + GetType() + "): Scheduling Expansion marker UID " + m_ExpansionMarkerUID + " removal in " + (delayMarkerRemovalSeconds / 60.0) + " minutes.");

        if (!m_MarkerRemovalTimer) {
            m_MarkerRemovalTimer = new Timer(CALL_CATEGORY_SYSTEM);
        }

        if (m_MarkerRemovalTimer && !m_MarkerRemovalTimer.IsRunning()) { 
            m_MarkerRemovalTimer.Run(delayMarkerRemovalSeconds, this, "RemoveExpansionMapMarker", null, false);
        } else if (m_MarkerRemovalTimer && m_MarkerRemovalTimer.IsRunning()) { 
            BSHC_Log.GetInstance().Warning("HandlePostLootTimersAndDespawn (" + GetType() + "): Expansion Marker removal timer already running!");
        }
    }
    #endif

    #ifdef LBmaster_Groups
    if (currentSettings.UseAdvancedGroupsMapMarker && m_BSHC_MyAdvancedGroupsMarkerUID != 0)
    {
        BSHC_Log.GetInstance().Info("HandlePostLootTimersAndDespawn (" + GetType() + "): Advanced Groups marker (UID: " + m_BSHC_MyAdvancedGroupsMarkerUID + ") will be handled by EEDelete or specific despawn logic.");
    }
    #endif

    int despawnMinutes = currentSettings.AutoDespawnTimeMinutes;
    if (despawnMinutes > 0)
    {
        float despawnSeconds = despawnMinutes * 60.0;
        BSHC_Log.GetInstance().Info("HandlePostLootTimersAndDespawn (" + GetType() + "): Scheduling auto-despawn in " + despawnSeconds + "s (" + despawnMinutes + " minutes).");
        StartAutoDespawnTimer(despawnSeconds);
    }
    else
       {
        BSHC_Log.GetInstance().Info("HandlePostLootTimersAndDespawn (" + GetType() + "): Auto-despawn is disabled (AutoDespawnTimeMinutes <= 0) as per CrateSettings.");
       }
     }
    private void StartAutoDespawnTimer(float timeInSeconds)
    {
        if (!GetGame().IsServer()) return;

        if (m_AutoDespawnTimer) 
        {
            if (m_AutoDespawnTimer.IsRunning())
            {
                m_AutoDespawnTimer.Stop();
            }
        }
        else
        {
            m_AutoDespawnTimer = new Timer(CALL_CATEGORY_SYSTEM); 
        }

        m_AutoDespawnTimer.Run(timeInSeconds, this, "DeleteCrateScheduled", null, false); 
        m_IsPendingDespawn = true;
        SetSynchDirty(); 
        BSHC_Log.GetInstance().Info("StartAutoDespawnTimer: Auto-despawn timer started for " + this + ". Will delete in " + timeInSeconds + "s.");
    }
    void DeleteCrateScheduled()
    {
        if (!GetGame().IsServer()) return;

        BSHC_Log.GetInstance().Info("DeleteCrateScheduled: Auto-despawn timer finished for " + this + ". Deleting crate now.");
        DeleteCrate();
    }
    private void DeleteCrate()
    {
        if (!GetGame().IsServer()) return;

        if (m_CountdownTimer && m_CountdownTimer.IsRunning()) m_CountdownTimer.Stop();
        if (m_MarkerRemovalTimer && m_MarkerRemovalTimer.IsRunning()) m_MarkerRemovalTimer.Stop();
        if (m_AutoDespawnTimer && m_AutoDespawnTimer.IsRunning()) m_AutoDespawnTimer.Stop(); 

        RemoveExpansionMapMarker(); 
        GetGame().ObjectDelete(this);
    }

   override void OnVariablesSynchronized()
   {
    super.OnVariablesSynchronized();
    UpdateVisualState();
    UpdateInventoryLock();

    if (BSHC_TimerStarted && HC_CurrentTime > 0)
    {
        int remainingMinutes = HC_CurrentTime / 60;
        int remainingSeconds = HC_CurrentTime % 60;
        int digit_TM = Digits(remainingMinutes, 10);
        int digit_OM = Digits(remainingMinutes, 1);
        int digit_TS = Digits(remainingSeconds, 10);
        int digit_OS = Digits(remainingSeconds, 1);
        SetObjectTexture(0, GetDigitTexturePath(digit_TM));
        SetObjectTexture(1, GetDigitTexturePath(digit_OM));
        SetObjectTexture(2, GetSpacerTexturePath());      
        SetObjectTexture(3, GetDigitTexturePath(digit_TS));
        SetObjectTexture(4, GetDigitTexturePath(digit_OS));
    }
    // desactive esto para qeu siempre el numero inicial sea 00:00 Y NO 15:00
    /*
    else if (!BSHC_TimerStarted)
    {
         if (m_HasBeenLooted || IsOpen()) 
         {
             SetFinalDisplayState();
         }
         else 
         {
             SetObjectTexture(0, GetDigitTexturePath(0)); 
             SetObjectTexture(1, GetDigitTexturePath(0)); 
             SetObjectTexture(2, GetSpacerTexturePath()); 
             SetObjectTexture(3, GetDigitTexturePath(0)); 
             SetObjectTexture(4, GetDigitTexturePath(0)); 
         }
    }
    */
    else if (!BSHC_TimerStarted) 
    {
         if (m_HasBeenLooted) 
         {
             SetFinalDisplayState(); 
         }
         else 
         {
             SetInitialDisplayState(); 
         }
      }
   }

    void UpdateVisualState() 
    {
        if (IsOpen())
        {
            SetAnimationPhase("lid", 1);
            if (m_HasBeenLooted)
            {
                SetFinalDisplayState(); // Muestra "DONE"
            }
        }
        else // Tapa cerrada
        {
            SetAnimationPhase("lid", 0); // Animación de la tapa

            if (!BSHC_TimerStarted && !m_HasBeenLooted) // Estado inicial antes de hackear
            {
                SetInitialDisplayState(); // Muestra "00:00"
            }
            else if (!BSHC_TimerStarted && m_HasBeenLooted) // Estado después de hackear y lootear, pero cerrado
            {
                SetFinalDisplayState(); // Muestra "DONE" si ya se looteó
            }
        }
    }
    void BSHC_UpdateExpansionMarkerText(string newText)
    {
        #ifdef EXPANSIONMODNAVIGATION
        if (GetGame().IsServer() && m_ExpansionMarkerUID != "")
        {
            ExpansionMarkerModule markerModule;
            if (CF_Modules<ExpansionMarkerModule>.Get(markerModule))
            {
                // Paso 1: Obtener las propiedades actuales de la caja para recrear el marcador
                CrateSettings currentSettings = GetCrateSettings();
                if (!currentSettings) return;

                vector markerPos = GetPosition();
                int markerColor = BSHC_ParseColorFromString(currentSettings.ExpansionMarkerColor);
                bool createAs3D = currentSettings.MarkerEnable3D;

                // Paso 2: Eliminar el marcador antiguo usando su UID guardado
                markerModule.RemoveServerMarker(m_ExpansionMarkerUID);

                // Paso 3: 替换newText中的字符串键为配置的名称
                string markerNameToUse = newText;
                string configMarkerName = GetMarkerDisplayName();
                
                // 如果配置中有自定义名称（不是字符串键），替换文本中的字符串键
                if (configMarkerName.IndexOf("#STR_") != 0)
                {
                    // 配置中有自定义名称，替换文本中的字符串键
                    markerNameToUse.Replace("#STR_BSHC_HackedCrate_DisplayName", configMarkerName);
                    markerNameToUse.Replace("#STR_BSHC_HackedCrateRust_DisplayName", configMarkerName);
                }
                // 如果配置使用的是字符串键，直接使用newText（保持原样）

                // Paso 4: Crear un marcador nuevo con el texto actualizado
                ExpansionMarkerData newMarker = markerModule.CreateServerMarker(markerNameToUse, "Hacked Crate", markerPos, markerColor, createAs3D);

                // Paso 4: (MUY IMPORTANTE) Actualizar nuestro UID con el del nuevo marcador
                if (newMarker)
                {
                    m_ExpansionMarkerUID = newMarker.GetUID();
                    SetSynchDirty(); // Asegurarse de que el nuevo UID se guarde si es necesario
                }
            }
        }
        #endif
    }  
    void BSHC_UpdateAdvancedGroupsMarkerText(string newText)
    {
        #ifdef LBmaster_Groups
        if (GetGame().IsServer() && m_BSHC_MyAdvancedGroupsMarkerUID != 0)
        {
            CrateSettings currentSettings = GetCrateSettings();
            if (!currentSettings || !currentSettings.UseAdvancedGroupsMapMarker) return;

            // Primero, eliminamos el marcador antiguo
            BSHC_RemoveAdvancedGroupsMapMarker();

            // 替换newText中的字符串键为配置的名称
            string markerNameToUse = newText;
            string configMarkerName = GetMarkerDisplayName();
            
            // 如果配置中有自定义名称（不是字符串键），替换文本中的字符串键
            if (configMarkerName.IndexOf("#STR_") != 0)
            {
                // 配置中有自定义名称，替换文本中的字符串键
                markerNameToUse.Replace("#STR_BSHC_HackedCrate_DisplayName", configMarkerName);
                markerNameToUse.Replace("#STR_BSHC_HackedCrateRust_DisplayName", configMarkerName);
            }

            // Ahora, creamos uno nuevo con el texto actualizado
            string iconPath = "BS_HackedCrate/gui/iconcrate.paa";
            int color = BSHC_ParseColorFromString(currentSettings.AdvancedGroupsMarkerColor);
            bool showOnMap = currentSettings.MarkerEnable2D;
            bool showInWorld = currentSettings.MarkerEnable3D;

            if (LBStaticMarkerManager && LBStaticMarkerManager.Get)
            {
                LBServerMarker newServerMarker = LBStaticMarkerManager.Get.AddTempServerMarker(markerNameToUse, GetPosition(), iconPath, color, showOnMap, showInWorld);
                if (newServerMarker)
                {
                    // Guardamos el nuevo UID para la próxima actualización
                    m_BSHC_MyAdvancedGroupsMarkerUID = newServerMarker.uid;
                }
            }
        }
        #endif
    }
   void UpdateInventoryLock()
    { 
    if (IsOpen() && m_LootAccessActionDone)
    {
        GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
        BSHC_Log.GetInstance().Info("Inventory for " + GetType() + " UNLOCKED. IsOpen: " + IsOpen() + " LootAccessActionDone: " + m_LootAccessActionDone);
    }
    else
    {
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
        BSHC_Log.GetInstance().Info("Inventory for " + GetType() + " LOCKED. IsOpen: " + IsOpen() + " LootAccessActionDone: " + m_LootAccessActionDone);
      }
    }

   override void Open()
    {
    if (!IsOpen()) 
    {
        m_Openable.Open(); 
        UpdateVisualState();
        SetFinalDisplayState();
        if (GetGame().IsServer())
        {
            SetSynchDirty();
        }
        BSHC_Log.GetInstance().Info("Crate Visually Opened at " + GetPosition().ToString());
      } 
   }


    override void Close()
    {
        if (IsOpen())
        {
            m_Openable.Close();
            UpdateVisualState();
            UpdateInventoryLock();
            SetObjectTexture(0, GetDigitTexturePath(0));
            SetObjectTexture(1, GetDigitTexturePath(0));
            SetObjectTexture(2, GetDigitTexturePath(0));
            SetObjectTexture(3, GetDigitTexturePath(0));
            if (GetGame().IsServer())
            {
                SetSynchDirty();
            }
            BSHC_Log.GetInstance().Info("Crate Closed at " + GetPosition().ToString());
        }
    }

   override bool IsOpen()
   { 
    if (m_Openable) return m_Openable.IsOpened();
    return false;
   }

    override bool CanDisplayCargo()
    {
        return IsOpen(); 
    }
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);

        ctx.Write(IsOpen());
        ctx.Write(BSHC_TimerStarted);
        ctx.Write(HC_CurrentTime);
        ctx.Write(m_HasBeenLooted);
        ctx.Write(m_LootAccessActionDone);
        ctx.Write(m_ExpansionMarkerUID);
        ctx.Write(m_IsPendingDespawn);
        ctx.Write(m_ConfigUniqueID_Persist); // <--- GUARDAR EL ID DE CONFIG
        ctx.Write(m_SpawnLocationName);

        if (m_AutoDespawnTimer && m_AutoDespawnTimer.IsRunning())
        {
            ctx.Write(m_AutoDespawnTimer.GetRemaining());
        }
        else
        {
            ctx.Write(0.0);
        }

        if (m_MarkerRemovalTimer && m_MarkerRemovalTimer.IsRunning())
        {
            ctx.Write(m_MarkerRemovalTimer.GetRemaining());
        }
        else
        {
            ctx.Write(-1.0);
        }
    }
    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) return false;
        //BSHC_Log.GetInstance().Info("OnStoreLoad: START for " + GetType() + "<" + GetID().ToString() + ">");

        bool opened_state_loaded_temp;
        if (!ctx.Read(opened_state_loaded_temp)) { BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read opened_state_loaded for " + GetType() + "<" + GetID().ToString() + ">"); return false; }

        if (!ctx.Read(BSHC_TimerStarted)) { BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read BSHC_TimerStarted for " + GetType() + "<" + GetID().ToString() + ">"); return false; }
        if (!ctx.Read(HC_CurrentTime)) { BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read HC_CurrentTime for " + GetType() + "<" + GetID().ToString() + ">"); return false; }
        if (!ctx.Read(m_HasBeenLooted)) { BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read m_HasBeenLooted for " + GetType() + "<" + GetID().ToString() + ">"); return false; }

        if (!ctx.Read(m_LootAccessActionDone)) {
            BSHC_Log.GetInstance().Warning("OnStoreLoad: Failed to read m_LootAccessActionDone for " + GetType() + "<" + GetID().ToString() + ">. Defaulting to false. Will be re-evaluated in EEInit.");
            m_LootAccessActionDone = false;
        }

        string loaded_uid;
        if (!ctx.Read(loaded_uid)) {
            loaded_uid = "";
        }
        m_ExpansionMarkerUID = loaded_uid; // Se usará m_LoadedExpansionMarkerUID en EEInit

        if (!ctx.Read(m_IsPendingDespawn)) { BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read m_IsPendingDespawn for " + GetType() + "<" + GetID().ToString() + ">"); m_IsPendingDespawn = false; return false; }

        // Leer m_ConfigUniqueID_Persist
        string loaded_config_id;
        if (!ctx.Read(loaded_config_id)) {
            BSHC_Log.GetInstance().Error("OnStoreLoad: Failed to read m_ConfigUniqueID_Persist for " + GetType() + "<" + GetID().ToString() + ">. Defaulting to empty.");
            m_ConfigUniqueID_Persist = "";
        } else {
            m_ConfigUniqueID_Persist = loaded_config_id;
            BSHC_Log.GetInstance().Info("OnStoreLoad: m_ConfigUniqueID_Persist set from storage to: '" + m_ConfigUniqueID_Persist + "' for " + GetType() + "<" + GetID().ToString() + ">");
        }
        if (!ctx.Read(m_SpawnLocationName)) { // <--- AÑADIR ESTE BLOQUE COMPLETO
            m_SpawnLocationName = "";
        }

        float temp_remaining_despawn_time;
        if (!ctx.Read(temp_remaining_despawn_time)) {
            temp_remaining_despawn_time = 0.0;
        }
        m_LoadedAutoDespawnRemainingTime = temp_remaining_despawn_time;

        if (!ctx.Read(m_MarkerRemovalRemainingTime_Persist)) {
            m_MarkerRemovalRemainingTime_Persist = -1.0;
        }

        if (!m_Openable) {
            m_Openable = new OpenableBehaviour(false);
        }
        if (opened_state_loaded_temp) {
            m_Openable.Open(); 
        }


        BSHC_Log.GetInstance().Info("OnStoreLoad: FINISHED loading raw data into member variables for " + GetType() + "<" + GetID().ToString() + ">");
        return true;
    }
   override void EEDelete(EntityAI parent)
    {
        if (GetGame().IsServer())
        {
            if (m_SpawnedAI && m_SpawnedAI.Count() > 0)
            {
                BSHC_Log.GetInstance().Info("EEDelete (" + GetType() + "): Cleaning up " + m_SpawnedAI.Count() + " referenced AI units...");
                for (int i = 0; i < m_SpawnedAI.Count(); i++)
                {
                    EntityAI ai_unit = m_SpawnedAI.Get(i);
                    if (ai_unit) 
                    {
                        GetGame().ObjectDelete(ai_unit);
                    }
                }
            }
            
            CrateSettings currentSettings = GetCrateSettings(); 

            BSHC_Log.GetInstance().Info("EEDelete called for " + GetType() + " at " + GetPosition());

            if (m_CountdownTimer && m_CountdownTimer.IsRunning()) m_CountdownTimer.Stop();
            if (m_AutoDespawnTimer && m_AutoDespawnTimer.IsRunning()) m_AutoDespawnTimer.Stop();
            if (m_AIWaveTimer && m_AIWaveTimer.IsRunning()) m_AIWaveTimer.Stop();
            if (m_MaxLifetimeTimer && m_MaxLifetimeTimer.IsRunning()) m_MaxLifetimeTimer.Stop();

            RemoveExpansionMapMarker("EEDelete");
            #ifdef LBmaster_Groups
                #ifdef SERVER
                    BSHC_RemoveAdvancedGroupsMapMarker();
                #endif
            #endif

            if (currentSettings && currentSettings.EnableDespawnNotification)
            {
                BSHC_GlobalNotification(EHCNotificationType.DESPAWN, m_SpawnLocationName, currentSettings);
            }
            
            if (g_ActiveHackedCrates) {
                int findIdx = g_ActiveHackedCrates.Find(this);
                if (findIdx != -1) {
                    g_ActiveHackedCrates.Remove(findIdx);
                    BSHC_Log.GetInstance().Info("EEDelete: Removed " + GetType() + " from g_ActiveHackedCrates. Remaining count: " + g_ActiveHackedCrates.Count());
                }
            }
        }

        super.EEDelete(parent);
    }
    override bool CanPutInCargo(EntityAI parent) 
    { 
        return false; 
    } 
    override bool CanPutIntoHands(EntityAI parent) 
    { 
        return false; 
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionOpenBSHC);
        AddAction(ActionAccessLootBSHC); 
    }

    void SetCrateSettings_Instance(CrateSettings settings)
    {
    m_CrateSettings_Instance = settings;
    if (m_CrateSettings_Instance) {
        m_ConfigUniqueID_Persist = m_CrateSettings_Instance.ConfigUniqueID;
        BSHC_Log.GetInstance().Info("HackedCrate_Base (" + GetType() + "): Instance specific CrateSettings assigned. ConfigUniqueID: " + m_ConfigUniqueID_Persist);
        
        SetSynchDirty();
       } else {
        BSHC_Log.GetInstance().Error("HackedCrate_Base (" + GetType() + "): SetCrateSettings_Instance received NULL settings!");
       }
    }


    void BSHC_GlobalNotification(EHCNotificationType notifType, string locationName, CrateSettings settings) 
    {
        if (!settings) 
        {
            BSHC_Log.GetInstance().Error("BSHC_GlobalNotification: Se intentó enviar una notificación sin un objeto de configuración válido.");
            return;
        }

        string key_to_use;

        switch (notifType)
        {
            case EHCNotificationType.START:
                if (settings.ShowLocationInNotifications)
                    key_to_use = settings.CrateStartNotification_Key_Located;
                else
                    key_to_use = settings.CrateStartNotification_Key;
                break;

            case EHCNotificationType.END:
                if (settings.ShowLocationInNotifications)
                    key_to_use = settings.CrateEndNotification_Key_Located;
                else
                    key_to_use = settings.CrateEndNotification_Key;
                break;
            
            case EHCNotificationType.DESPAWN:
                if (settings.ShowLocationInNotifications)
                    key_to_use = settings.CrateDespawnNotification_Key_Located;
                else
                    key_to_use = settings.CrateDespawnNotification_Key;
                break;
        }

        if (key_to_use == "") return;

        BSHC_Log.GetInstance().Info("HackedCrate ("+GetType()+"): Sending RPC Notification. Type: " + typename.EnumToString(EHCNotificationType, notifType) + ", Key: " + key_to_use);

        array<Man> players = {}; 
        GetGame().GetPlayers(players);
        if (players.Count() == 0) return;

        foreach(Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if(player && player.GetIdentity())
            {
                if (settings.ShowLocationInNotifications)
                {
                    GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowStandardNotification", new Param2<string, string>(key_to_use, locationName), true, player.GetIdentity());
                }
                else
                {
                    GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", new Param1<string>(key_to_use), true, player.GetIdentity());
                }
            }
        }
    }
}    

class BS_Hacked_Crate extends HackedCrate_Base
{

    override void UpdateVisualState() 
    {
        super.UpdateVisualState(); 

        int lock_hidden_selection_index_standard = 5;

        if (IsOpen())
        {
            SetObjectTexture(lock_hidden_selection_index_standard, lock_unlocked_tex_path);
            //BSHC_Log.GetInstance().Info("BS_Hacked_Crate: Codelock texture set to UNLOCKED (index 5).");
        }
        else
        {
            SetObjectTexture(lock_hidden_selection_index_standard, lock_locked_tex_path);
            //BSHC_Log.GetInstance().Info("BS_Hacked_Crate: Codelock texture set to LOCKED (index 5).");
        }
    }
};