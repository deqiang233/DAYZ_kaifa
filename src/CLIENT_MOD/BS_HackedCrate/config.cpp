class CfgPatches
{
	class BS_HackedCrate
	{
		units[]=
		{
			"BS_Hacked_Crate",
			"BS_Hacked_Crate_Red",
			"BS_Hacked_Crate_Blue",
			"BS_Hacked_Crate_Black",
			"BS_Hacked_Crate_White",
			"BS_Hacked_Crate_Tan"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class BS_HackedCrate
	{
		dir="BS_HackedCrate";
		hideName=1;
		hidePicture=1;
		name="Bastardos Hacked Crate";
		credits="";
		author="CJCARW";
		authorID="0";
		version="2.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"BS_HackedCrate/Scripts/3_game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"BS_HackedCrate/Scripts/Common",
					"BS_HackedCrate/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"BS_HackedCrate/Scripts/Common/HC_Define.c",
					"BS_HackedCrate/Scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Container_Base;
	class WorldContainer_Base;
	class HackedCrateClose_Base: Container_Base
	{
		scope=0;
		hologramMaterial="wooden_case";
		hologramMaterialPath="dz\gear\camping\data";
		forceFarBubble="true";
		slopeTolerance=0.40000001;
		yawPitchRollLimit[]={45,45,45};
		itemSize[]={10,5};
		repairableWithKits[]={10};
		weight=10000;
		repairCosts[]={30};
		itemBehaviour=1;
		carveNavmesh=1;
		alignHologramToTerain=1;
		canBeDigged=0;
		rotationFlags=2;
		itemIsOpenable=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=13000;
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
					class Blood
					{
						damage=8;
					};
					class Shock
					{
						damage=8;
					};
				};
			};
		};
		class AnimationSources
		{
			class Lid
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class Lid2
			{
				source="user";
				initPhase=1;
				animPeriod=0.0099999998;
			};
		};
		soundImpactType="metal";
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class HackedCrate_Base: HackedCrateClose_Base
	{
		scope=0;
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		model="BS_HackedCrate\HackedCrate.p3d";
		hiddenSelections[]=
		{
			"timer_tenthminutes",
			"timer_onesminutes",
			"spacer",
			"timer_tenthseconds",
			"timer_onesseconds",
			"lock"
		};
		slopeTolerance=0.40000001;
		itemBehaviour=0;
		yawPitchRollLimit[]={45,45,45};
		canBeDigged=0;
		heavyItem=1;
		carveNavmesh=1;
		weight=12000;
		physLayer="item_large";
		alignHologramToTerain=1;
		itemIsOpenable=1;
		hiddenSelectionsTextures[]=
		{
			"BS_HackedCrate\data\1.paa",
			"BS_HackedCrate\data\5.paa",
			"BS_HackedCrate\data\colon.paa",
			"BS_HackedCrate\data\0.paa",
			"BS_HackedCrate\data\0.paa",
			"BS_HackedCrate\Rust\data\crate\lock_locked_co.paa"
		};
		class Cargo
		{
			itemsCargoSize[]={10,100};
			allowOwnedCargoManipulation=1;
		};
	};
	class BS_Hacked_Crate: HackedCrate_Base
	{
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
	class BS_Hacked_Crate_Red: HackedCrate_Base
	{
		model="BS_HackedCrate\HackedCrate_Red.p3d";
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
	class BS_Hacked_Crate_Blue: HackedCrate_Base
	{
		model="BS_HackedCrate\HackedCrate_Blue.p3d";
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
	class BS_Hacked_Crate_Black: HackedCrate_Base
	{
		model="BS_HackedCrate\HackedCrate_Black.p3d";
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
	class BS_Hacked_Crate_White: HackedCrate_Base
	{
		model="BS_HackedCrate\HackedCrate_White.p3d";
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
	class BS_Hacked_Crate_Tan: HackedCrate_Base
	{
		model="BS_HackedCrate\HackedCrate_Tan.p3d";
		displayName="#STR_BSHC_HackedCrate_DisplayName";
		descriptionShort="#STR_BSHC_HackedCrate_Description";
		scope=2;
	};
};
