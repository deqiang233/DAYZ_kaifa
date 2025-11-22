class FreezeNodeLocation
{
    string Enabled;
    string name;
    string Node;
    int Spawn_min;
    int Spawn_max;
    ref array<string> pos;
    int respawn_timer;
    int randomize_position;

    void FreezeNodeLocation()
    {
        pos = new array<string>();
    }
}

class FreezeSpawnManagerConfig
{
    string EnableNodeSpawns;
    ref array<ref FreezeNodeLocation> NodeLocations;

    void FreezeSpawnManagerConfig()
    {
        NodeLocations = new array<ref FreezeNodeLocation>();
    }
}

class FreezeSpawnedNode
{
    string nodeType;
    vector position;
    vector orientation;
    Object spawnedObject;
    int respawnTimer;
    float timeSinceDestroyed;

    void FreezeSpawnedNode(string type, vector pos, vector ori, Object obj, int timer)
    {
        nodeType = type;
        position = pos;
        orientation = ori;
        spawnedObject = obj;
        respawnTimer = timer;
        timeSinceDestroyed = 0;
    }
}

class FreezeSpawnManager extends PluginBase
{
    private const static string FileFolder = "$profile:FreezeMining\\Mining\\";
    private const static string FilePath = FileFolder + "FMS_SpawnManager.json";
    
    ref FreezeSpawnManagerConfig m_Config;
    ref array<ref FreezeSpawnedNode> m_SpawnedNodes;
    private bool m_Initialized = false;

    void FreezeSpawnManager()
    {
        m_Config = new FreezeSpawnManagerConfig();
        m_SpawnedNodes = new array<ref FreezeSpawnedNode>();
    }

    override void OnInit()
    {
        if (GetGame().IsDedicatedServer())
        {
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] Initializing spawn manager...", true);
            LoadConfig();
            
            if (m_Config.EnableNodeSpawns == "1")
            {
                SpawnAllNodes();
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckNodeRespawns, 10000, true);
            }
        }
    }

    void LoadConfig()
    {
        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Loading spawn configuration...", true);

        if (!FileExist(FilePath))
        {
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] Config not found, creating default config.", true);
            CreateDefaultConfig();
            SaveConfig();
        }
        else
        {
            JsonFileLoader<FreezeSpawnManagerConfig>.JsonLoadFile(FilePath, m_Config);
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] Config loaded with " + m_Config.NodeLocations.Count().ToString() + " location groups.", true);
        }
    }

    void SaveConfig()
    {
        if (!GetGame().IsDedicatedServer())
        {
            return;
        }

        LoggingUtility.EnsureDirectoriesExist();
        JsonFileLoader<FreezeSpawnManagerConfig>.JsonSaveFile(FilePath, m_Config);
        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Config saved to file.", true);
    }

    void CreateDefaultConfig()
    {
        m_Config.EnableNodeSpawns = "0";
        
        ref FreezeNodeLocation copperLoc = new FreezeNodeLocation();
        copperLoc.Enabled = "0";
        copperLoc.name = "Copper Node Cluster";
        copperLoc.Node = "FreezeNode_copper";
        copperLoc.Spawn_min = 1;
        copperLoc.Spawn_max = 3;
        copperLoc.pos.Insert("3372.0 2.0 5465.0|0.0 0.0 0.0");
        copperLoc.respawn_timer = 1200;
        copperLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(copperLoc);
        
        ref FreezeNodeLocation goldLoc = new FreezeNodeLocation();
        goldLoc.Enabled = "0";
        goldLoc.name = "Gold Node Cluster";
        goldLoc.Node = "FreezeNode_gold";
        goldLoc.Spawn_min = 1;
        goldLoc.Spawn_max = 2;
        goldLoc.pos.Insert("3400.0 2.0 5500.0|0.0 0.0 0.0");
        goldLoc.respawn_timer = 1800;
        goldLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(goldLoc);
        
        ref FreezeNodeLocation ironLoc = new FreezeNodeLocation();
        ironLoc.Enabled = "0";
        ironLoc.name = "Iron Node Cluster";
        ironLoc.Node = "FreezeNode_iron";
        ironLoc.Spawn_min = 1;
        ironLoc.Spawn_max = 3;
        ironLoc.pos.Insert("3450.0 2.0 5550.0|0.0 0.0 0.0");
        ironLoc.respawn_timer = 1200;
        ironLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(ironLoc);
        
        ref FreezeNodeLocation silverLoc = new FreezeNodeLocation();
        silverLoc.Enabled = "0";
        silverLoc.name = "Silver Node Cluster";
        silverLoc.Node = "FreezeNode_silver";
        silverLoc.Spawn_min = 1;
        silverLoc.Spawn_max = 2;
        silverLoc.pos.Insert("3500.0 2.0 5600.0|0.0 0.0 0.0");
        silverLoc.respawn_timer = 1500;
        silverLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(silverLoc);
        
        ref FreezeNodeLocation tinLoc = new FreezeNodeLocation();
        tinLoc.Enabled = "0";
        tinLoc.name = "Tin Node Cluster";
        tinLoc.Node = "FreezeNode_tin";
        tinLoc.Spawn_min = 1;
        tinLoc.Spawn_max = 3;
        tinLoc.pos.Insert("3550.0 2.0 5650.0|0.0 0.0 0.0");
        tinLoc.respawn_timer = 1200;
        tinLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(tinLoc);
        
        ref FreezeNodeLocation stoneLoc = new FreezeNodeLocation();
        stoneLoc.Enabled = "0";
        stoneLoc.name = "Stone Node Cluster";
        stoneLoc.Node = "FreezeNode_stone";
        stoneLoc.Spawn_min = 2;
        stoneLoc.Spawn_max = 5;
        stoneLoc.pos.Insert("3600.0 2.0 5700.0|0.0 0.0 0.0");
        stoneLoc.respawn_timer = 600;
        stoneLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(stoneLoc);
        
        ref FreezeNodeLocation uraniumLoc = new FreezeNodeLocation();
        uraniumLoc.Enabled = "0";
        uraniumLoc.name = "Uranium Node Cluster";
        uraniumLoc.Node = "FreezeNode_uranium";
        uraniumLoc.Spawn_min = 1;
        uraniumLoc.Spawn_max = 1;
        uraniumLoc.pos.Insert("3650.0 2.0 5750.0|0.0 0.0 0.0");
        uraniumLoc.respawn_timer = 2400;
        uraniumLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(uraniumLoc);
        
        ref FreezeNodeLocation sulphurLoc = new FreezeNodeLocation();
        sulphurLoc.Enabled = "0";
        sulphurLoc.name = "Sulphur Node Cluster";
        sulphurLoc.Node = "FreezeNode_sulphur";
        sulphurLoc.Spawn_min = 1;
        sulphurLoc.Spawn_max = 3;
        sulphurLoc.pos.Insert("3700.0 2.0 5800.0|0.0 0.0 0.0");
        sulphurLoc.respawn_timer = 1200;
        sulphurLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(sulphurLoc);
        
        ref FreezeNodeLocation amberLoc = new FreezeNodeLocation();
        amberLoc.Enabled = "0";
        amberLoc.name = "Amber Gem Node";
        amberLoc.Node = "FreezeNode_AmberGemNode";
        amberLoc.Spawn_min = 1;
        amberLoc.Spawn_max = 1;
        amberLoc.pos.Insert("3750.0 2.0 5850.0|0.0 0.0 0.0");
        amberLoc.respawn_timer = 3600;
        amberLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(amberLoc);
        
        ref FreezeNodeLocation amethystLoc = new FreezeNodeLocation();
        amethystLoc.Enabled = "0";
        amethystLoc.name = "Amethyst Gem Node";
        amethystLoc.Node = "FreezeNode_AmethystGemNode";
        amethystLoc.Spawn_min = 1;
        amethystLoc.Spawn_max = 1;
        amethystLoc.pos.Insert("3800.0 2.0 5900.0|0.0 0.0 0.0");
        amethystLoc.respawn_timer = 3600;
        amethystLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(amethystLoc);
        
        ref FreezeNodeLocation aquamarineLoc = new FreezeNodeLocation();
        aquamarineLoc.Enabled = "0";
        aquamarineLoc.name = "Aquamarine Gem Node";
        aquamarineLoc.Node = "FreezeNode_AquamarineGemNode";
        aquamarineLoc.Spawn_min = 1;
        aquamarineLoc.Spawn_max = 1;
        aquamarineLoc.pos.Insert("3850.0 2.0 5950.0|0.0 0.0 0.0");
        aquamarineLoc.respawn_timer = 3600;
        aquamarineLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(aquamarineLoc);
        
        ref FreezeNodeLocation fancyDiamondLoc = new FreezeNodeLocation();
        fancyDiamondLoc.Enabled = "0";
        fancyDiamondLoc.name = "Fancy Colour Diamond Gem Node";
        fancyDiamondLoc.Node = "FreezeNode_FancyColourDiamondGemNode";
        fancyDiamondLoc.Spawn_min = 1;
        fancyDiamondLoc.Spawn_max = 1;
        fancyDiamondLoc.pos.Insert("3900.0 2.0 6000.0|0.0 0.0 0.0");
        fancyDiamondLoc.respawn_timer = 7200;
        fancyDiamondLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(fancyDiamondLoc);
        
        ref FreezeNodeLocation ioliteLoc = new FreezeNodeLocation();
        ioliteLoc.Enabled = "0";
        ioliteLoc.name = "Iolite Gem Node";
        ioliteLoc.Node = "FreezeNode_IoliteGemNode";
        ioliteLoc.Spawn_min = 1;
        ioliteLoc.Spawn_max = 1;
        ioliteLoc.pos.Insert("3950.0 2.0 6050.0|0.0 0.0 0.0");
        ioliteLoc.respawn_timer = 3600;
        ioliteLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(ioliteLoc);
        
        ref FreezeNodeLocation jadeLoc = new FreezeNodeLocation();
        jadeLoc.Enabled = "0";
        jadeLoc.name = "Jade Gem Node";
        jadeLoc.Node = "FreezeNode_JadeGemNode";
        jadeLoc.Spawn_min = 1;
        jadeLoc.Spawn_max = 1;
        jadeLoc.pos.Insert("4000.0 2.0 6100.0|0.0 0.0 0.0");
        jadeLoc.respawn_timer = 3600;
        jadeLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(jadeLoc);
        
        ref FreezeNodeLocation rubyLoc = new FreezeNodeLocation();
        rubyLoc.Enabled = "0";
        rubyLoc.name = "Ruby Gem Node";
        rubyLoc.Node = "FreezeNode_RubyGemNode";
        rubyLoc.Spawn_min = 1;
        rubyLoc.Spawn_max = 1;
        rubyLoc.pos.Insert("4050.0 2.0 6150.0|0.0 0.0 0.0");
        rubyLoc.respawn_timer = 4800;
        rubyLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(rubyLoc);
        
        ref FreezeNodeLocation turquoiseLoc = new FreezeNodeLocation();
        turquoiseLoc.Enabled = "0";
        turquoiseLoc.name = "Turquoise Gem Node";
        turquoiseLoc.Node = "FreezeNode_TurquoiseGemNode";
        turquoiseLoc.Spawn_min = 1;
        turquoiseLoc.Spawn_max = 1;
        turquoiseLoc.pos.Insert("4100.0 2.0 6200.0|0.0 0.0 0.0");
        turquoiseLoc.respawn_timer = 3600;
        turquoiseLoc.randomize_position = 1;
        m_Config.NodeLocations.Insert(turquoiseLoc);
        
        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Created default config with 16 node types.", true);
    }

    void SpawnAllNodes()
    {
        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Starting to spawn nodes...", true);

        for (int i = 0; i < m_Config.NodeLocations.Count(); i++)
        {
            FreezeNodeLocation location = m_Config.NodeLocations.Get(i);
            
            if (location.Enabled != "1")
            {
                continue;
            }

            LoggingUtility.LogToFileFM("[FreezeSpawnManager] Spawning location group: " + location.name, true);

            for (int j = 0; j < location.pos.Count(); j++)
            {
                string posData = location.pos.Get(j);
                
                int spawnMin = location.Spawn_min;
                int spawnMax = location.Spawn_max;
                
                if (spawnMin <= 0)
                {
                    spawnMin = 1;
                }
                if (spawnMax < spawnMin)
                {
                    spawnMax = spawnMin;
                }
                
                int nodesToSpawn = Math.RandomInt(spawnMin, spawnMax + 1);
                
                for (int k = 0; k < nodesToSpawn; k++)
                {
                    SpawnNodeAtPosition(location.Node, posData, location.respawn_timer, location.randomize_position);
                }
                
                LoggingUtility.LogToFileFM("[FreezeSpawnManager] Spawned " + nodesToSpawn.ToString() + " nodes of type " + location.Node + " at position " + j.ToString(), true);
            }
        }

        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Finished spawning " + m_SpawnedNodes.Count().ToString() + " total nodes.", true);
    }

    void SpawnNodeAtPosition(string nodeType, string posData, int respawnTimer, int randomize)
    {
        TStringArray parts = new TStringArray;
        posData.Split("|", parts);

        if (parts.Count() < 2)
        {
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] ERROR: Invalid position data: " + posData, true);
            return;
        }

        vector position = parts[0].ToVector();
        vector orientation = parts[1].ToVector();

        if (randomize == 1)
        {
            float randomX = Math.RandomFloatInclusive(-2.0, 2.0);
            float randomZ = Math.RandomFloatInclusive(-2.0, 2.0);
            position[0] = position[0] + randomX;
            position[2] = position[2] + randomZ;
        }

        Object spawnedNode = GetGame().CreateObjectEx(nodeType, position, ECE_PLACE_ON_SURFACE);
        
        if (spawnedNode)
        {
            spawnedNode.SetPosition(position);
            spawnedNode.SetOrientation(orientation);
            
            ref FreezeSpawnedNode nodeData = new FreezeSpawnedNode(nodeType, position, orientation, spawnedNode, respawnTimer);
            m_SpawnedNodes.Insert(nodeData);
            
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] Spawned " + nodeType + " at " + position.ToString(), true);
        }
        else
        {
            LoggingUtility.LogToFileFM("[FreezeSpawnManager] ERROR: Failed to spawn " + nodeType, true);
        }
    }

    void CheckNodeRespawns()
    {
        if (!GetGame().IsDedicatedServer())
        {
            return;
        }

        for (int i = m_SpawnedNodes.Count() - 1; i >= 0; i--)
        {
            FreezeSpawnedNode nodeData = m_SpawnedNodes.Get(i);
            
            bool needsRespawn = false;
            
            if (!nodeData.spawnedObject)
            {
                needsRespawn = true;
            }
            else if (!nodeData.spawnedObject.IsAlive())
            {
                needsRespawn = true;
            }
            
            if (needsRespawn)
            {
                nodeData.timeSinceDestroyed = nodeData.timeSinceDestroyed + 10.0;
                
                if (nodeData.timeSinceDestroyed >= nodeData.respawnTimer)
                {
                    LoggingUtility.LogToFileFM("[FreezeSpawnManager] Respawning " + nodeData.nodeType + " at " + nodeData.position.ToString(), true);
                    
                    Object newNode = GetGame().CreateObjectEx(nodeData.nodeType, nodeData.position, ECE_PLACE_ON_SURFACE);
                    
                    if (newNode)
                    {
                        newNode.SetPosition(nodeData.position);
                        newNode.SetOrientation(nodeData.orientation);
                        nodeData.spawnedObject = newNode;
                        nodeData.timeSinceDestroyed = 0;
                        LoggingUtility.LogToFileFM("[FreezeSpawnManager] Successfully respawned " + nodeData.nodeType, true);
                    }
                    else
                    {
                        LoggingUtility.LogToFileFM("[FreezeSpawnManager] ERROR: Failed to respawn " + nodeData.nodeType, true);
                    }
                }
            }
        }
    }
};

