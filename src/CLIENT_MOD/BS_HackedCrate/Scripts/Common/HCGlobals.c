class BSHCGlobalConfig 
{
    static ref BSHCLootPoolConfig m_LootConfig; 


    static void SetConfig(BSHCLootPoolConfig config)
    {
        m_LootConfig = config;
    }

    static ref BSHCLootPoolConfig GetConfig() 
    {
        return m_LootConfig;
    }
}