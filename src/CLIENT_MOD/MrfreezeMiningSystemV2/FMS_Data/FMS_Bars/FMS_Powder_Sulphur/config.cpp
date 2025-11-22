class CfgPatches
{
	class Powder_Sulphur
	{
		units[]=
		{
			"FreezePowder_Sulphur"
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
	class FreezePowder_Sulphur: Inventory_Base
	{
		scope=2;
		displayName="硫磺粉";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\FMS_Powder_Sulphur.p3d";
		descriptionShort="使用10个精炼硫制作。用于DayZ挖矿系统。";
		itemSize[]={1,2};
		canBeSplit=1;
		varQuantityDestroyOnMin=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10;
		weight=30;
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\data\FMS_Powder_Sulphur.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\data\FMS_Powder_Sulphur.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\data\FMS_Powder_Sulphur_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\data\FMS_Powder_Sulphur_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\FMS_Powder_Sulphur\data\FMS_Powder_Sulphur_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};
