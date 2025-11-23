class CfgPatches
{
	class vzp_dron_mod_drone
	{
		units[]=
		{
			"CoCo_drone2",
			"CoCo_drone3",
			"CoCo_drone4",
			"CoCo_drone5",
			"CoCo_drone1"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Characters",
			"DZ_Scripts",
			"DZ_Vehicles_Wheeled",
			"DZ_Sounds_Effects"
		};
	};
};
class cfgVehicles
{
	class Clothing_Base;
	class Clothing: Clothing_Base
	{
	};
	class VZP_drone_ColorBase: Clothing
	{
		scope=0;
		model="vzp_dron_mod\drone\zemlya\vzpdrone_g.p3d";
		debug_ItemCategory=9;
		inventorySlot[]=
		{
			"sample_Pouch",
		}; 
		itemInfo[]=
		{
			"Clothing",
			"Back"
		};
		rotationFlags=16;
		itemSize[]={4,4};
		itemsCargoSize[]={10,50};
		weight=1000;
		varWetMax=0.0099999998;
		heatIsolation=1;
		soundAttType="Outdoor";
		hiddenSelections[]=
		{
			"camo",
			"camo2"
		};
		class ClothingTypes
		{
			male="vzp_dron_mod\drone\vzpdrone.p3d";
			female="vzp_dron_mod\drone\vzpdrone.p3d";
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500000;
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpBackPack_Metal_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpBackPack_Metal_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="taloonbag_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class CoCo_drone1: VZP_drone_ColorBase
	{
		scope=2;
		displayName="无人机";
		descriptionShort="无人机";
		hiddenSelections[]=
		{
			"camo",
			"camo2"
		};
		hiddenSelectionsTextures[]=
		{
			"vzp_dron_mod\drone\data\light\drone_light.paa",
			"vzp_dron_mod\drone\data\light\drone_light_em.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"vzp_dron_mod\drone\data\light\drone_light.rvmat",
			"vzp_dron_mod\drone\data\light\drone_lightem.rvmat"
		};
		weight=-5000000;
		itemsCargoSize[]={10,50};
		attachments[]=
		{
			"BatteryD",
			"dronammobox",
			"Shoulder",
			"Melee",
			"Belt_Left",
			"Knife"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"vzp_dron_mod\drone\data\light\drone_light.rvmat",
								"vzp_dron_mod\drone\data\light\drone_lightem.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"vzp_dron_mod\drone\data\light\drone_light.rvmat",
								"vzp_dron_mod\drone\data\light\drone_lightem.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"vzp_dron_mod\drone\data\light\drone_light.rvmat",
								"vzp_dron_mod\drone\data\light\drone_lightem.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"vzp_dron_mod\drone\data\light\drone_light.rvmat",
								"vzp_dron_mod\drone\data\light\drone_lightem.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\Characters\backpacks\data\mountain_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CoCo_drone3: VZP_drone_ColorBase
	{
		scope=2;
		displayName="$STR_MagnetDrone_Name";
		descriptionShort="$STR_MagnetDrone_Desc";
		hiddenSelectionsTextures[]=
		{
			"vzp_dron_mod\drone\data\magnet\drone_magnet.paa",
			"vzp_dron_mod\drone\data\magnet\drone_magnet_em.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"vzp_dron_mod\drone\data\magnet\drone_magnet.rvmat",
			"vzp_dron_mod\drone\data\magnet\drone_magnetem.rvmat"
		};
		weight=1000;
		itemsCargoSize[]={10,50};
		attachments[]=
		{
			"BatteryD",
			"Shoulder",
			"Melee",
			"Knife"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"vzp_dron_mod\drone\data\magnet\drone_magnet.rvmat",
								"vzp_dron_mod\drone\data\magnet\drone_magnetem.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"vzp_dron_mod\drone\data\magnet\drone_magnet.rvmat",
								"vzp_dron_mod\drone\data\magnet\drone_magnetem.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"vzp_dron_mod\drone\data\magnet\drone_magnet.rvmat",
								"vzp_dron_mod\drone\data\magnet\drone_magnetem.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"vzp_dron_mod\drone\data\magnet\drone_magnet.rvmat",
								"vzp_dron_mod\drone\data\magnet\drone_magnetem.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\Characters\backpacks\data\mountain_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CoCo_drone4: VZP_drone_ColorBase
	{
		scope=2;
		displayName="$STR_MedicalDrone_Name";
		descriptionShort="$STR_MedicalDrone_Desc";
		hiddenSelectionsTextures[]=
		{
			"vzp_dron_mod\drone\data\medical\drone_medical.paa",
			"vzp_dron_mod\drone\data\medical\drone_medical_em.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"vzp_dron_mod\drone\data\medical\drone_medical.rvmat",
			"vzp_dron_mod\drone\data\medical\drone_medicalem.rvmat"
		};
		weight=1000;
		itemsCargoSize[]={10,50};
		attachments[]=
		{
			"BatteryD",
			"Shoulder",
			"Melee",
			"Belt_Left",
			"dronmedspas1"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"vzp_dron_mod\drone\data\medical\drone_medical.rvmat",
								"vzp_dron_mod\drone\data\medical\drone_medicalem.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"vzp_dron_mod\drone\data\medical\drone_medical.rvmat",
								"vzp_dron_mod\drone\data\medical\drone_medicalem.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"vzp_dron_mod\drone\data\medical\drone_medical.rvmat",
								"vzp_dron_mod\drone\data\medical\drone_medicalem.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"vzp_dron_mod\drone\data\medical\drone_medical.rvmat",
								"vzp_dron_mod\drone\data\medical\drone_medicalem.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\Characters\backpacks\data\mountain_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class CoCo_drone5: VZP_drone_ColorBase
	{
		scope=2;
		displayName="$STR_MilitaryDrone_Name";
		descriptionShort="$STR_MilitaryDrone_Desc";
		hiddenSelectionsTextures[]=
		{
			"vzp_dron_mod\drone\data\military\drone_military.paa",
			"vzp_dron_mod\drone\data\military\drone_military_em.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"vzp_dron_mod\drone\data\military\drone_military.rvmat",
			"vzp_dron_mod\drone\data\military\drone_militaryem.rvmat"
		};
		weight=1000;
		itemsCargoSize[]={10,50};
		attachments[]=
		{
			"BatteryD",
			"dronammobox",
			"Shoulder",
			"Melee",
			"Knife"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500000;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"vzp_dron_mod\drone\data\military\drone_military.rvmat",
								"vzp_dron_mod\drone\data\military\drone_militaryem.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"vzp_dron_mod\drone\data\military\drone_military.rvmat",
								"vzp_dron_mod\drone\data\military\drone_militaryem.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"vzp_dron_mod\drone\data\military\drone_military.rvmat",
								"vzp_dron_mod\drone\data\military\drone_militaryem.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"vzp_dron_mod\drone\data\military\drone_military.rvmat",
								"vzp_dron_mod\drone\data\military\drone_militaryem.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\Characters\backpacks\data\mountain_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};
class CfgSoundShaders
{
	class NoObjects_dron_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\NoObjects_dron.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class ZamBatareya_dron_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\ZamBatareya_dron.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class Reanim_dron_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\Reanim_dron.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class TargetDestroyed_voenDrone_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\TargetDestroyed_voenDrone.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class MaxFood_dron_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\MaxFood_dron.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class LoadBattary_Drone_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\LoadBattary_Drone.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
	class Magnet_Activate_SoundShader
	{
		samples[]=
		{
			
			{
				"\vzp_dron_mod\sound\MagnetActivate.ogg",
				1
			}
		};
		volume=1;
		range=45;
	};
};
class CfgSoundSets
{
	class baseDroneItem_SoundSet
	{
		sound3DProcessingType="Vehicle_Ext_3DProcessingType";
		distanceFilter="softVehiclesDistanceFreqAttenuationFilter";
		volumeCurve="vehicleEngineAttenuationCurve";
		volumeFactor=1;
		occlusionFactor=0;
		obstructionFactor=0;
		spatial=1;
		loop=0;
		positionOffset[]={0,0,0};
	};
	class NoObjects_dron_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"NoObjects_dron_SoundShader"
		};
		volumeFactor=1;
	};
	class ZamBatareya_dron_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"ZamBatareya_dron_SoundShader"
		};
		volumeFactor=1;
	};
	class Reanim_dron_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"Reanim_dron_SoundShader"
		};
		volumeFactor=1;
	};
	class TargetDestroyed_voenDrone_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"TargetDestroyed_voenDrone_SoundShader"
		};
		volumeFactor=1;
	};
	class MaxFood_dron_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"MaxFood_dron_SoundShader"
		};
		volumeFactor=1;
	};
	class LoadBattary_Drone_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"LoadBattary_Drone_SoundShader"
		};
		volumeFactor=1;
	};
	class Magnet_Activate_SoundSet: baseDroneItem_SoundSet
	{
		soundShaders[]=
		{
			"Magnet_Activate_SoundShader"
		};
		volumeFactor=1;
	};
};
