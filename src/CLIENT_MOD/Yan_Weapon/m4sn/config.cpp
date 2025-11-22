class CfgPatches
{
	class m4sn
	{
		units[]=
		{
			"m4sn",
			"m4sn_magz"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Launchers"
		};
	};
};
class Mode_Single;
class Mode_SemiAuto;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class Rifle_Base;
	class M4A1_Base;
	class yan_m4sn: M4A1_Base
	{
		scope=0;
		attachments[]=
		{
			"weaponOptics",
			"weaponMuzzleM4"
		};
		itemSize[]={8,3};
		modes[]=
		{
			"SemiAuto",
			"FullAuto"
		};
		chamberableFrom[]=
		{
			"CYX_Ammo_100"
		};
		magazines[]=
		{
			"yan_cyx_m4sn_magz_v1",
			"yan_cyx_m4sn_magz_v2",
			"yan_cyx_m4sn_magz_v3",
			"yan_cyx_m4sn_magz_v4",
			"yan_cyx_m4sn_magz_v5",
			"yan_cyx_m4sn_magz_v6",
			"yan_cyx_m4sn_magz_v7",
			"yan_cyx_m4sn_magz_v8",
			"yan_cyx_m4sn_magz_v9",
			"yan_cyx_m4sn_magz_v10"
		};
		recoilModifier[]={0.69999999,0.69999999,0.69999999};
		swayModifier[]={0.69999999,0.69999999,0.69999999};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"M4_Shot_SoundSet",
				"M4_Tail_SoundSet",
				"M4_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"M4_silencerHomeMade_SoundSet",
					"M4_silencerHomeMadeTail_SoundSet",
					"M4_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.1;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"M4_Shot_SoundSet",
				"M4_Tail_SoundSet",
				"M4_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"M4_silencerHomeMade_SoundSet",
					"M4_silencerHomeMadeTail_SoundSet",
					"M4_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.1;
			recoil="recoil_AKM";
			recoilProne="recoil_AKM_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		spawnDamageRange[]={0,0.60000002};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\M4\Data\m4_body.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\M4\Data\m4_body.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\M4\Data\m4_body_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\M4\Data\m4_body_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\M4\Data\m4_body_destruct.rvmat"
							}
						}
					};
				};
			};
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
					overrideParticle="weapon_shot_ump45_01";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
					positionOffset[]={0,0,0};
				};
				class MuzzleFlashStar
				{
					overrideParticle="weapon_shot_Flame_3D_4star";
					ignoreIfSuppressed=1;
					overrideDirectionVector[]={0,45,0};
					positionOffset[]={0.0099999998,0,0};
				};
				class ChamberSmoke
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
					overrideDirectionPoint="Nabojniceend";
				};
			};
			class OnOverheating
			{
				maxOverheatingValue=12;
				shotsToStartOverheating=4;
				overheatingDecayInterval=0.69999999;
				class SmokingBarrel1
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0,0.5};
					positionOffset[]={0.2,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrel2
				{
					overrideParticle="smoking_barrel";
					onlyWithinOverheatLimits[]={0.5,0.69999999};
					positionOffset[]={0.2,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrel3
				{
					overrideParticle="smoking_barrel_heavy";
					onlyWithinOverheatLimits[]={0.69999999,1};
					positionOffset[]={0.2,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHotSteamSmall
				{
					overrideParticle="smoking_barrel_steam_small";
					positionOffset[]={0.34999999,0,0};
					onlyWithinRainLimits[]={0.2,0.5};
				};
				class SmokingBarrelHotSteam
				{
					overrideParticle="smoking_barrel_steam";
					positionOffset[]={0.34999999,0,0};
					onlyWithinRainLimits[]={0.5,1};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
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
	};
	class yan_cyx_m4sn_v1: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v1";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v1.p3d";
	};
	class yan_cyx_m4sn_v2: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v2";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v1.p3d";
	};
	class yan_cyx_m4sn_v3: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v3";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v1.p3d";
	};
	class yan_cyx_m4sn_v4: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v4";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v5: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v5";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v6: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v6";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v7: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v7";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v8: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v8";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v9: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v9";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};
	class yan_cyx_m4sn_v10: yan_m4sn
	{
		scope=2;
		displayName="M4 | 霜凝v10";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		model="Yan_Weapon\m4sn\m4sn_v3.p3d";
	};

};
class CfgMagazines
{
	class Mag_STANAG_30Rnd;
	class yan_cyx_m4sn_magz: Mag_STANAG_30Rnd
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
	class yan_cyx_m4sn_magz_v1: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v1";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v1.p3d";
		count=100;
	};
	class yan_cyx_m4sn_magz_v2: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v2";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v1.p3d";
		count=200;
	};
	class yan_cyx_m4sn_magz_v3: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v3";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v1.p3d";
		count=300;
	};
	class yan_cyx_m4sn_magz_v4: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v4";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=400;
	};
	class yan_cyx_m4sn_magz_v5: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v5";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=500;
	};
	class yan_cyx_m4sn_magz_v6: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v6";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=600;
	};
	class yan_cyx_m4sn_magz_v7: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v7";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=700;
	};
	class yan_cyx_m4sn_magz_v8: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v8";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=800;
	};
	class yan_cyx_m4sn_magz_v9: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v9";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=900;
	};
	class yan_cyx_m4sn_magz_v10: yan_cyx_m4sn_magz
	{
		scope=2;
		displayName="霜凝弹夹v10";
		descriptionShort="霜凝配套弹夹";
		model="Yan_Weapon\m4sn\m4sn_magz_v3.p3d";
		count=1000;
	};

};
