class CfgPatches
{
	class FreezeBar_base
	{
		units[]={};
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
	class FreezeBar_base: Inventory_Base
	{
		scope=0;
		displayName="Ore Bar";
		descriptionShort="Crafted with 10x Nuggets. Used by DayZ Mining System.";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.p3d";
		soundImpactType="metal";
		itemSize[]={1,2};
		canBeSplit=1;
		varQuantityDestroyOnMin=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10;
		weight=30;
		physLayer="item_small";
		fragility=0.0099999998;
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset="crowbar_drop_SoundSet";
					id=898;
				};
				class Crowbar_loop
				{
					soundSet="Crowbar_loop_SoundSet";
					id=1119;
				};
				class Crowbar_end
				{
					soundSet="Crowbar_end_SoundSet";
					id=1120;
				};
			};
		};
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Bars\Data\FMS_Bar_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};
