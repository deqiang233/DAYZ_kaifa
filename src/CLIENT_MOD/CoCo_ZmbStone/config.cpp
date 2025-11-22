class CfgPatches
{
	class CoCo_ZmbStone
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Consumables"
		};
	};
};

class CfgMods
{
	class CoCo_ZmbStone
	{
		dir = "CoCo_ZmbStone";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "CoCo Zombie Stone Thrower";
		credits = "CoCo";
		author = "CoCo";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		
		class defs
		{	
			class gameScriptModule
			{
				value = "";
				files[] = 
				{
					"CoCo_ZmbStone/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] = 
				{
					"CoCo_ZmbStone/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{
					"CoCo_ZmbStone/Scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Stone;
	class CoCo_ThrownStone: Stone
	{
		scope=2;
	};
};

