class CfgPatches
{
	class MrAK47
	{
		units[]=
		{
			"Mr_AK47_1",
			"Mr_AK47_2"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Firearms"
		};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class AKM_Base;
	class Mr_AK47_Base: AKM_Base
	{
		scope=0;
		weight=2140;
		absorbency=0;
		repairableWithKits[]={1};
		repairCosts[]={25};
		PPDOFProperties[]={1,0.5,50,160,4,10};
		ironsightsExcludingOptics[]=
		{
			"KashtanOptic",
			"GrozaOptic",
			"KobraOptic"
		};
		WeaponLength=0.89999998;
		barrelArmor=4.4439998;
		initSpeedMultiplier=0.89999998;
		chamberSize=1;
		chamberedRound="";
		attachments[]=
		{
			"weaponWrap",
			"weaponOpticsAK",
			"weaponFlashlight",
			"weaponMuzzleAK",
			"weaponButtstockAK",
			"weaponBayonetAK"
		};
		magazineSwitchTime=0.2;
		ejectType=1;
		recoilModifier[]={0.30000001,0.30000001,0.30000001};
		swayModifier[]={0.30000001,0.30000001,0.30000001};
		simpleHiddenSelections[]=
		{
			"hide_barrel"
		};
		hiddenSelections[]=
		{
			"camo"
		};
		modes[]=
		{
			"SemiAuto",
			"FullAuto"
		};
		class NoiseShoot
		{
			strength=82;
			type="shot";
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"AK_Shot_SoundSet",
				"AK_Tail_SoundSet",
				"AK_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"AK_silencer_SoundSet",
					"AK_silencerTail_SoundSet",
					"AK_silencerInteriorTail_SoundSet"
				},
				
				{
					"AK_silencerHomeMade_SoundSet",
					"AK_silencerHomeMadeTail_SoundSet",
					"AK_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.12;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"AK_Shot_SoundSet",
				"AK_Tail_SoundSet",
				"AK_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"AK_silencer_SoundSet",
					"AK_silencerTail_SoundSet",
					"AK_silencerInteriorTail_SoundSet"
				},
				
				{
					"AK_silencerHomeMade_SoundSet",
					"AK_silencerHomeMadeTail_SoundSet",
					"AK_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.097999997;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class OpticsInfo: OpticsInfoRifle
		{
			memoryPointCamera="eye";
			discreteDistance[]={100,200,300,400,500,600,700,800,900,1000};
			discreteDistanceInitIndex=0;
			modelOptics="-";
			distanceZoomMin=100;
			distanceZoomMax=1000;
		};
		class Particles
		{
			class OnFire
			{
				class SmokeCloud
				{
					overrideParticle="weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_akm_01";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
					positionOffset[]={-0.050000001,0,0};
				};
				class ChamberSmoke
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
					overrideDirectionPoint="Nabojniceend";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
				};
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=9999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AKM\data\AKM.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AKM\data\AKM.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AKM\data\AKM_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AKM\data\AKM_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AKM\data\AKM_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK47: Mr_AK47_Base
	{
		scope=0;
		model="LY_Weapon\AK47\AK47.p3d";
		itemSize[]={8,3};
	};
	class Mr_AK47_1: Mr_AK47
	{
		scope=2;
		displayName="AK-47|霓虹骑士";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_471.paa"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47Mag999",
			"Mr_AK47HigMag999"
		};
	};
	class Mr_AK47_2: Mr_AK47
	{
		scope=2;
		displayName="AK-47|量子力场";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_472.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_47eo.rvmat"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47MagShotgun",
			"Mr_AK47MagBlack999",
			"Mr_AK47HigMag_Black999"
		};
	};
	class Mr_AK47_3: Mr_AK47
	{
		scope=2;
		displayName="AK-47|迷幻动漫";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_473.paa"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47MagPink999",
			"Mr_AK47HigMag_Pink999"
		};
	};
	class Mr_AK47_4: Mr_AK47
	{
		scope=2;
		displayName="AK-47|野荷";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_474.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_474_eo.rvmat"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47HigMag_YH999",
			"Mr_AK47MagYH999"
		};
	};
	class Mr_AK47_5: Mr_AK47
	{
		scope=2;
		displayName="AK-47|碧落";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_475.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_475_eo.rvmat"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47HigMag_BL999",
			"Mr_AK47MagBL999"
		};
	};
	class Mr_AK47_6: Mr_AK47
	{
		scope=2;
		displayName="AK-47|梅花";
		descriptionShort="稀有度：隐秘级，掉落率较低，在玩家中非常受欢迎，是 AK-47 的热门皮肤之一。因其独特而生动的设计、稀有性以及与重大行动的关联，在 CS:GO 社区中获得了很高的评价，通常在 AK-47 皮肤中名列前茅";
		itemSize[]={8,3};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_476.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_476_eo.rvmat"
		};
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mr_AK47HigMag_MH999",
			"Mr_AK47MagMH999"
		};
	};
};
class CfgMagazines
{
	class Mag_AKM_30Rnd;
	class Mr_AK47Mag_Low: Mag_AKM_30Rnd
	{
		scope=0;
		model="LY_Weapon\AK47\Mag\AK47_Mag.p3d";
		weight=230;
		itemSize[]={1,3};
		weightPerQuantityUnit=3;
		count=999;
		ammo="Bullet_762x39Tracer";
		ammoItems[]=
		{   "Ammo_762x39Low",
			"Ammo_762x39Tracer",
			"Ammo_762x39"
		};
		tracersEvery=0;
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"LY_Weapon\AK47\data\Ak_47.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"LY_Weapon\AK47\data\Ak_47.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"LY_Weapon\AK47\data\Ak_47_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"LY_Weapon\AK47\data\Ak_47_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"LY_Weapon\AK47\data\Ak_47_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK47Mag999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|霓虹骑士-配套弹匣_Low";
		descriptionShort="AK-47|霓虹骑士_999发_弹匣_Low";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47.paa"
		};
	};
	class Mr_AK47MagBlack999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|量子力场-配套弹匣_Low";
		descriptionShort="AK-47|量子力场_999发_弹匣_Low";
		count=999;
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47_2.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_47eo.rvmat"
		};
	};
	
	class Mr_AK47MagPink999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|迷幻动漫-配套弹匣_Low";
		descriptionShort="AK-47|迷幻动漫_999发_弹匣_Low";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_473.paa"
		};
	};
	class Mr_AK47MagYH999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|野荷-配套弹匣_Low";
		descriptionShort="AK-47|野荷_999发_弹匣_Low";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_474.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_474_eo.rvmat"
		};
	};
	class Mr_AK47MagBL999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|碧落-配套弹匣_Low";
		descriptionShort="AK-47|碧落_999发_弹匣_Low";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_475.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_475_eo.rvmat"
		};
	};
	class Mr_AK47MagMH999: Mr_AK47Mag_Low
	{
		scope=2;
		displayName="AK-47|梅花-配套弹匣_Low";
		descriptionShort="AK-47|梅花_999发_弹匣_Low";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_476.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_476_eo.rvmat"
		};
	};
	class Mr_AK47Mag_Hig: Mag_AKM_30Rnd
	{
		scope=0;
		model="LY_Weapon\AK47\Mag\AK47_Mag.p3d";
		weight=230;
		itemSize[]={1,3};
		weightPerQuantityUnit=3;
		count=999;
		ammo="Bullet_762x39Hig";
		ammoItems[]=
		{
			"Ammo_762x39Low",
			"Ammo_762x39Hig"
		};
		tracersEvery=0;
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"LY_Weapon\AK47\data\Ak_47.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"LY_Weapon\AK47\data\Ak_47.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"LY_Weapon\AK47\data\Ak_47_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"LY_Weapon\AK47\data\Ak_47_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"LY_Weapon\AK47\data\Ak_47_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK47HigMag999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|霓虹骑士-配套弹匣_Hig";
		descriptionShort="AK-47|霓虹骑士_999发_弹匣_Hig";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47.paa"
		};
	};
	class Mr_AK47HigMag_Black999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|量子力场-配套弹匣_Hig";
		descriptionShort="AK-47|量子力场_999发_弹匣_Hig";
		count=999;
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_47_2.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_47eo.rvmat"
		};
	};
	class Mr_AK47HigMag_Pink999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|迷幻动漫-配套弹匣_Hig";
		descriptionShort="AK-47|迷幻动漫_999发_弹匣_Hig";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_473.paa"
		};
	};
	class Mr_AK47HigMag_YH999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|野荷-配套弹匣_Hig";
		descriptionShort="AK-47|野荷_999发_弹匣_Hig";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_474.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_474_eo.rvmat"
		};
	};
	class Mr_AK47HigMag_BL999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|碧落-配套弹匣_Hig";
		descriptionShort="AK-47|碧落_999发_弹匣_Hig";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_475.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_475_eo.rvmat"
		};
	};
	class Mr_AK47HigMag_MH999: Mr_AK47Mag_Hig
	{
		scope=2;
		displayName="AK-47|梅花-配套弹匣_Hig";
		descriptionShort="AK-47|梅花_999发_弹匣_Hig";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Ak_476.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Ak_476_eo.rvmat"
		};
	};
};
class cfgVehicles
{
	class Inventory_Base;
	class AK_PlasticBttstck;
	class AK_Suppressor;
	class UniversalLight;
	class AK_Bayonet;
	class Mr_UniversalLight: UniversalLight
	{
		scope=2;
		displayName="AK-47|量子力场-配套手电";
		descriptionShort="AK-47|量子力场_手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\flashlight_co.paa",
			"LY_Weapon\AK47\data\flashlight_co.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\flashlight_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_UniversalLight2: UniversalLight
	{
		scope=2;
		displayName="尘埃落定M4专用-配套手电";
		descriptionShort="尘埃落定M4专用手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\m4_flashlight_2.paa",
			"LY_Weapon\AK47\data\m4_flashlight_2.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\m4_flashlight_2.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\flashlight.rvmat",
			"LY_Weapon\AK47\data\flashlight.rvmat",
			"dz\gear\tools\data\flashlight_glass.rvmat",
			"LY_Weapon\AK47\data\flashlight.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_UniversalLight3: UniversalLight
	{
		scope=2;
		displayName="AK-47|迷幻动漫-配套手电";
		descriptionShort="AK-47|迷幻动漫_手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\m4_flashlight_3.paa",
			"LY_Weapon\AK47\data\m4_flashlight_3.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\m4_flashlight_3.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\flashlight.rvmat",
			"LY_Weapon\AK47\data\flashlight.rvmat",
			"dz\gear\tools\data\flashlight_glass.rvmat",
			"LY_Weapon\AK47\data\flashlight.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_UniversalLightM249: UniversalLight
	{
		scope=2;
		displayName="突突M249专用-配套手电";
		descriptionShort="突突M249专用手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\m4_flashlightm249.paa",
			"LY_Weapon\AK47\data\m4_flashlightm249.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\m4_flashlightm249.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_UniversalLight5: UniversalLight
	{
		scope=2;
		displayName="龙的传人M4A4专用-配套手电";
		descriptionShort="龙的传人M4A4专用手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\m4_flashlight_5.paa",
			"LY_Weapon\AK47\data\m4_flashlight_5.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\m4_flashlight_5.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_UniversalLight6: UniversalLight
	{
		scope=2;
		displayName="AK-47|碧落-配套手电";
		descriptionShort="AK-47|碧落_手电";
		inventorySlot[]=
		{
			"weaponFlashlight",
			"helmetFlashlight"
		};
		hiddenSelections[]=
		{
			"zbytek",
			"reflector",
			"glass",
			"reflector_far"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\m4_flashlight_6.paa",
			"LY_Weapon\AK47\data\m4_flashlight_6.paa",
			"dz\gear\tools\data\flashlight_glass.paa",
			"LY_Weapon\AK47\data\m4_flashlight_6.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight.rvmat",
								"dz\gear\tools\data\flashlight_glass.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_damage.rvmat",
								"dz\gear\tools\data\flashlight_glass_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_flashlight_destruct.rvmat",
								"dz\gear\tools\data\flashlight_glass_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Bayonet_YH: AK_Bayonet
	{
		scope=2;
		displayName="AK-47|野荷-配套枪刺";
		descriptionShort="AK-47|野荷-配套配套枪刺.";
		inventorySlot[]=
		{
			"weaponBayonetAK",
			"Knife"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\akm_bayonet_YH.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\Russian_AKM_Bayonet.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\Russian_AKM_Bayonet.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\Russian_AKM_Bayonet_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\Russian_AKM_Bayonet_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\Russian_AKM_Bayonet_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_1: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|霓虹骑士-配套消音器";
		descriptionShort="AK-47|霓虹骑士-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co1.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_2: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|量子力场-配套消音器";
		descriptionShort="AK-47|量子力场-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co2.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_3: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|迷幻动漫-配套消音器";
		descriptionShort="AK-47|迷幻动漫-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co3.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_4: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|野荷-配套消音器";
		descriptionShort="AK-47|野荷-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co4.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_5: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|碧落-配套消音器";
		descriptionShort="AK-47|碧落-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co5.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_6: AK_Suppressor
	{
		scope=2;
		displayName="AK-47|梅花-配套消音器";
		descriptionShort="AK-47|梅花-配套消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_co6.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_Suppressor_TM: AK_Suppressor
	{
		scope=2;
		displayName="AK专用-透明消音器";
		descriptionShort="AK专用-透明消音器.";
		inventorySlot[]=
		{
			"weaponMuzzleAK"
		};
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\tgpa_coTM.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck1: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|霓虹骑士-配套枪托";
		descriptionShort="AK-47|霓虹骑士-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck1.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck2: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|量子力场-配套枪托";
		descriptionShort="AK-47|量子力场-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck2.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Bttstck2.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck3: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|迷幻动漫-配套枪托";
		descriptionShort="AK-47|迷幻动漫-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck3.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck4: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|野荷-配套枪托";
		descriptionShort="AK-47|野荷-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck4.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Bttstck4.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck5: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|碧落-配套枪托";
		descriptionShort="AK-47|碧落-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck5.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Bttstck5.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class Mr_AK_PlasticBttstck6: AK_PlasticBttstck
	{
		scope=2;
		displayName="AK-47|梅花-配套枪托";
		descriptionShort="AK-47|梅花-配套枪托.";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"LY_Weapon\AK47\data\Bttstck6.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"LY_Weapon\AK47\data\Bttstck6.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\AK101\data\ak101_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyAK47_Mag: ProxyAttachment
	{
		scope=2;
		inventorySlot="magazine";
		model="LY_Weapon\Mag\AK47_Mag.p3d";
	};
};
