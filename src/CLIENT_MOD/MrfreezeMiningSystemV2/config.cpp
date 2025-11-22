class CfgPatches
{
	class MrfreezeMiningSystemV2
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Cooking",
			"DZ_Rocks",
			"DZ_Sounds_Effects",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class MrfreezeMiningSystemV2
	{
		dir="MrfreezeMiningSystemV2";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="MrfreezeMiningSystemV2";
		credits="MrFreezeGamesPC & FUBAR";
		author="MrFreezeGamesPC";
		authorID="https://steamcommunity.com/id/MrFreezeGamesPC/";
		version="0.1";
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
			class imageSets
			{
				files[]=
				{
					"MrfreezeMiningSystemV2\ImageSets\fms_icons.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"MrfreezeMiningSystemV2\Scripts\3_game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"MrfreezeMiningSystemV2\Scripts\4_world"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"MrfreezeMiningSystemV2\Scripts\5_mission"
				};
			};
		};
	};
};
class CfgSounds
{
	sounds[]={};
	class FreezeFurnace_On
	{
		name="FreezeFurnace_On";
		sound[]=
		{
			"\MrfreezeMiningSystemV2\sounds\fms_furnace_on.ogg",
			1,
			1
		};
		titles[]={};
	};
	class FreezeFurnace_Off
	{
		name="FreezeFurnace_Off";
		sound[]=
		{
			"\MrfreezeMiningSystemV2\sounds\fms_furnace_on.ogg",
			1,
			1
		};
		titles[]={};
	};
	class FreezeAnvil_On
	{
		name="FreezeAnvil_On";
		sound[]=
		{
			"\MrfreezeMiningSystemV2\sounds\fms_anvil_on.ogg",
			1,
			1
		};
		titles[]={};
	};
	class FreezeGrindingStone_On
	{
		name="FreezeGrindingStone_On";
		sound[]=
		{
			"\MrfreezeMiningSystemV2\sounds\fms_grindstone_on.ogg",
			1,
			1
		};
		titles[]={};
	};
};
class CfgSoundShaders
{
	class FreezeCraftingBase_SoundShader
	{
		range=30;
		rangeCurve="linear";
	};
	class FreezeFurnace_On_SoundShader: FreezeCraftingBase_SoundShader
	{
		samples[]=
		{
			
			{
				"MrfreezeMiningSystemV2\sounds\fms_furnace_on",
				1
			}
		};
		volume=1;
	};
	class FreezeAnvil_On_SoundShader: FreezeCraftingBase_SoundShader
	{
		samples[]=
		{
			
			{
				"MrfreezeMiningSystemV2\sounds\fms_anvil_on",
				1
			}
		};
		volume=1;
	};
	class FreezeGrindingStone_On_SoundShader: FreezeCraftingBase_SoundShader
	{
		samples[]=
		{
			
			{
				"MrfreezeMiningSystemV2\sounds\fms_grindstone_on",
				1
			}
		};
		volume=1;
	};
};
class CfgSoundSets
{
	class FreezeCraftingBase_SoundSet
	{
		sound3DProcessingType="character3DProcessingType";
		distanceFilter="BaseCharacter_AttenuationFilter";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=1;
		volumeFactor=1;
	};
	class FreezeFurnace_On_SoundSet: FreezeCraftingBase_SoundSet
	{
		soundShaders[]=
		{
			"FreezeFurnace_On_SoundShader"
		};
	};
	class FreezeAnvil_On_SoundSet: FreezeCraftingBase_SoundSet
	{
		soundShaders[]=
		{
			"FreezeAnvil_On_SoundShader"
		};
	};
	class FreezeGrindingStone_On_SoundSet: FreezeCraftingBase_SoundSet
	{
		soundShaders[]=
		{
			"FreezeGrindingStone_On_SoundShader"
		};
	};
};
