const int SFL_SEND_NAME = -1811;

class SFBuildingCategory
{
    string name;
    ref TStringArray buildings;

    void SFBuildingCategory( string nam, TStringArray build )
    {
        name = nam;
        buildings = build;
    }
}

class SFLootItem
{
    string item;
    float weight;
    
    void SFLootItem(string itm, float wgt)
    {
        item = itm;
        weight = wgt;
    }
}

class SFLootCategory
{
    string name;
	float rarity;
    ref TStringArray loot; // 兼容旧格式
    ref array<ref SFLootItem> lootItems; // 新格式：带权重的物品列表

    void SFLootCategory( string nam, float rari, TStringArray loo )
    {
        name = nam;
		rarity = rari;
        loot = loo;
        lootItems = new array<ref SFLootItem>;
    }
}

class SFProxyCategory
{
    string name;
    ref TStringArray proxies;

    void SFProxyCategory( string nam, TStringArray pro )
    {
        name = nam;
        proxies = pro;
    }
}

class SFLConfig
{

	bool EnableDebug;
	float Rarity;
	int InitialCooldown;
	int XPGain;
	bool SoundEnabled;
	bool DisableNotifications;
	string NotificationHeading;
	string NotificationText;
	string NotificationText2;
	float MaxHealthCoef;
	ref array< ref SFBuildingCategory > SFLBuildings;
	ref array< ref SFLootCategory > SFLLootCategory;
	ref array< ref SFProxyCategory > SFLProxyCategory;
	void SFLConfig()
	{
		SFLBuildings = new ref array< ref SFBuildingCategory >;
		SFLLootCategory = new ref array< ref SFLootCategory >;
		SFLProxyCategory = new ref array< ref SFProxyCategory >;
	}

}

class SearchForLootConfig
{

    protected const static string m_ConfigRoot = "$profile:\\SearchForLoot\\";

    static void LoadConfig(string configName, out SFLConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            SFLLogger.Log("'" + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<SFLConfig>.JsonLoadFile(configPath, configData);
        SFLLogger.Log("'" + configName + "' found, loading existing config");

    }

    protected static void SaveConfig(string configName, SFLConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            SFLLogger.Log("'" + m_ConfigRoot + "' does not exist, creating directory");
            MakeDirectory(m_ConfigRoot);
        }
        JsonFileLoader<SFLConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out SFLConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            SFLLogger.Log("'"  + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<SFLConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...
		if (!configData.MaxHealthCoef)
		{
			configData.MaxHealthCoef = 1.0;	
		}
		
		if (!configData.XPGain)
		{
			configData.XPGain = 1;
		}
			
        JsonFileLoader<SFLConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out SFLConfig configData)
    {
        configData = new SFLConfig();
		configData.EnableDebug = false;
		configData.Rarity = 50;
		configData.InitialCooldown = 400;
		configData.XPGain = 1;
		configData.SoundEnabled = true;
		configData.DisableNotifications = 0;
		configData.NotificationHeading = "Searching";
		configData.NotificationText = "You found something...";
		configData.NotificationText2 = "Seems to be empty...";
		configData.MaxHealthCoef = 1.0;
		configData.SFLProxyCategory.Insert(new SFProxyCategory("Food", {"static_kitchen_unit_a_dz", "static_shelf", "static_shelf_1side", "static_skrin_bar", "static_fridge", "static_kitchenstove_elec"} ));
        configData.SFLProxyCategory.Insert(new SFProxyCategory("Clothing", {"static_washing_machine", "static_tent_strecher", "static_locker_open_v3", "static_locker_open_v2", "static_locker_closed_v2", "static_matress_white_bent", "static_locker_closed_blue_v1", "static_case_bedroom_b", "static_case_cans_b", "static_class_case_b_open", "static_class_case_a_open", "static_class_case_a_closed", "static_foldingbed_open", "static_vojenska_palanda", "static_locker_closed_v1", "static_case_d", "static_dhangar_brownskrin", "static_case_a", "static_case_a_open", "static_almara_open", "static_almara", "static_dhangar_brownskrin_old", "static_pipe-big", "static_school_cage"} ));
        configData.SFLProxyCategory.Insert(new SFProxyCategory("Tools", {"static_tent_gunrack", "static_lekarnicka", "static_medical_table", "static_wheel_cart_dz", "static_locker_closed_v3", "static_teacher_desk", "static_lab_teacher_bench", "static_metalcrate_02", "static_hospital_transport_bed", "static_classroom_case_a", "static_shelfs_small", "static_lab_bench", "static_truck_01_aban_1_lod1parts_fire", "static_class_case_b_closed", "static_workbench_dz", "static_metalcrate", "static_workbench", "static_metalcase_02", "static_metalcase_01", "static_locker_open_blue_v2", "static_library_a", "static_office_table_a", "static_bucket", "static_box_c_multi", "static_rack_dz", "static_box_c", "static_tools_racking_dz", "static_library_a_open", "static_case_bedroom_a", "static_desk_office", "static_table_drawer", "static_shelf_dz", "static_conference_table_a", "static_koz", "static_pipe-small", "static_phonebox", "static_tent_boxwooden", "static_table_umakart", "static_misc_boxwooden"} ));

		
        configData.SFLLootCategory.Insert(new SFLootCategory("Civilian_Food", 50, { "TunaCan", "Pajka", "UnknownFoodCan", "Zagorky", "PowderedMilk", "BoxCerealCrunchin", "Apple", "BakedBeansCan", "CatFoodCan", "Chips"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Civilian_Clothing", 50, { "CivilianBelt", "Rope", "PetrolLighter", "AthleticShoes_Blue", "BalaclavaMask_Blue", "Paper", "Raincoat_Red", "ShortJeans_Blue", "SlacksPants_LightGrey", "BeanieHat_Beige"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Civilian_Tools", 50, { "Paper", "PetrolLighter", "Rope", "Ammo_22", "Ammo_12gaSlug", "KitchenKnife", "KitchenTimer", "SteakKnife", "Whetstone", "Screwdriver"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Industrial_Food", 50, { "UnknownFoodCan", "Apple", "BoxCerealCrunchin", "Chips", "BakedBeansCan", "Chips", "Crackers", "GreenBellPepper", "Honey", "HumanSteakMeat"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Industrial_Clothing", 50, { "JumpsuitJacket_Blue", "JumpsuitPants_Green", "MotoHelmet_Lime", "Netting", "Fabric", "Headtorch_Grey", "RadarCap_Black", "WorkingGloves_Beige", "ZmijovkaCap_Black", "BalaclavaMask_Beige"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Industrial_Tools", 50, { "NailBox", "MetalWire", "ElectronicRepairKit", "EpoxyPutty", "Fabric", "Headtorch_Grey", "Nail", "Screwdriver", "WorkingGloves_Yellow", "Wrench"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Farm_Food", 50, { "Apple", "Crackers", "GreenBellPepper", "Honey", "LactariusMushroom", "Lunchmeat", "MacrolepiotaMushroom", "Marmalade", "Pajka", "SodaCan_Fronta", "SodaCan_Cola", "SodaCan_Kvass", "BakedBeansCan"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Farm_Clothing", 50, { "CargoPants_Beige", "CowboyHat_Brown", "Fabric", "DuctTape", "FaceCover_Improvised", "Headtorch_Black", "LeatherSewingKit", "paper", "BeanieHat_Black", "WorkingGloves_Beige", "Rope", "WoolGloves_Tan"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Farm_Tools", 50, { "Ammo_12gaSlug", "Ammo_357", "BarbedWire", "DuctTape", "Hammer", "Broom", "LeatherSewingKit", "BarbedWire", "Nail", "Rope", "MediumGasCanister", "CanisterGasoline"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Hunting_Food", 50, { "UnknownFoodCan", "Apple", "BoxCerealCrunchin", "Chips", "BakedBeansCan", "Chips", "Crackers", "GreenBellPepper", "Honey", "HumanSteakMeat"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Hunting_Clothing", 50, { "CowboyHat_black", "DryBag_Blue", "Armband_BabyDeer", "Armband_Bear", "Headtorch_Grey", "ChernarusMap", "Heatpack", "HunterPants_Autumn", "HuntingJacket_Autumn", "HuntingKnife", "Ushanka_Black", "Whetstone", "Balaclava3Holes_Beige"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Hunting_Tools", 50, { "OrienteeringCompass", "CanOpener", "CookingStand", "PUScopeOptic", "Headtorch_Grey", "ChernarusMap", "Compass", "Flashlight", "Heatpack", "HuntingKnife", "Matchbox", "Whetstone", "SewingKit"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Police_Food", 50, { "UnknownFoodCan", "Apple", "BoxCerealCrunchin", "Chips", "BakedBeansCan", "Chips", "Crackers", "TacticalBaconCan", "TunaCan", "BakedBeansCan"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Police_Clothing", 50, { "PoliceCap", "PolicePants", "Ammo_40mm_Smoke_Red", "PoliceJacket", "PoliceJacketOrel", "AviatorGlasses", "HandcuffKeys", "Handcuffs", "PoliceVest", "PrisonUniformJacket", "PrisonUniformPants"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Police_Tools", 50, { "Ammo_12gaRubberSlug", "Ammo_12gaPellets", "Ammo_40mm_Smoke_Red", "Rangefinder", "Armband_LivoniaPolice", "AviatorGlasses", "HandcuffKeys", "Handcuffs", "UniversalLight", "WeaponCleaningKit"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Medical_Food", 50, { "TunaCan", "PowderedMilk", "BloodBagEmpty", "BloodTestKit", "CharcoalTablets", "DisinfectantSpray", "Morphine", "NioshFaceMask", "PainkillerTablets", "SalineBag", "StartKitIV", "VitaminBottle"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Medical_Clothing", 50, { "SurgicalGloves_Blue", "Armband_White", "MedicalScrubsPants_White", "SurgicalMask", "FirstAidKit", "DisinfectantSpray", "LabCoat", "MouthRag", "MedicalScrubsHat_Blue", "MedicalScrubsPants_Blue", "MedicalScrubsShirt_Blue"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Medical_Tools", 50, { "BloodBagEmpty", "BloodTestKit", "CharcoalTablets", "DisinfectantSpray", "Morphine", "MouthRag", "FirstAidKit", "PainkillerTablets", "Pen_Black", "SalineBag", "StartKitIV", "SurgicalGloves_Green", "VitaminBottle"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Military_Food", 50, { "UnknownFoodCan", "TacticalBaconCan", "BoxCerealCrunchin", "Chips", "BakedBeansCan", "TunaCan", "Crackers", "UnknownFoodCan", "Honey", "Canteen"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Military_Clothing", 50, { "MilitaryBelt", "MilitaryBeret_CDF", "CombatKnife", "Flag_Chernarus", "MilitaryBoots_Beige", "NVGHeadstrap", "OMNOGloves_Brown", "NylonKnifeSheath", "OfficerHat", "TTSKOPants", "TTsKOJacket_Camo", "TacticalGloves_Beige"} ));
		configData.SFLLootCategory.Insert(new SFLootCategory("Military_Tools", 50, { "CombatKnife", "Flag_Chernarus", "LandMineTrap", "M18SmokeGrenade_White", "MilitaryBelt", "NylonKnifeSheath", "Rangefinder", "Ammo_545x39", "Ammo_762x54", "Ammo_9x19", "Ammo_45ACP" } ));
		
		configData.SFLBuildings.Insert(new SFBuildingCategory("Civilian", { "" } ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Industrial", { "Land_CementWorks_Hall2_Grey", "Land_CementWorks_Hall2_Brick", "Land_Airfield_Hangar_Green", "Land_Airfield_ServiceHangar_L", "Land_Airfield_ServiceHangar_R" ,"Land_Barn_Metal_Big", "Land_Barn_Metal_Big_Grey", "Land_CoalPlant_Main", "Land_Construction_Building", "Land_Construction_House1", "Land_Construction_House2", "Land_DieselPowerPlant_Building", "Land_Factory_Lathes", "Land_Factory_Small", "Land_Garage_Big", "Land_Garage_Office", "Land_Garage_Row_Big", "Land_Garage_Row_Small", "Land_Garage_Small", "Land_Garage_Tall", "Land_Mil_AircraftShelter", "Land_Mine_Building", "Land_Power_Station", "Land_Power_Transformer_Build", "Land_Quarry_Main" ,"Land_Rail_Station_Big", "Land_Rail_Station_Small", "Land_Rail_Warehouse_Small", "Land_Repair_Center", "Land_Sawmill_Building", "Land_Workshop_FuelStation", "Land_Workshop1", "Land_Workshop2", "Land_Workshop3", "Land_Workshop4", "Land_Workshop5"} ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Farm", { "Land_Barn_Brick1", "Land_Barn_Brick2", "Land_Barn_Wood1", "Land_Barn_Wood2", "Land_Farm_CowshedA", "Land_Farm_CowshedB", "Land_Farm_CowshedC"} ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Hunting", { "Land_Village_Pub", "Land_Camp_House_brown", "Land_Camp_House_red", "Land_Camp_House_white"} ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Police", { "Land_Village_PoliceStation", "Land_City_PoliceStation", "Land_Village_PoliceStation_Enoch", "Land_City_PoliceStation", "Land_Guardhouse", "Land_Mil_Guardhouse1", "Land_Mil_Guardhouse3"} ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Medical", { "Land_Village_HealthCare", "Land_Village_HealthCare_Enoch", "Land_City_Hospital", "Land_Medical_Tent_Big", "Land_Medical_Tent_Shower"} ));
		configData.SFLBuildings.Insert(new SFBuildingCategory("Military", { "Land_Bunker1_Double", "Land_Bunker1_Left", "Land_Bunker1_Right", "Land_Bunker2_Double", "Land_Bunker2_Left", "Land_Bunker2_Right", "Land_Mil_Airfield_HQ", "Land_Mil_ATC_Big", "Land_Mil_ATC_Small", "Land_Mil_Barracks_Round", "Land_Mil_Barracks1", "Land_Mil_Barracks2",
			 "Land_Mil_Barracks3", "Land_Mil_Barracks4", "Land_Mil_Barracks5", "Land_Mil_Barracks6", "Land_Mil_ControlTower", "Land_Mil_Fortified_Nest_Big", "Land_Mil_Fortified_Nest_Small", "Land_Mil_Fortified_Nest_Watchtower", "Land_Mil_Guardbox_Brown", "Land_Mil_Guardbox_Green", "Land_Mil_Guardbox_Smooth", "Land_Mil_Guardhouse2", "Land_Mil_GuardShed",
			 "Land_Mil_GuardTower", "Land_Mil_Tent_Big1_1", "Land_Mil_Tent_Big1_2", "Land_Mil_Tent_Big1_3", "Land_Mil_Tent_Big1_4", "Land_Mil_Tent_Big1_5", "Land_Mil_Tent_Big2_1", "Land_Mil_Tent_Big2_2", "Land_Mil_Tent_Big2_3", "Land_Mil_Tent_Big2_4", "Land_Mil_Tent_Big2_5", "Land_Mil_Tent_Big3", "Land_Mil_Tent_Big4", "Land_Mil_Tower_Small", 
			 "Land_Ruin_Mil_ControlTower", "Land_Tisy_Barracks", "Land_Tisy_Garages", "Land_Tisy_HQ", "Land_Tisy_KitchenRoom", "Land_Tisy_RadarB_Base", "Land_Tisy_RadarPlatform_Top"} ));
	}
}
