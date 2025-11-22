modded class MissionServer
{
    void MissionServer()
    {
		SFLConfig config;
        SearchForLootConfig.UpgradeConfig("SearchForLoot.json", config);
		SearchForLootConfig.LoadConfig("SearchForLoot.json", config);
        GetDayZGame().SetSearchForLootConfig(config);
		GetDayZGame().SetBuildingCategoryMap(config);
		/*
		SearchForLootManager.ClearInstance();
		SearchForLootManager.GetInstance();
		*/
    }
};
