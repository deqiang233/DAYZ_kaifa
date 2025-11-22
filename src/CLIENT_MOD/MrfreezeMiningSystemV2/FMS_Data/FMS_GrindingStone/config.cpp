class CfgPatches
{
	class FMS_GrindingStone
	{
		units[]=
		{
			"FreezeGrindingStone"
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
	class HouseNoDestruct;
	class Inventory_Base;
	class LargeGasCanister;
	class FreezeGrindingStone: Inventory_Base
	{
		scope=2;
		displayName="磨石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\FMS_GrindingStone_Only.p3d";
		descriptionShort="用于切割和打磨宝石。DayZ挖矿系统使用。";
		canBeDigged=0;
		carveNavmesh=1;
		overrideDrawArea="4.0";
		placement="ForceSlopeOnTerrain";
		heavyItem=1;
		weight=10000;
		physLayer="item_large";
		itemBehaviour=0;
		attachments[]=
		{
			"FMS_GrindingStoneWheel",
			"Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class SlotGrindingStoneWheel
			{
				name="砂轮";
				description="安装砂轮";
				attachmentSlots[]=
				{
					"FMS_GrindingStoneWheel"
				};
				icon="set:fms_icon_set image:fms_srindstone_icon";
			};
			class Wooden_Crate_Storage
			{
				name="木箱";
				description="木箱存储";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1"
				};
				icon="cat_common_cargo";
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeGrindingStone_Static: Inventory_Base
	{
		scope=2;
		displayName="磨石（静态）";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\FMS_GrindingStone.p3d";
		descriptionShort="用于切割和打磨宝石。DayZ挖矿系统使用。";
		itemsCargoSize[]={0,0};
		canBeDigged=0;
		carveNavmesh=1;
		overrideDrawArea="4.0";
		placement="ForceSlopeOnTerrain";
		heavyItem=1;
		weight=10000;
		physLayer="item_large";
		itemBehaviour=0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\data\FMS_GrindingStone_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeGrindingStone_Kit_Holo: Inventory_Base
	{
		scope=0;
		displayName="FreezeGrindingStone HOLO";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\FMS_GrindingStone_Only.p3d";
	};
	class FreezeGrindingStoneWheel: Inventory_Base
	{
		scope=2;
		displayName="砂轮";
		descriptionShort="用于切割和打磨宝石的重型砂轮。安装在磨石上，使用时会磨损。包含20单位耐久度。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_GrindingStone\FMS_GrindingStone_Wheel.p3d";
		overrideDrawArea="8.0";
		weight=2500;
		weightPerQuantityUnit=0.51999998;
		itemSize[]={2,2};
		stackedUnit="w";
		quantityBar=1;
		varQuantityMin=0;
		varQuantityMax=20;
		varQuantityInit=20;
		varQuantityDestroyOnMin=0;
		inventorySlot[]=
		{
			"FMS_GrindingStoneWheel"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace_Set\Data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace_Set\Data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace_Set\Data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace_Set\Data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace_Set\Data\FMS_Furnace.rvmat"
							}
						}
					};
				};
			};
		};
		soundImpactType="metal";
	};
};
