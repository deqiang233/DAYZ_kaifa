class BSHCSpawnDefinition
{
    string item_name;
    ref array<string> attachments;
    float probability;

    void BSHCSpawnDefinition()
    {
        attachments = new array<string>;
        probability = 1.0;
    }
}

class BSHCLootPool
{
    string pool_name;
    ref array<ref BSHCSpawnDefinition> items;
    int min_items;
    int max_items;
    float probability; 

    void BSHCLootPool()
    {
        items = new array<ref BSHCSpawnDefinition>;
        min_items = 0; 
        max_items = 0; 
        probability = 1.0;
    }
}

class BSHCLootPoolConfig
{
    ref map<string, ref array<ref BSHCLootPool>> AllDefinedCategories;

    void BSHCLootPoolConfig()
    {
        AllDefinedCategories = new map<string, ref array<ref BSHCLootPool>>;
    }

    static ref BSHCLootPoolConfig Load(string filePath)
    {
        ref BSHCLootPoolConfig configData = new BSHCLootPoolConfig();

        if (FileExist(filePath))
        {
            BSHC_Log.GetInstance().Info("[BSHCLootPoolConfig] Found loot_pools.json at: " + filePath);
            JsonFileLoader<BSHCLootPoolConfig>.JsonLoadFile(filePath, configData);

            if (!configData)
            {
                BSHC_Log.GetInstance().Error("[BSHCLootPoolConfig] JsonLoadFile resulted in NULL configData object. Path: " + filePath + ". Creating default.");
                configData = new BSHCLootPoolConfig(); // Asegurarse que no sea null
                configData.SaveDefaults(filePath); // Guardar defaults si la carga falla críticamente
                return configData;
            }
            
            if (!configData.AllDefinedCategories) // Si el mapa es null después de cargar (JSON vacío o malformado)
            {
                BSHC_Log.GetInstance().Warning("[BSHCLootPoolConfig] AllDefinedCategories is null after loading. Initializing empty map.");
                configData.AllDefinedCategories = new map<string, ref array<ref BSHCLootPool>>;
            }

            BSHC_Log.GetInstance().Info("[BSHCLootPoolConfig] JsonLoadFile executed. Loaded " + configData.AllDefinedCategories.Count() + " categories defined in the root.");
            
            // Ejemplo de cómo verificar los pools dentro de cada categoría cargada
            for (int i = 0; i < configData.AllDefinedCategories.Count(); i++)
            {
                string categoryName = configData.AllDefinedCategories.GetKey(i);
                ref array<ref BSHCLootPool> poolsInCategory = configData.AllDefinedCategories.Get(categoryName);
                if (poolsInCategory)
                {
                    BSHC_Log.GetInstance().Info("[BSHCLootPoolConfig] Category '" + categoryName + "' has " + poolsInCategory.Count() + " loot pools.");
                }
            }
            
            if (configData.AllDefinedCategories.Count() == 0)
            {
                 BSHC_Log.GetInstance().Warning("[BSHCLootPoolConfig] loot_pools.json loaded but no categories found or 'AllDefinedCategories' was empty/missing. Check JSON structure.");
                 // Considerar si crear defaults aquí también si está vacío
            }
            return configData;
        }
        else
        {
            BSHC_Log.GetInstance().Error("[BSHCLootPoolConfig] loot_pools.json not found at: " + filePath + ". Creating default.");
            configData.SaveDefaults(filePath);
            return configData;
        }
    }

    void SaveDefaults(string filePath)
    {
        ref array<ref BSHCLootPool> basicArmamentPools = new array<ref BSHCLootPool>;
        ref BSHCLootPool m4Pool = new BSHCLootPool();
        m4Pool.pool_name = "M4A1_Example_Pool";
        m4Pool.min_items = 1;
        m4Pool.max_items = 1;
        m4Pool.probability = 1.0; // Todos los pools en esta categoría de ejemplo tendrán el mismo peso
            ref BSHCSpawnDefinition m4Def = new BSHCSpawnDefinition();
            m4Def.item_name = "M4A1";
            m4Def.attachments.Insert("Mag_STANAG_30Rnd");
            m4Def.attachments.Insert("M4_OEBttstck");
            m4Def.attachments.Insert("M4_CarryHandleOptic");
            m4Def.probability = 1.0; // Este M4 tiene peso 1.0 en este pool
        m4Pool.items.Insert(m4Def);
        basicArmamentPools.Insert(m4Pool);

        // Ejemplo Categoría 2: Equipo Médico
        ref array<ref BSHCLootPool> medicalPools = new array<ref BSHCLootPool>;
        ref BSHCLootPool bandagePool = new BSHCLootPool();
        bandagePool.pool_name = "Basic_Medical_Supplies";
        bandagePool.min_items = 2;
        bandagePool.max_items = 4;
        bandagePool.probability = 0.8;
            ref BSHCSpawnDefinition bandageDef = new BSHCSpawnDefinition();
            bandageDef.item_name = "BandageDressing";
            bandageDef.probability = 1.5; 
            ref BSHCSpawnDefinition painkillerDef = new BSHCSpawnDefinition();
            painkillerDef.item_name = "PainkillerTablets";
            painkillerDef.probability = 0.5; 
        bandagePool.items.Insert(bandageDef);
        bandagePool.items.Insert(painkillerDef);
        medicalPools.Insert(bandagePool);

        AllDefinedCategories.Insert("DefaultArmaments", basicArmamentPools);
        AllDefinedCategories.Insert("DefaultMedical", medicalPools);

        JsonFileLoader<BSHCLootPoolConfig>.JsonSaveFile(filePath, this);
        BSHC_Log.GetInstance().Info("[BSHCLootPoolConfig] Default loot pool config saved to: " + filePath);
    }
}