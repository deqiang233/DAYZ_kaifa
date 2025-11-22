class CfgPatches
{
	class FMS_PickAxe
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Melee_Blade"
		};
	};
};
class CfgVehicles
{
	class Pickaxe;
	class CYX_wakuanggao_t1: Pickaxe
	{
		scope=2;
		displayName="强化镐T1";
		descriptionShort="强化镐T1 500耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t2: Pickaxe
	{
		scope=2;
		displayName="强化镐T2";
		descriptionShort="强化镐T2 600耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=600;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t3: Pickaxe
	{
		scope=2;
		displayName="强化镐T3 ";
		descriptionShort="强化镐T3 700耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T1Reinforced_Iron_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=700;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t4: Pickaxe
	{
		scope=2;
		displayName="强化镐T4";
		descriptionShort="强化镐T4 800耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=800;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t5: Pickaxe
	{
		scope=2;
		displayName="强化镐T5";
		descriptionShort="强化镐T5 900耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=900;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t6: Pickaxe
	{
		scope=2;
		displayName="强化镐T6";
		descriptionShort="强化镐T6 1000耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T2Crystalforge_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t7: Pickaxe
	{
		scope=2;
		displayName="强化镐T7";
		descriptionShort="强化镐T7 1100耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t8: Pickaxe
	{
		scope=2;
		displayName="强化镐T8";
		descriptionShort="强化镐T8 1200耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t9: Pickaxe
	{
		scope=2;
		displayName="强化镐T9";
		descriptionShort="强化镐T9 1300耐久度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1300;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CYX_wakuanggao_t10: Pickaxe
	{
		scope=2;
		displayName="强化镐T10_最终镐";
		descriptionShort="强化镐T10 150000耐久度 超快的速度";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa",
			"MrfreezeMiningSystemV2\FMS_Data\FMS_PickAxe\data\Freeze_T3Fusioncore_Pickaxe.paa"
		};
		itemSize[]={3,6};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=150000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\melee\blade\data\axe.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\melee\blade\data\axe_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_damage.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\melee\blade\data\axe_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_metal_destruct.rvmat",
								"DZ\weapons\melee\blade\data\axe_view_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};

};
