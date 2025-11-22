class CfgPatches
{
	class Freezestone_base
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
	class Stone;
	class Freezestone_base: Stone
	{
		scope=0;
		displayName="Don't Use this Ore rock";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\FMS_Stone_Base.p3d";
		descriptionShort="Ore you get from mining the nodes, Place in furnace to smelt into nuggets. Used by DayZ Mining System";
		itemSize[]={1,1};
		weight=1;
		canBeSplit=1;
		varStackMax=10;
		varQuantityDestroyOnMin=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10;
		inventorySlot[]=
		{
			"Freezestone_base",
			"Freezestone_base1",
			"Freezestone_base2",
			"Freezestone_base3"
		};
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\Data\FMS_Stone_Base.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\Data\FMS_Stone_Base.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\Data\FMS_Stone_Base.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\Data\FMS_Stone_Base.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Base\Data\FMS_Stone_Base.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_copper: Freezestone_base
	{
		scope=2;
		displayName="铜矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\FMS_Stone_Copper.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_copper",
			"Freezestone_copper1",
			"Freezestone_copper2",
			"Freezestone_copper3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\Data\FMS_Stone_Copper.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\Data\FMS_Stone_Copper.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\Data\FMS_Stone_Copper.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\Data\FMS_Stone_Copper.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Copper\Data\FMS_Stone_Copper.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_gold: Freezestone_base
	{
		scope=2;
		displayName="金矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\FMS_Stone_Gold.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_gold",
			"Freezestone_gold1",
			"Freezestone_gold2",
			"Freezestone_gold3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\Data\FMS_Stone_Gold.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\Data\FMS_Stone_Gold.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\Data\FMS_Stone_Gold.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\Data\FMS_Stone_Gold.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Gold\Data\FMS_Stone_Gold.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_iron: Freezestone_base
	{
		scope=2;
		displayName="铁矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\FMS_Stone_Iron.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_iron",
			"Freezestone_iron1",
			"Freezestone_iron2",
			"Freezestone_iron3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\Data\FMS_Stone_Iron.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\Data\FMS_Stone_Iron.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\Data\FMS_Stone_Iron.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\Data\FMS_Stone_Iron.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Iron\Data\FMS_Stone_Iron.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_silver: Freezestone_base
	{
		scope=2;
		displayName="银矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\FMS_Stone_Silver.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_silver",
			"Freezestone_silver1",
			"Freezestone_silver2",
			"Freezestone_silver3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\Data\FMS_Stone_Silver.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\Data\FMS_Stone_Silver.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\Data\FMS_Stone_Silver.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\Data\FMS_Stone_Silver.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Silver\Data\FMS_Stone_Silver.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_tin: Freezestone_base
	{
		scope=2;
		displayName="锡矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\FMS_Stone_Tin.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_tin",
			"Freezestone_tin1",
			"Freezestone_tin2",
			"Freezestone_tin3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\Data\FMS_Stone_Tin.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\Data\FMS_Stone_Tin.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\Data\FMS_Stone_Tin.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\Data\FMS_Stone_Tin.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Tin\Data\FMS_Stone_Tin.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_uranium: Freezestone_base
	{
		scope=2;
		displayName="铀矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\FMS_Stone_Uranium.p3d";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_uranium",
			"Freezestone_uranium1",
			"Freezestone_uranium2",
			"Freezestone_uranium3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\Data\FMS_Stone_Uranium.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\Data\FMS_Stone_Uranium.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\Data\FMS_Stone_Uranium.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\Data\FMS_Stone_Uranium.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Uranium\Data\FMS_Stone_Uranium.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Freezestone_sulphur: Freezestone_base
	{
		scope=2;
		displayName="硫矿石";
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\FMS_Stone_Sulphur.p3d";
		descriptionShort="从挖矿节点获得的硫矿石。用于DayZ挖矿系统";
		weight=4;
		inventorySlot[]=
		{
			"Freezestone_sulphur",
			"Freezestone_sulphur1",
			"Freezestone_sulphur2",
			"Freezestone_sulphur3"
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
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\Data\FMS_Stone_Sulphur.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\Data\FMS_Stone_Sulphur.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\Data\FMS_Stone_Sulphur.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\Data\FMS_Stone_Sulphur.rvmat"
							}
						},
						
						{
							0,
							
							{
								"MrfreezeMiningSystemV2\FMS_Data\FMS_Stone\FMS_Stone_Sulphur\Data\FMS_Stone_Sulphur.rvmat"
							}
						}
					};
				};
			};
		};
	};
};
