modded class DayZGame
{	
	protected ref SFLConfig m_SearchForLootConfig;
	protected ref TStringStringMap m_SFLBuildings;

	
    void SetSearchForLootConfig(SFLConfig config)
    {
        m_SearchForLootConfig = config;
    }

    SFLConfig GetSearchForLootConfig()
    {
		return m_SearchForLootConfig;
    }
	
	void SetBuildingCategoryMap(SFLConfig config)
	{
		m_SFLBuildings = new TStringStringMap;
		for (int i = 0; i < config.SFLBuildings.Count(); i++)
		{
			for (int j = 0; j < config.SFLBuildings.Get(i).buildings.Count(); j++)
			{
				
				m_SFLBuildings.Insert(config.SFLBuildings.Get(i).buildings.Get(j),config.SFLBuildings.Get(i).name);
			}
		}
	}
	string GetBuildingCategory(string building)
	{
		string category;
		bool found = m_SFLBuildings.Find(building, category);
		if (!found)
		{
			return "Civilian";
		}
		return category;
	}
};