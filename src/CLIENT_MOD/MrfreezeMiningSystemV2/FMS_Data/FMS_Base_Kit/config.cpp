class CfgPatches
{
	class FMS_Base_Kit
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class Container_Base;
	class WoodenCrate: Container_Base
	{
		hiddenSelections[]=
		{
			"camoGround"
		};
	};
	class FreezeMining_Kit_Base: WoodenCrate
	{
		scope=0;
		displayName="";
		descriptionShort="";
		model="\DZ\gear\camping\wooden_case.p3d";
		hiddenSelections[]=
		{
			"camoGround"
		};
		itemSize[]={3,2};
		carveNavmesh=1;
		canBeDigged=0;
		simulation="inventoryItem";
		physLayer="item_small";
		SingleUseActions[]={527};
		ContinuousActions[]={231};
		rotationFlags=2;
		InteractActions[]={};
		weight=300;
		itemBehaviour=2;
		class Cargo
		{
		};
	};
	class FreezeFurnace_Kit: FreezeMining_Kit_Base
	{
		scope=2;
		displayName="熔炉套件";
		descriptionShort="熔炉套件可以部署，用于将矿石熔炼成金属块";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Base_Kit\Data\FreezeFurnace_Kit.paa"
		};
	};
	class FreezeAnvil_Kit: FreezeMining_Kit_Base
	{
		scope=2;
		displayName="铁砧套件";
		descriptionShort="铁砧套件可以部署，用于将金属块锻造成金属锭。";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Base_Kit\Data\FreezeAnvil_Kit.paa"
		};
	};
	class FreezeGrindingStone_Kit: FreezeMining_Kit_Base
	{
		scope=2;
		displayName="磨石套件";
		descriptionShort="磨石可以切割原始宝石。";
		hiddenSelectionsTextures[]=
		{
			"MrfreezeMiningSystemV2\FMS_Data\FMS_Base_Kit\Data\FreezeGrindingStone_Kit.paa"
		};
	};
};
