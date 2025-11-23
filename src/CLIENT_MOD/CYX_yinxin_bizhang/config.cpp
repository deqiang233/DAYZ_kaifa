class CfgPatches
{
	class CYX_yinxin_bizhang
	{
		units[]=
		{
			"CYX_yinxin_bizhang"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Characters",
			"DZ_Scripts",
			"DZ_Data",
			"DZ_Characters_Backpacks",
			"DZ_Characters_Pants",
			"DZ_Characters_Tops",
			"DZ_Characters_Headgear",
			"DZ_Characters_Belts"
		};
	};
	class sample_slot
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts","DZ_Gear_Medical","DZ_Characters_Masks","DZ_Gear_Consumables","DZ_Characters"};
	};
};

class CfgMods
{
	class CYX_yinxin_bizhang
	{
		dir="CYX_yinxin_bizhang";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="CYX_yinxin_bizhang";
		credits="CYX_yinxin_bizhang";
		author="Meru";
		authorID="0";
		version="1.0";
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
			class gameScriptModule {
				value = "";
				files[] = {"CYX_yinxin_bizhang/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"CYX_yinxin_bizhang\scripts\4_World"
				};
			};
			class missionScriptModule {
				value = "";
				files[] = {"CYX_yinxin_bizhang/scripts/5_Mission"};
			};
		};
	};
};

// 自定义按键绑定配置
class CfgUserActions
{
	class User5
	{
		priority = 1;
		userActionID = 5;
		analogChangeThreshold = 0.01;
	};
};

class UserActionInput
{
	class UACYX_TestKey
	{
		actionName = "CYX测试按键";
		input = "User5";
		priority = 1;
	};
};


class CfgSlots
{
	class Slot_sample_Pouch
	{
		name="sample_Pouch";
		displayName="能力宝石";
		ghostIcon="set:dayz_inventory image:pouches";
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Inventory_Base;
	class AssaultBag_ColorBase;
	class BallisticHelmet_Green;
	class WorkingGloves_Black;
	class NBCJacketYellow;
	class NBCBootsYellow;
	class NBCPantsYellow;
	class NBCGlovesYellow;
	class NBCHoodYellow;
	class LeatherBelt_ColorBase;
	class Man;
	class SurvivorBase: Man
	{
		attachments[]+=
		{
			"sample_Pouch"
		};
		class InventoryEquipment
		{
			playerSlots[]+=
			{
				"Slot_sample_Pouch"
			};
		};
	};
	class Clothing: Clothing_Base
	{
	};
	class CYX_yinxin_bizhang: AssaultBag_ColorBase
	{
		displayName="隐形臂章";
		descriptionShort="具有无限体力 跳高功能";
		model="CYX_yinxin_bizhang\FENG_Bag_g.p3d";
		itemsCargoSize[]={10,100};
		heatIsolation=0.89999998;
		scope=2;
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		inventorySlot[]=
		{
			"Armband"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 999999999;
				};
			};
		};
		attachments[]=
		{
		};
		class ClothingTypes
		{
			male="CYX_yinxin_bizhang\FENG_Bag.p3d";
			female="CYX_yinxin_bizhang\FENG_Bag.p3d";
		};
	};
	class CYX_baoshi_v1: AssaultBag_ColorBase
	{
		displayName="能力宝石v1";
		descriptionShort="能力宝石v1_可以无需吃喝自动恢复";
		model="CYX_yinxin_bizhang\FENG_Bag_g.p3d";
		itemsCargoSize[]={0,0};
		heatIsolation=0.89999998;
		scope=2;
		itemInfo[]=
		{
			"Clothing",
			"sample_Pouch"
		};
		inventorySlot[]=
		{
			"sample_Pouch"
		};
	};
	class CYX_baoshi_v2: CYX_baoshi_v1
	{
		displayName="能力宝石v2";
		descriptionShort="能力宝石v2_无需吃喝_缓慢回血";
	};
	class CYX_baoshi_v3: CYX_baoshi_v1
	{
		displayName="能力宝石v3";
		descriptionShort="能力宝石v2_无需吃喝_缓慢回血_缓慢回健康";
	};
	class CYX_baoshi_v4: CYX_baoshi_v1
	{
		displayName="能力宝石v4";
		descriptionShort="能力宝石v4_无需吃喝_缓慢回血_缓慢回健康";
	};

};

// 自定义坠落伤害弹药类型 - 免疫坠落伤害
class CfgAmmo
{
	class FallDamage;
	class FallDamageCYX: FallDamage
	{
		class DamageApplied
		{
			type="Falling";
			class Health
			{
				damage=0;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
};