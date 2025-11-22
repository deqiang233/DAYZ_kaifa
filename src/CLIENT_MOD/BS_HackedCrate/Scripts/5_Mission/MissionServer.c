modded class MissionServer
{
    private ref CrateConfigManager m_BSHC_CrateConfigManager; 
    private ref CrateSpawner m_BSHC_CrateSpawner;         
    private ref BSHC_Log m_BSHCLogger;                    

    private int m_BSHC_ServerStartGracePeriodMinutes;   
    private float m_BSHC_PeriodicTickIntervalSeconds;   
    void MissionServer()
    {
        Print("[BS_HackedCrate MissionServer] Constructor called. Mod system is initializing.");
    }

    CrateConfigManager GetBSHCCrateConfigManager()
    {
        return m_BSHC_CrateConfigManager;
    }
    CrateSpawner GetBSHCCrateSpawner() 
    {
        return m_BSHC_CrateSpawner;
    }

    override void OnInit()
    {
        super.OnInit();

        
        m_BSHCLogger = BSHC_Log.GetInstance("BSHC_MissionServer"); 
        if (!m_BSHCLogger)
        {
            Print("[BS_HackedCrate MissionServer ERROR] CRITICAL: BSHC_Log.GetInstance() returned NULL in OnInit! Logging will fail.");
        }
        else
        {
            m_BSHCLogger.Info("OnInit - Initializing Bastardos Hacked Crates System...");
        }

        if (m_BSHCLogger) m_BSHCLogger.Info("OnInit - Loading Hacked Crate Loot Configuration (loot_pools.json)...");
        
        string lootConfigPath = "$profile:\\Bastardo_HC\\loot_pools.json";
        string configBaseDir = "$profile:\\Bastardo_HC"; 

        if (!FileExist(configBaseDir))
        {
             if (MakeDirectory(configBaseDir))
             {
                 if (m_BSHCLogger) m_BSHCLogger.Info("OnInit - Created main configuration directory: " + configBaseDir);
             }
             else
             {
                 if (m_BSHCLogger) m_BSHCLogger.Error("OnInit - CRITICAL: Failed to create main configuration directory: " + configBaseDir + ". Config loading might fail.");
             }
        }

        ref BSHCLootPoolConfig loadedLootConfig = BSHCLootPoolConfig.Load(lootConfigPath);
        if (loadedLootConfig)
        {
            BSHCGlobalConfig.SetConfig(loadedLootConfig); 
            if (m_BSHCLogger) m_BSHCLogger.Info("OnInit - Hacked Crate Loot Configuration processed successfully.");
        }
        else
        {
             if (m_BSHCLogger) m_BSHCLogger.Error("OnInit - Failed to load or process Hacked Crate Loot Configuration from: " + lootConfigPath + ". Loot functionality might be impaired.");
        }

        if (m_BSHCLogger) m_BSHCLogger.Info("OnInit - Loading Hacked Crate settings (global, static, dynamic)...");
        
        m_BSHC_CrateConfigManager = new CrateConfigManager();
        m_BSHC_CrateConfigManager.LoadOrCreateConfigs();

        CrateManagement crateManagementSettings = m_BSHC_CrateConfigManager.GetCrateManagement();
        if (crateManagementSettings)
        {
            m_BSHC_CrateSpawner = new CrateSpawner(crateManagementSettings);
            
            m_BSHC_ServerStartGracePeriodMinutes = crateManagementSettings.ServerStartGracePeriod;
            m_BSHC_PeriodicTickIntervalSeconds = crateManagementSettings.PeriodicTickIntervalSeconds;

            if (m_BSHC_PeriodicTickIntervalSeconds <= 10) { 
                if (m_BSHCLogger) m_BSHCLogger.Warning("OnInit - PeriodicTickIntervalSeconds from config is very low (" + m_BSHC_PeriodicTickIntervalSeconds + "s). Adjusted to a minimum of 300s (5 minutes).");
                m_BSHC_PeriodicTickIntervalSeconds = 300; 
            }
            if (m_BSHC_ServerStartGracePeriodMinutes < 0) { 
                 if (m_BSHCLogger) m_BSHCLogger.Warning("OnInit - ServerStartGracePeriodMinutes from config is negative (" + m_BSHC_ServerStartGracePeriodMinutes + "). Setting to 0 minutes.");
                m_BSHC_ServerStartGracePeriodMinutes = 0;
            }


            if (m_BSHCLogger) {
                m_BSHCLogger.Info("OnInit - Crate Spawner created. Grace Period: " + m_BSHC_ServerStartGracePeriodMinutes + " minutes. Periodic Tick: " + m_BSHC_PeriodicTickIntervalSeconds + " seconds.");
            }
        }
        else 
        {
            if (m_BSHCLogger) m_BSHCLogger.Error("OnInit - CRITICAL: Failed to retrieve Crate Management settings from CrateConfigManager. Hacked Crate system will likely not function.");
            m_BSHC_CrateSpawner = null; 
            m_BSHC_ServerStartGracePeriodMinutes = 5;  
            m_BSHC_PeriodicTickIntervalSeconds = 3600; 
            if (m_BSHCLogger) {
                m_BSHCLogger.Warning("OnInit - Using hardcoded fallback Grace Period: " + m_BSHC_ServerStartGracePeriodMinutes + " minutes due to critical config load failure.");
                m_BSHCLogger.Warning("OnInit - Using hardcoded fallback Periodic Tick Interval: " + m_BSHC_PeriodicTickIntervalSeconds + " seconds due to critical config load failure.");
            }
        }

        if (m_BSHCLogger) m_BSHCLogger.Info("OnInit - Bastardos Hacked Crates System Initialization sequence finished.");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart(); 

        if (GetGame().IsServer()) 
        {
            if (m_BSHCLogger)
            {
                m_BSHCLogger.Info("OnMissionStart - Server mission started. Scheduling Hacked Crate cleanup and initial spawn setup.");
            }

            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeleteHackedCratesFromKnownLocations, 10000, false);

            if (m_BSHCLogger) m_BSHCLogger.Info("OnMissionStart - Immediate STATIC Crate spawn scheduled in 15 seconds.");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.PerformImmediateStaticSpawn, 15000, false);

            int gracePeriodMillis = m_BSHC_ServerStartGracePeriodMinutes * 60 * 1000;
            int initialDynamicSpawnDelay = gracePeriodMillis + 20000; 
            if (m_BSHCLogger) m_BSHCLogger.Info("OnMissionStart - Initial DYNAMIC Crate spawn scheduled in approx. " + (initialDynamicSpawnDelay / 1000.0) + " seconds.");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.PerformInitialDynamicSpawn, initialDynamicSpawnDelay, false);

            float firstPeriodicTickDelayMs = m_BSHC_PeriodicTickIntervalSeconds * 1000;
            if (m_BSHCLogger) m_BSHCLogger.Info("OnMissionStart - Scheduling first PERIODIC Crate Spawn Tick in approx. " + (firstPeriodicTickDelayMs / 1000.0) + " seconds.");
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.OnCrateSpawnTickPeriodic, firstPeriodicTickDelayMs, false);
        }
    }
    void PerformImmediateStaticSpawn()
    {
        if (!GetGame().IsServer()) return;

        if (m_BSHCLogger) m_BSHCLogger.Info("PerformImmediateStaticSpawn - Calling CrateSpawner to setup STATIC Hacked Crates...");

        if (m_BSHC_CrateSpawner) 
        {
            m_BSHC_CrateSpawner.SetupInitialStaticCrates(); 
        }
        else
        {
            if (m_BSHCLogger) m_BSHCLogger.Error("PerformImmediateStaticSpawn - m_BSHC_CrateSpawner is NULL!");
        }
    }

    void PerformInitialDynamicSpawn()
    {
        if (!GetGame().IsServer()) return;

        if (m_BSHCLogger) m_BSHCLogger.Info("PerformInitialDynamicSpawn - Grace period ended. Calling CrateSpawner to setup initial DYNAMIC Hacked Crates...");

        if (m_BSHC_CrateSpawner) 
        {
            m_BSHC_CrateSpawner.SetupInitialDynamicCrates(); 
        }
        else
        {
            if (m_BSHCLogger) m_BSHCLogger.Error("PerformInitialDynamicSpawn - m_BSHC_CrateSpawner is NULL!");
        }
    }

    void DeleteHackedCratesFromKnownLocations()
    {
        if (!GetGame().IsServer()) return;

        if (!m_BSHC_CrateConfigManager || !m_BSHC_CrateConfigManager.GetCrateManagement())
        {
            if (m_BSHCLogger) m_BSHCLogger.Error("DeleteHackedCratesFromKnownLocations - CrateConfigManager or its CrateManagement data not available. Cannot perform cleanup.");
            return;
        }

        if (m_BSHCLogger) m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - Starting cleanup of Hacked Crates from KNOWN SPAWN LOCATIONS as defined in configurations...");

        array<ref CrateSettings> crateConfigs = m_BSHC_CrateConfigManager.GetCrateManagement().CrateConfigs;
        if (!crateConfigs || crateConfigs.Count() == 0)
        {
            if (m_BSHCLogger) m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - No CrateConfigs found in CrateManagement. No locations to check for cleanup.");
            return;
        }

        int cratesDeletedCount = 0;

        foreach (CrateSettings bs_crateSettings : crateConfigs)
        {
            if (!bs_crateSettings) // MODIFICADO
            {
                BSHC_Log.GetInstance().Warning("DeleteHackedCratesFromKnownLocations: Null CrateSettings entry in CrateManagement.CrateConfigs. Skipping.");
                continue;
            }

            if (!bs_crateSettings || !bs_crateSettings.CrateLocations || bs_crateSettings.CrateLocations.Count() == 0) 
            {
                if (m_BSHCLogger && bs_crateSettings) m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - CrateType '" + bs_crateSettings.CrateType + "' has no CrateLocations defined in its settings. Skipping cleanup for this type."); // MODIFICADO
                continue;
            }

            foreach (HCLocation locDef : bs_crateSettings.CrateLocations) 
            {
                if (!locDef) continue;

                vector spawnPosition = locDef.GetPosition();
                float checkRadius = 1.0; 

                array<Object> foundObjects = new array<Object>();
                array<CargoBase> proxyCargos = new array<CargoBase>(); 

                GetGame().GetObjectsAtPosition3D(spawnPosition, checkRadius, foundObjects, proxyCargos);

                for (int i = 0; i < foundObjects.Count(); i++)
                {
                    Object currentObject = foundObjects.Get(i);
                    if (currentObject && currentObject.IsInherited(HackedCrate_Base) && currentObject.GetType() == bs_crateSettings.CrateType) // MODIFICADO
                    {
                        HackedCrate_Base crateInstance = HackedCrate_Base.Cast(currentObject);
                        if (crateInstance && !crateInstance.IsTimerStarted() && !crateInstance.IsOpen())
                        {
                            if (m_BSHCLogger)
                            {
                                m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - Deleting INACTIVE: " + currentObject.GetType() + " (ID: " + currentObject.GetID() + ") found at configured spawn Pos: " + currentObject.GetPosition().ToString() + " for CrateType " + bs_crateSettings.CrateType); // MODIFICADO
                            }
                            GetGame().ObjectDelete(currentObject);
                            cratesDeletedCount++;
                        } else if (crateInstance) {
                            if (m_BSHCLogger) m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - SKIPPING ACTIVE: " + currentObject.GetType() + " (TimerStarted: " + crateInstance.IsTimerStarted() + ", IsOpen: " + crateInstance.IsOpen() + ") at " + currentObject.GetPosition().ToString());
                        }
                    }
                }
            }
        }

        if (m_BSHCLogger)
        {
            m_BSHCLogger.Info("DeleteHackedCratesFromKnownLocations - Cleanup from known locations finished. Total inactive Hacked Crates (matching type and location) deleted: " + cratesDeletedCount);
        }
    }

    void PerformInitialCrateSpawn()
    {
        if (!GetGame().IsServer()) return;

        if (m_BSHCLogger)
        {
            m_BSHCLogger.Info("PerformInitialCrateSpawn - Grace period ended. Calling CrateSpawner to setup initial Hacked Crates...");
        }

        if (m_BSHC_CrateSpawner) 
        {
            m_BSHC_CrateSpawner.SetupCrateSpawns(); 
        }
        else
        {
            if (m_BSHCLogger)
            {
                m_BSHCLogger.Error("PerformInitialCrateSpawn - m_BSHC_CrateSpawner is NULL! Cannot spawn Hacked Crates. Check OnInit logic and config loading.");
            } else {
                Print("[BS_HackedCrate MissionServer CRITICAL ERROR] PerformInitialCrateSpawn - m_BSHC_CrateSpawner is NULL!");
            }
        }
         if (m_BSHCLogger) m_BSHCLogger.Info("PerformInitialCrateSpawn - Initial crate spawn pass completed.");
    }

    void OnCrateSpawnTickPeriodic() 
    {
        if (!GetGame().IsServer()) return;

        if (m_BSHCLogger)
        {
            m_BSHCLogger.Info("--------------------------------------------------------------------------");
            m_BSHCLogger.Info("OnCrateSpawnTickPeriodic - Tick received. Re-evaluating Hacked Crate spawns...");
            m_BSHCLogger.Info("--------------------------------------------------------------------------");
        }

        if (m_BSHC_CrateSpawner)
        {
            m_BSHC_CrateSpawner.SetupCrateSpawns(); 
        }
        else
        {
            if (m_BSHCLogger)
            {
                m_BSHCLogger.Error("OnCrateSpawnTickPeriodic - m_BSHC_CrateSpawner is NULL! Cannot check/spawn crates periodically.");
            }
        }

        float nextTickDelayMs = m_BSHC_PeriodicTickIntervalSeconds * 1000;
        
       
        if (nextTickDelayMs <= 10000) { 
             if (m_BSHCLogger) m_BSHCLogger.Warning("OnCrateSpawnTickPeriodic - Configured PeriodicTickInterval is very short ("+m_BSHC_PeriodicTickIntervalSeconds+"s). Next tick will be scheduled with this interval. Ensure this is intended.");
             if (nextTickDelayMs <=0) { 
                nextTickDelayMs = 300000; 
                if (m_BSHCLogger) m_BSHCLogger.Warning("OnCrateSpawnTickPeriodic - PeriodicTickInterval was <=0, forced to 300s for next CallLater.");
             }
        }
        
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.OnCrateSpawnTickPeriodic, nextTickDelayMs, false);
        
        if (m_BSHCLogger) 
        {
            m_BSHCLogger.Info("OnCrateSpawnTickPeriodic - Periodic spawn pass completed. Next periodic tick scheduled in " + (nextTickDelayMs / 1000.0) + " seconds.");
        }
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        if (eventTypeId == ChatMessageEventTypeID)
        {
            ChatMessageEventParams chat_params = ChatMessageEventParams.Cast(params);
            
            if (!chat_params) return;

            if (chat_params.param1 == 0)
            {
                string senderName = chat_params.param2;
                string message = chat_params.param3;

                if (message == "") return;

                PlayerBase player = GetPlayerByName(senderName);
                
                if (!player) return;

                message.ToLower(); 

                if (message == "!hcreload")
                {

                    if (BSHC_IsPlayerAdmin(player.GetIdentity()))
                    {
                        BSHC_ReloadConfigs(player.GetIdentity());
                    }
                    else
                    {
                        GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", new Param1<string>("#STR_BSHC_NoPermission"), true, player.GetIdentity());
                    }
                }
            }
        }
    }
    void BSHC_ReloadConfigs(PlayerIdentity adminIdentity)
    {
        BSHC_Log.GetInstance().Info("BSHC_ReloadConfigs: Admin " + adminIdentity.GetId() + " initiated a live config reload.");
        Print("[BS_HackedCrate] Recarga de configuración iniciada por un administrador.");
        if (m_BSHC_CrateConfigManager)
        {
            m_BSHC_CrateConfigManager.LoadOrCreateConfigs();

            CrateManagement newMgmt = m_BSHC_CrateConfigManager.GetCrateManagement();
            if (newMgmt && m_BSHC_CrateSpawner)
            {
                m_BSHC_CrateSpawner.UpdateCrateManagement(newMgmt);
                
                m_BSHC_PeriodicTickIntervalSeconds = newMgmt.PeriodicTickIntervalSeconds;
                
                BSHC_Log.GetInstance().Info("BSHC_ReloadConfigs: Configs reloaded successfully. New periodic tick interval is " + m_BSHC_PeriodicTickIntervalSeconds + "s.");
                Print("[BS_HackedCrate] ¡Configuraciones recargadas con éxito!");

                GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", new Param1<string>("#STR_BSHC_ReloadSuccess"), true, adminIdentity);
            }
            else
            {
                BSHC_Log.GetInstance().Error("BSHC_ReloadConfigs: Failed to get new CrateManagement or Spawner is null.");
                Print("[BS_HackedCrate] Error: No se pudieron aplicar las nuevas configuraciones.");
                GetRPCManager().SendRPC("BSHC_Notif_RPC", "Client_ShowSimpleNotification", new Param1<string>("#STR_BSHC_NoPermission"), true, adminIdentity); 
            }
        }
    }

    bool BSHC_IsPlayerAdmin(PlayerIdentity identity)
    {
        if (!identity) return false;

        string adminFilePath = "$profile:\\Bastardo_HC\\admins.txt";
        
        if (!FileExist(adminFilePath))
        {
            FileHandle file = OpenFile(adminFilePath, FileMode.WRITE);
            if (file != 0)
            {
                FPrintln(file, "// Put the Steam64IDs of the administrators here, one per line.");
                CloseFile(file);
            }
            return false;
        }

        FileHandle adminFile = OpenFile(adminFilePath, FileMode.READ);
        if (adminFile == 0) return false;

        string line;
        string playerSteamId = identity.GetPlainId(); 

        while (FGets(adminFile, line) > 0)
        {
            line.Trim();
            if (line.IndexOf("//") == 0 || line == "") continue;
            
            if (line == playerSteamId)
            {
                CloseFile(adminFile);
                return true;
            }
        }

        CloseFile(adminFile);
        return false;
    }

    PlayerBase GetPlayerByName(string name)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man p : players)
        {
            PlayerBase player = PlayerBase.Cast(p);
            if (player && player.GetIdentity() && player.GetIdentity().GetName() == name)
            {
                return player;
            }
        }
        return null;
    }
}