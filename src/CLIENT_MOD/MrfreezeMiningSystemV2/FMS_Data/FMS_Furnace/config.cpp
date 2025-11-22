class CfgPatches
{
	class FMS_Furnace
	{
		units[]=
		{
			"FreezeFurnace"
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
	class Container_Base;
	class LargeGasCanister;
	class Hammer;
	class FreezeProp_Furnace: HouseNoDestruct
	{
		scope=2;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace.p3d";
	};
	class FreezeFurnace: Inventory_Base
	{
		scope=2;
		displayName="熔炉";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace_Only.p3d";
		descriptionShort="将同类型的矿石填满四个槽位即可熔炼成金属块，可同时处理4种类型。用于DayZ挖矿系统。";
		canBeDigged=0;
		carveNavmesh=1;
		overrideDrawArea="8.0";
		placement="ForceSlopeOnTerrain";
		destroyOnEmpty=0;
		quantityBar=0;
		varQuantityMax=0;
		heavyItem=1;
		weight=10000;
		itemBehaviour=0;
		physLayer="item_large";
		attachments[]=
		{
			"FMS_Propane_Canister",
			"FMS_Propane_Pipe",
			"FMS_FurnaceHammer1",
			"FMS_FurnaceHammer2",
			"FMS_FurnaceHammer3",
			"Freezestone_gold",
			"Freezestone_gold1",
			"Freezestone_gold2",
			"Freezestone_gold3",
			"Freezestone_silver",
			"Freezestone_silver1",
			"Freezestone_silver2",
			"Freezestone_silver3",
			"Freezestone_copper",
			"Freezestone_copper1",
			"Freezestone_copper2",
			"Freezestone_copper3",
			"Freezestone_tin",
			"Freezestone_tin1",
			"Freezestone_tin2",
			"Freezestone_tin3",
			"Freezestone_iron",
			"Freezestone_iron1",
			"Freezestone_iron2",
			"Freezestone_iron3",
			"Freezestone_base",
			"Freezestone_base1",
			"Freezestone_base2",
			"Freezestone_base3",
			"Freezestone_uranium",
			"Freezestone_uranium1",
			"Freezestone_uranium2",
			"Freezestone_uranium3",
			"Freezestone_sulphur",
			"Freezestone_sulphur1",
			"Freezestone_sulphur2",
			"Freezestone_sulphur3",
			"Truck_01_WoodenCrate1",
			"Truck_01_WoodenCrate2",
			"Truck_01_WoodenCrate3",
			"Truck_01_WoodenCrate4"
		};
		class GUIInventoryAttachmentsProps
		{
			class SlotPropane_Canister
			{
				name="丙烷罐和管道";
				description="安装丙烷罐和管道";
				attachmentSlots[]=
				{
					"FMS_Propane_Canister",
					"FMS_Propane_Pipe",
					"FMS_FurnaceHammer1",
					"FMS_FurnaceHammer2",
					"FMS_FurnaceHammer3"
				};
				icon="set:fms_icon_set image:fms_furnace_icon";
			};
			class GoldProcessing_Storage
			{
				name="金矿石处理";
				description="填入金矿石";
				attachmentSlots[]=
				{
					"Freezestone_gold",
					"Freezestone_gold1",
					"Freezestone_gold2",
					"Freezestone_gold3"
				};
				icon="stones";
			};
			class TinProcessing_Storage
			{
				name="锡矿石处理";
				description="填入锡矿石";
				attachmentSlots[]=
				{
					"Freezestone_tin",
					"Freezestone_tin1",
					"Freezestone_tin2",
					"Freezestone_tin3"
				};
				icon="stones";
			};
			class IronProcessing_Storage
			{
				name="铁矿石处理";
				description="填入铁矿石";
				attachmentSlots[]=
				{
					"Freezestone_iron",
					"Freezestone_iron1",
					"Freezestone_iron2",
					"Freezestone_iron3"
				};
				icon="stones";
			};
			class SilverProcessing_Storage
			{
				name="银矿石处理";
				description="填入银矿石";
				attachmentSlots[]=
				{
					"Freezestone_silver",
					"Freezestone_silver1",
					"Freezestone_silver2",
					"Freezestone_silver3"
				};
				icon="stones";
			};
			class CopperProcessing_Storage
			{
				name="Copper Processing";
				description="Fill with Copper Ore";
				attachmentSlots[]=
				{
					"Freezestone_copper",
					"Freezestone_copper1",
					"Freezestone_copper2",
					"Freezestone_copper3"
				};
				icon="stones";
			};
			class uraniumProcessing_Storage
			{
				name="Uranium Processing";
				description="Fill with Uranium Ore";
				attachmentSlots[]=
				{
					"Freezestone_uranium",
					"Freezestone_uranium1",
					"Freezestone_uranium2",
					"Freezestone_uranium3"
				};
				icon="stones";
			};
			class sulphurProcessing_Storage
			{
				name="Sulphur Processing";
				description="Fill with Sulphur Ore";
				attachmentSlots[]=
				{
					"Freezestone_sulphur",
					"Freezestone_sulphur1",
					"Freezestone_sulphur2",
					"Freezestone_sulphur3"
				};
				icon="stones";
			};
			class Wooden_Crate_Storage
			{
				name="木箱";
				description="木箱存储";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenCrate2",
					"Truck_01_WoodenCrate3",
					"Truck_01_WoodenCrate4"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeFurnace_Static: Inventory_Base
	{
		scope=2;
		displayName="熔炉（静态）";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace.p3d";
		descriptionShort="将同类型的矿石填满四个槽位即可熔炼成金属块，可同时处理4种类型。用于DayZ挖矿系统。";
		itemsCargoSize[]={10,5};
		canBeDigged=0;
		carveNavmesh=1;
		overrideDrawArea="8.0";
		placement="ForceSlopeOnTerrain";
		destroyOnEmpty=0;
		quantityBar=0;
		varQuantityMax=0;
		heavyItem=1;
		weight=10000;
		itemBehaviour=0;
		physLayer="item_large";
		allowOwnedCargoManipulation=1;
		attachments[]=
		{
			"Freezestone_gold",
			"Freezestone_gold1",
			"Freezestone_gold2",
			"Freezestone_gold3",
			"Freezestone_silver",
			"Freezestone_silver1",
			"Freezestone_silver2",
			"Freezestone_silver3",
			"Freezestone_copper",
			"Freezestone_copper1",
			"Freezestone_copper2",
			"Freezestone_copper3",
			"Freezestone_tin",
			"Freezestone_tin1",
			"Freezestone_tin2",
			"Freezestone_tin3",
			"Freezestone_iron",
			"Freezestone_iron1",
			"Freezestone_iron2",
			"Freezestone_iron3",
			"Freezestone_base",
			"Freezestone_base1",
			"Freezestone_base2",
			"Freezestone_base3",
			"Freezestone_uranium",
			"Freezestone_uranium1",
			"Freezestone_uranium2",
			"Freezestone_uranium3",
			"Freezestone_sulphur",
			"Freezestone_sulphur1",
			"Freezestone_sulphur2",
			"Freezestone_sulphur3"
		};
		class GUIInventoryAttachmentsProps
		{
			class GoldProcessing_Storage
			{
				name="金矿石处理";
				description="填入金矿石";
				attachmentSlots[]=
				{
					"Freezestone_gold",
					"Freezestone_gold1",
					"Freezestone_gold2",
					"Freezestone_gold3"
				};
				icon="stones";
			};
			class TinProcessing_Storage
			{
				name="锡矿石处理";
				description="填入锡矿石";
				attachmentSlots[]=
				{
					"Freezestone_tin",
					"Freezestone_tin1",
					"Freezestone_tin2",
					"Freezestone_tin3"
				};
				icon="stones";
			};
			class IronProcessing_Storage
			{
				name="铁矿石处理";
				description="填入铁矿石";
				attachmentSlots[]=
				{
					"Freezestone_iron",
					"Freezestone_iron1",
					"Freezestone_iron2",
					"Freezestone_iron3"
				};
				icon="stones";
			};
			class SilverProcessing_Storage
			{
				name="银矿石处理";
				description="填入银矿石";
				attachmentSlots[]=
				{
					"Freezestone_silver",
					"Freezestone_silver1",
					"Freezestone_silver2",
					"Freezestone_silver3"
				};
				icon="stones";
			};
			class CopperProcessing_Storage
			{
				name="铜矿石处理";
				description="填入铜矿石";
				attachmentSlots[]=
				{
					"Freezestone_copper",
					"Freezestone_copper1",
					"Freezestone_copper2",
					"Freezestone_copper3"
				};
				icon="stones";
			};
			class uraniumProcessing_Storage
			{
				name="铀矿石处理";
				description="填入铀矿石";
				attachmentSlots[]=
				{
					"Freezestone_uranium",
					"Freezestone_uranium1",
					"Freezestone_uranium2",
					"Freezestone_uranium3"
				};
				icon="stones";
			};
			class sulphurProcessing_Storage
			{
				name="硫矿石处理";
				description="填入硫矿石";
				attachmentSlots[]=
				{
					"Freezestone_sulphur",
					"Freezestone_sulphur1",
					"Freezestone_sulphur2",
					"Freezestone_sulphur3"
				};
				icon="stones";
			};
		};
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\data\FMS_Furnace_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeFurnace_Kit_Holo: Inventory_Base
	{
		scope=0;
		displayName="FreezeFurnace HOLO";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace_Only.p3d";
	};
	class FreezeFurnace_Canister: Inventory_Base
	{
		scope=2;
		displayName="丙烷罐";
		descriptionShort="用于为熔炉提供燃料的大型丙烷罐。包含20单位燃料。DayZ挖矿系统使用。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Propane_Canister.p3d";
		overrideDrawArea="8.0";
		weight=1000;
		weightPerQuantityUnit=0.51999998;
		itemSize[]={2,4};
		stackedUnit="w";
		quantityBar=1;
		varQuantityMin=0;
		varQuantityMax=20;
		varQuantityInit=20;
		varQuantityDestroyOnMin=0;
		inventorySlot[]=
		{
			"FMS_Propane_Canister"
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
	class FreezeFurnace_Pipe: Inventory_Base
	{
		scope=2;
		displayName="丙烷连接管道";
		descriptionShort="连接丙烷罐和熔炉的管道。熔炉运行所需。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Propane_Pipe.p3d";
		weight=1500;
		itemSize[]={2,2};
		inventorySlot[]=
		{
			"FMS_Propane_Pipe"
		};
		isMeleeWeapon=1;
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
	};
	class FreezeHammer: Hammer
	{
		scope=2;
		displayName="挖矿锤";
		descriptionShort="用于挖矿和锻造的重型锤子。也可用作工具或武器。DayZ挖矿系统使用。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace_Hammer.p3d";
		inventorySlot[]=
		{
			"FMS_FurnaceHammer1",
			"FMS_FurnaceHammer2",
			"FMS_FurnaceHammer3",
			"FMS_Anvil_HammerActive",
			"FMS_Anvil_HammerSpare"
		};
		isMeleeWeapon=1;
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
	};
	class FreezeFurnaceTongs: Hammer
	{
		scope=2;
		displayName="铁匠钳";
		descriptionShort="用于在熔炉中处理热金属的重型钳子。铁匠必备工具。DayZ挖矿系统使用。";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Furnace\FMS_Furnace_Tongs.p3d";
		inventorySlot[]=
		{
			"FMS_Furnace_Tongs"
		};
		isMeleeWeapon=1;
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
	};
};
