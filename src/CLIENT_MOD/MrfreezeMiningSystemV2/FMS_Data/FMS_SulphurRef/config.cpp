class CfgPatches
{
	class FMS_SulphurRef
	{
		units[]=
		{
			"FreezeRef_Sulphur"
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
	class FreezeNugget_base;
	class FreezeRef_Sulphur: FreezeNugget_base
	{
		scope=2;
		displayName="硫磺块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_SulphurRef\FMS_SulphurRef.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_SulphurRef\Data\FMS_SulphurRef.paa"
		};
		inventorySlot[]=
		{
			"FreezeRef_Sulphur",
			"FreezeRef_Sulphur1",
			"FreezeRef_Sulphur2",
			"FreezeRef_Sulphur3"
		};
	};
};
