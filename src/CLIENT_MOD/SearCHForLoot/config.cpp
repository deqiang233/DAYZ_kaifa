class CfgPatches
{
	class SearchForLoot
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Sounds_Effects",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class SearchForLoot
	{
		dir="SearchForLoot";
		picture="";
		action="";
		hideName=0;
		hidePicture=0;
		name="SearchForLoot";
		credits="Hunterz";
		author="Hunterz";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ND_Clans/scripts/Common",
					"SearchForLoot/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ND_Clans/scripts/Common",
					"SearchForLoot/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ND_Clans/scripts/Common",
					"SearchForLoot/Scripts/5_Mission"
				};
			};
		};
	};
};
class CfgSFLProxies
{
	proxies[]=
	{
		"static_case_bedroom_a",
		"static_dhangar_brownskrin_old",
		"static_almara_open",
		"static_almara",
		"static_desk_office",
		"static_fridge",
		"static_kitchenstove_elec",
		"static_shelf_dz",
		"static_table_drawer",
		"static_conference_table_a",
		"static_phonebox",
		"static_case_a_open",
		"static_library_a_open",
		"static_case_a",
		"static_tools_racking_dz",
		"static_box_c",
		"static_skrin_bar",
		"static_dhangar_brownskrin",
		"static_case_d",
		"static_rack_dz",
		"static_locker_closed_v1",
		"static_basin_a",
		"static_vojenska_palanda",
		"static_foldingbed_open",
		"static_class_case_a_closed",
		"static_class_case_a_open",
		"static_class_case_b_open",
		"static_shelf_1side",
		"static_case_cans_b",
		"static_box_c_multi",
		"static_case_bedroom_b",
		"static_bucket",
		"static_office_table_a",
		"static_library_a",
		"static_shelf",
		"static_locker_closed_blue_v1",
		"static_locker_open_blue_v2",
		"static_metalcase_01",
		"static_metalcase_02",
		"static_workbench",
		"static_metalcrate",
		"static_workbench_dz",
		"static_class_case_b_closed",
		"static_truck_01_aban_1_lod1parts_fire",
		"static_lab_bench",
		"static_washing_machine",
		"static_shelfs_small",
		"static_matress_white_bent",
		"static_classroom_case_a",
		"static_hospital_transport_bed",
		"static_metalcrate_02",
		"static_locker_closed_v2",
		"static_locker_open_v2",
		"static_school_cage",
		"static_lab_teacher_bench",
		"static_teacher_desk",
		"static_locker_closed_v3",
		"static_locker_open_v3",
		"static_koz",
		"static_pipe-small",
		"static_pipe-big",
		"static_wheel_cart_dz",
		"static_kitchen_unit_a_dz",
		"static_medical_table",
		"static_lekarnicka",
		"static_tent_strecher",
		"static_tent_gunrack",
		"static_tent_boxwooden",
		"static_table_umakart",
		"static_misc_boxwooden"
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class SearchingForLoot_SoundShader5: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"SearchForLoot\sounds\junkrummage5",
				1
			}
		};
		volume=1.5;
		range=10;
		rangeCurve[]=
		{
			{0,1},
			{0.5,0.69999999},
			{1,0}
		};
	};
	class SearchingForLoot_SoundShader4: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"SearchForLoot\sounds\junkrummage4",
				1
			}
		};
		volume=1.5;
		range=10;
		rangeCurve[]=
		{
			{0,1},
			{0.5,0.69999999},
			{1,0}
		};
	};
	class SearchingForLoot_SoundShader3: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"SearchForLoot\sounds\junkrummage3",
				1
			}
		};
		volume=1.5;
		range=10;
		rangeCurve[]=
		{
			{0,1},
			{0.5,0.69999999},
			{1,0}
		};
	};
	class SearchingForLoot_SoundShader2: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"SearchForLoot\sounds\junkrummage2",
				1
			}
		};
		volume=1.5;
		range=10;
		rangeCurve[]=
		{
			{0,1},
			{0.5,0.69999999},
			{1,0}
		};
	};
};
class CfgSoundSets
{
	class baseCharacter_SoundSet;
	class SearchingForLoot_SoundSet5: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"SearchingForLoot_SoundShader5"
		};
	};
	class SearchingForLoot_SoundSet4: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"SearchingForLoot_SoundShader4"
		};
	};
	class SearchingForLoot_SoundSet3: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"SearchingForLoot_SoundShader3"
		};
	};
	class SearchingForLoot_SoundSet2: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"SearchingForLoot_SoundShader2"
		};
	};
};
