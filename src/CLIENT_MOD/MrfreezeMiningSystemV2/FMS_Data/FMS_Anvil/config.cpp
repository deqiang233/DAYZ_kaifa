class CfgPatches
{
	class FMS_Anvil
	{
		units[]=
		{
			"FreezeAnvil"
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
	class FreezeAnvil: Inventory_Base
	{
		scope=2;
		displayName="铁砧";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\FMS_Anvil.p3d";
		descriptionShort="用于将金属块锻造成金属锭。DayZ挖矿系统使用。";
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
			"FMS_Anvil_HammerActive",
			"FMS_Anvil_HammerSpare",
			"Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class SlotGrindingStoneWheel
			{
				name="锻造锤";
				description="安装锤子";
				attachmentSlots[]=
				{
					"FMS_Anvil_HammerActive",
					"FMS_Anvil_HammerSpare"
				};
				icon="set:fms_icon_set image:fms_hammer_icon";
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeProp_Anvil: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\FMS_Anvil.p3d";
	};
	class FreezeAnvil_Static: Inventory_Base
	{
		scope=2;
		displayName="铁砧";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\FMS_Anvil.p3d";
		descriptionShort="用于将金属块锻造成金属锭。DayZ挖矿系统使用。";
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\Data\Anvil\FMS_Anvil_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class FreezeAnvil_Kit_Holo: Inventory_Base
	{
		scope=0;
		displayName="FreezeAnvil HOLO";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Anvil\FMS_Anvil.p3d";
	};
};
