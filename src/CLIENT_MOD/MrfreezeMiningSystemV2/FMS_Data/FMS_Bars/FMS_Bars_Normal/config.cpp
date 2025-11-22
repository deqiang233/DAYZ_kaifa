class CfgPatches
{
	class FMS_Bars_Normal
	{
		units[]=
		{
			"FreezeBar_copper",
			"FreezeBar_gold",
			"FreezeBar_iron",
			"FreezeBar_silver",
			"FreezeBar_tin",
			"FreezeBar_uranium"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Consumables"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class FreezeBar_base;
	class FreezeBar_copper: FreezeBar_base
	{
		scope=2;
		displayName="铜锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Copper\FreezeBar_copper.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_gold: FreezeBar_base
	{
		scope=2;
		displayName="金锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Gold\FreezeBar_gold.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_iron: FreezeBar_base
	{
		scope=2;
		displayName="铁锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Iron\FreezeBar_iron.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_silver: FreezeBar_base
	{
		scope=2;
		displayName="银锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Silver\FreezeBar_silver.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_tin: FreezeBar_base
	{
		scope=2;
		displayName="锡锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Tin\FreezeBar_tin.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_uranium: FreezeBar_base
	{
		scope=2;
		displayName="铀锭";
		descriptionShort="使用10个金属块制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Normal\FMS_Bar_Uranium\FreezeBar_Uranium.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
};
