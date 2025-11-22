class CfgPatches
{
	class FMS_Node
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
	class HouseNoDestruct;
	class FreezeNode_copper: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Copper\FMS_Node_Copper.p3d";
	};
	class FreezeNode_sulphur: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Sulphur\FMS_Node_Sulphur.p3d";
	};
	class FreezeNode_gold: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Gold\FMS_Node_Gold.p3d";
	};
	class FreezeNode_iron: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Iron\FMS_Node_Iron.p3d";
	};
	class FreezeNode_silver: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Silver\FMS_Node_Silver.p3d";
	};
	class FreezeNode_tin: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Tin\FMS_Node_Tin.p3d";
	};
	class FreezeNode_stone: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Stone\FMS_Node_Stone.p3d";
	};
	class FreezeNode_uranium: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Uranium\FMS_Node_Uranium.p3d";
	};
	class FreezeNode_AmberGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Amber\FMS_GemNode_Amber.p3d";
	};
	class FreezeNode_AmethystGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Amethyst\FMS_GemNode_Amethyst.p3d";
	};
	class FreezeNode_AquamarineGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Aquamrine\FMS_GemNode_Aquamrine.p3d";
	};
	class FreezeNode_FancyColourDiamondGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_FancyColourDimond\FMS_GemNode_FancyColourDimond.p3d";
	};
	class FreezeNode_IoliteGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Iolite\FMS_GemNode_Iolite.p3d";
	};
	class FreezeNode_JadeGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Jade\FMS_GemNode_Jade.p3d";
	};
	class FreezeNode_RubyGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Ruby\FMS_GemNode_Ruby.p3d";
	};
	class FreezeNode_TurquoiseGemNode: HouseNoDestruct
	{
		scope=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Turquoise\FMS_GemNode_Turquoise.p3d";
	};
	class FreezePropNode_copper: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Copper\FMS_Node_Copper.p3d";
	};
	class FreezePropNode_gold: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Gold\FMS_Node_Gold.p3d";
	};
	class FreezePropNode_iron: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Iron\FMS_Node_Iron.p3d";
	};
	class FreezePropNode_silver: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Silver\FMS_Node_Silver.p3d";
	};
	class FreezePropNode_tin: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Tin\FMS_Node_Tin.p3d";
	};
	class FreezePropNode_stone: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Stone\FMS_Node_Stone.p3d";
	};
	class FreezePropNode_uranium: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_Node_Uranium\FMS_Node_Uranium.p3d";
	};
	class FreezePropNode_AmberGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Amber\FMS_GemNode_Amber.p3d";
	};
	class FreezePropNode_AmethystGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Amethyst\FMS_GemNode_Amethyst.p3d";
	};
	class FreezePropNode_AquamrineGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Aquamrine\FMS_GemNode_Aquamrine.p3d";
	};
	class FreezePropNode_FancyColourDiamondGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_FancyColourDimond\FMS_GemNode_FancyColourDimond.p3d";
	};
	class FreezePropNode_IoliteGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Iolite\FMS_GemNode_Iolite.p3d";
	};
	class FreezePropNode_JadeGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Jade\FMS_GemNode_Jade.p3d";
	};
	class FreezePropNode_RubyGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Ruby\FMS_GemNode_Ruby.p3d";
	};
	class FreezePropNode_TurquoiseGem: HouseNoDestruct
	{
		scope=1;
		model="MrfreezeMiningSystemV2\FMS_Data\FMS_Node\FMS_GemNode_Turquoise\FMS_GemNode_Turquoise.p3d";
	};
};
