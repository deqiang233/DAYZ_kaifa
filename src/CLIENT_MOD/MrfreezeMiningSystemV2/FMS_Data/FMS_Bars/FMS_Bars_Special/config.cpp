class CfgPatches
{
	class FMS_Bars_Special
	{
		units[]=
		{
			"FreezeBar_Adamantite",
			"FreezeBar_Enchanted",
			"FreezeBar_Cobalt",
			"FreezeBar_Crimant",
			"FreezeBar_Eridium"
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
	class FreezeBar_Adamantite: FreezeBar_base
	{
		scope=2;
		displayName="精金锭";
		descriptionShort="通过混合元素制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Special\FMS_Bar_Adamantite\FreezeBar_Adamantite.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_Enchanted: FreezeBar_base
	{
		scope=2;
		displayName="附魔金属锭";
		descriptionShort="通过混合元素制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Special\FMS_Bar_Enchanted\FreezeBar_Enchanted.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_Cobalt: FreezeBar_base
	{
		scope=2;
		displayName="钴锭";
		descriptionShort="通过混合元素制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Special\FMS_Bar_Cobalt\FreezeBar_Cobalt.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_Crimant: FreezeBar_base
	{
		scope=2;
		displayName="红金属锭";
		descriptionShort="通过混合元素制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Special\FMS_Bar_Crimant\FreezeBar_Crimant.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
	class FreezeBar_Eridium: FreezeBar_base
	{
		scope=2;
		displayName="铱锭";
		descriptionShort="通过混合元素制作。用于DayZ挖矿系统。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Bars_Special\FMS_Bar_Eridium\FreezeBar_Eridium.paa"
		};
		hiddenSelections[]=
		{
			"barcamo"
		};
	};
};
