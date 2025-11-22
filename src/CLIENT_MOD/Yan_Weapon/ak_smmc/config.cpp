class CfgPatches
{
	class YANAK
	{
		units[]=
		{
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
// Yan_Weapon\ak_smmc\ak_smmc_v1.p3d
// Yan_Weapon\ak_smmc\ak_smmc_v3.p3d


// Yan_Weapon\ak_smmc\ak_smmc_magz_v1.p3d
// Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d

class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class AKM_Base;
	class YAN_AK_smmc: AKM_Base
	{
		scope=0;
		weight=2140;
		absorbency=0;
		repairableWithKits[]={1};
		repairCosts[]={25};
		PPDOFProperties[]={1,0.5,50,160,4,10};
		itemSize[]={8,3};
		ironsightsExcludingOptics[]={};
		WeaponLength=0.89999998;
		barrelArmor=4.4439998;
		initSpeedMultiplier=0.89999998;
		chamberSize=1;
		chamberedRound="";
		attachments[]=
		{
			"weaponOptics",
			"weaponMuzzleM4"
		};
		magazineSwitchTime=0.2;
		ejectType=1;
		chamberableFrom[]=
		{
			"CYX_Ammo_100"
		};
		magazines[]=
		{
			"yan_cyx_ak_smmc_magz_v1",
			"yan_cyx_ak_smmc_magz_v2",
			"yan_cyx_ak_smmc_magz_v3",
			"yan_cyx_ak_smmc_magz_v4",
			"yan_cyx_ak_smmc_magz_v5",
			"yan_cyx_ak_smmc_magz_v6",
			"yan_cyx_ak_smmc_magz_v7",
			"yan_cyx_ak_smmc_magz_v8",
			"yan_cyx_ak_smmc_magz_v9",
			"yan_cyx_ak_smmc_magz_v10"
		};
		recoilModifier[]={0.69999999,0.69999999,0.69999999};
		swayModifier[]={0.69999999,0.69999999,0.69999999};
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
			reloadTime=0.1;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=1e-10;
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
			reloadTime=0.1;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=1e-10;
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
	class yan_cxy_ak_smmc_v1: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v1";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v1.p3d";
	};
	class yan_cxy_ak_smmc_v2: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v2";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v1.p3d";

	};
	class yan_cxy_ak_smmc_v3: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v3";
		descriptionShort="暴力美学与可爱文化的极致碰撞。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v1.p3d";

	};
	class yan_cxy_ak_smmc_v4: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v4";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};;
	class yan_cxy_ak_smmc_v5: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v5";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
	class yan_cxy_ak_smmc_v6: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v6";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
	class yan_cxy_ak_smmc_v7: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v7";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
	class yan_cxy_ak_smmc_v8: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v8";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
	class yan_cxy_ak_smmc_v9: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v9";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
	class yan_cxy_ak_smmc_v10: YAN_AK_smmc
	{
		scope=2;
		displayName="AK | 数码脉冲v10";
		descriptionShort="当经典暴力美学遇上数字洪流。”这款皮肤将AK-47的粗犷与坚韧，完美融入了霓虹闪烁的赛博朋克未来。它不仅仅是涂装，更像是这把传奇步枪被数据化后的形态，冰冷的金属下仿佛有数字生命在流动。by_cyx_yan";
		model="Yan_Weapon\ak_smmc\ak_smmc_v3.p3d";
	};
};
class CfgMagazines
{
	class Mag_AKM_30Rnd;
	class YAN_AK_smmc_mags: Mag_AKM_30Rnd
	{
		scope=0;
		weight=230;
		itemSize[]={1,3};
		tracersEvery=0;
		ammo="Bullet_CYX_Ammo_100";
		ammoItems[]=
		{
			"CYX_Ammo_100"
		};
		hiddenSelections[]=
		{
			"camo"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999;
				};
			};
		};
	};
	class yan_cyx_ak_smmc_magz_v1: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v1";
		descriptionShort="数码脉冲弹夹v1";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v1.p3d";		
		count=100;

	};
	class yan_cyx_ak_smmc_magz_v2: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v2";
		descriptionShort="数码脉冲弹夹v2";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v1.p3d";
		count=200;

	};
	class yan_cyx_ak_smmc_magz_v3: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v3";
		descriptionShort="数码脉冲弹夹v3";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v1.p3d";
		count=300;
	};
	class yan_cyx_ak_smmc_magz_v4: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v4";
		descriptionShort="数码脉冲弹夹v4";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=400;
	};
	class yan_cyx_ak_smmc_magz_v5: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v5";
		descriptionShort="数码脉冲弹夹v5";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=500;
	};
	class yan_cyx_ak_smmc_magz_v6: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v6";
		descriptionShort="数码脉冲弹夹v6";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=600;
	};
	class yan_cyx_ak_smmc_magz_v7: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v7";
		descriptionShort="数码脉冲弹夹v7";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=700;
	};
	class yan_cyx_ak_smmc_magz_v8: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v8";
		descriptionShort="数码脉冲弹夹v8";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=800;
	};
	class yan_cyx_ak_smmc_magz_v9: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v9";
		descriptionShort="数码脉冲弹夹v9";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=900;
	};
	class yan_cyx_ak_smmc_magz_v10: YAN_AK_smmc_mags
	{
		scope=2;
		displayName="数码脉冲弹夹v10";
		descriptionShort="数码脉冲弹夹v10";
		model="Yan_Weapon\ak_smmc\ak_smmc_magz_v3.p3d";
		count=1000;
	};
};