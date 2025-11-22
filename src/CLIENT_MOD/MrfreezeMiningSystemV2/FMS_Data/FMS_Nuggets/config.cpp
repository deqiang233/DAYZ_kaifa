class CfgPatches
{
	class FMS_Nuggets
	{
		units[]=
		{
			"FreezeNugget_gold",
			"FreezeNugget_copper",
			"FreezeNugget_iron",
			"FreezeNugget_silver",
			"FreezeNugget_tin",
			"FreezeNugget_uranium"
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
	class SmallStone;
	class FreezeNugget_base: SmallStone
	{
		scope=0;
		displayName="Ore Nugget";
		descriptionShort="Nugget you gotten from smelting ore down. Used by DayZ Mining System";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base_co.paa"
		};
		itemSize[]={1,1};
		weight=4;
		canBeSplit=1;
		varStackMax=10;
		varQuantityDestroyOnMin=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10;
		physLayer="item_small";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Data\FMS_Nuggets_Base_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeNugget_gold: FreezeNugget_base
	{
		scope=2;
		displayName="金块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Gold.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_gold",
			"FreezeNugget_gold1",
			"FreezeNugget_gold2",
			"FreezeNugget_gold3"
		};
	};
	class FreezeNugget_copper: FreezeNugget_base
	{
		scope=2;
		displayName="铜块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Copper.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_copper",
			"FreezeNugget_copper1",
			"FreezeNugget_copper2",
			"FreezeNugget_copper3"
		};
	};
	class FreezeNugget_iron: FreezeNugget_base
	{
		scope=2;
		displayName="铁块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Iron.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_iron",
			"FreezeNugget_iron1",
			"FreezeNugget_iron2",
			"FreezeNugget_iron3"
		};
	};
	class FreezeNugget_silver: FreezeNugget_base
	{
		scope=2;
		displayName="银块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Silver.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_silver",
			"FreezeNugget_silver1",
			"FreezeNugget_silver2",
			"FreezeNugget_silver3"
		};
	};
	class FreezeNugget_tin: FreezeNugget_base
	{
		scope=2;
		displayName="锡块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Tin.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_tin",
			"FreezeNugget_tin1",
			"FreezeNugget_tin2",
			"FreezeNugget_tin3"
		};
	};
	class FreezeNugget_uranium: FreezeNugget_base
	{
		scope=2;
		displayName="铀块";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\FMS_Nuggets.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Nuggets\Textures\FMS_Nugget_Uranium.paa"
		};
		inventorySlot[]=
		{
			"FreezeNugget_uranium",
			"FreezeNugget_uranium1",
			"FreezeNugget_uranium2",
			"FreezeNugget_uranium3"
		};
	};
};
