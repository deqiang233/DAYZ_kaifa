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
	class yan_m4: M4A1_Base
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
	class yan_cyx_m4sn_v1: yan_m4
	{
		scope=2;
		displayName="M4 | 霜凝v1";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		chamberableFrom[]=
		{
			"CYX_Ammo_M4_v1_225",
			"Ammo_556x45",
			"Ammo_556x45Tracer"
		};
		model="m4sn\m4sn_v1.p3d";
		magazines[]=
		{
			"yan_cyx_m4sn_magz_v1"
		};
		recoilModifier[]={0.69999999,0.69999999,0.69999999};
		swayModifier[]={0.69999999,0.69999999,0.69999999};
	};
	class yan_cyx_m4sn_v2: yan_m4
	{
		scope=2;
		displayName="M4 | 霜凝v2";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		chamberableFrom[]=
		{
			"CYX_Ammo_M4_v2_450",
			"Ammo_556x45",
			"Ammo_556x45Tracer"
		};
		model="m4sn\m4sn.p3d";
		magazines[]=
		{
			"yan_cyx_m4sn_magz_v2"
		};
		recoilModifier[]={0.30000001,0.30000001,0.30000001};
		swayModifier[]={0.30000001,0.30000001,0.30000001};
	};
	class yan_cyx_m4sn_v3: yan_m4
	{
		scope=2;
		displayName="M4 | 霜凝v3";
		descriptionShort="“霜凝”并非追求张扬的华丽，而是将极致的寒冷与寂静凝聚于武器之中。它象征着绝对零度的冷静与精准，每一次击杀都干净利落，如同寒冬般无情。持有它，仿佛握住了北极之心，让对手在感受到刺骨寒意之前就已凝固。by_cyx_yan";
		chamberableFrom[]=
		{
			"CYX_Ammo_M4_v3_675",
			"Ammo_556x45",
			"Ammo_556x45Tracer"
		};
		model="m4sn\m4sn_v3.p3d";
		magazines[]=
		{
			"yan_cyx_m4sn_magz_v3",
			"yan_cyx_m4sn_magz_v3plus"
		};
		recoilModifier[]={0.10000001,0.10000001,0.10000001};
		swayModifier[]={0.10000001,0.10000001,0.10000001};
	};
};
class CfgMagazines
{
	class Mag_STANAG_30Rnd;
	class yan_cyx_magz: Mag_STANAG_30Rnd
	{
		scope=0;
		weight=450;
		itemSize[]={1,3};
		ammo="Bullet_556x45";
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
	class yan_cyx_m4sn_magz_v1: yan_cyx_magz
	{
		scope=2;
		displayName="霜凝配套弹夹v1";
		descriptionShort="霜凝配套弹夹";
		model="m4sn\m4sn_magz_v1.p3d";
		count=300;
		ammoItems[]=
		{
			"CYX_Ammo_M4_v1_225",
			"Ammo_556x45Tracer",
			"Ammo_556x45"
		};
	};
	class yan_cyx_m4sn_magz_v2: yan_cyx_magz
	{
		scope=2;
		displayName="霜凝配套弹夹v2";
		descriptionShort="霜凝配套弹夹";
		model="m4sn\m4sn_magz.p3d";
		count=400;
		ammoItems[]=
		{
			"CYX_Ammo_M4_v2_450",
			"Ammo_556x45Tracer",
			"Ammo_556x45"
		};
	};
	class yan_cyx_m4sn_magz_v3: yan_cyx_magz
	{
		scope=2;
		displayName="霜凝配套弹夹v3";
		descriptionShort="霜凝配套弹夹";
		model="m4sn\m4sn_magz_v3.p3d";
		count=500;
		ammoItems[]=
		{
			"CYX_Ammo_M4_v3_675",
			"Ammo_556x45Tracer",
			"Ammo_556x45"
		};
	};
	class yan_cyx_m4sn_magz_v3plus: yan_cyx_magz
	{
		scope=2;
		displayName="霜凝配套弹夹v3plus";
		descriptionShort="霜凝配套弹夹";
		model="m4sn\m4sn_magz_v3plus.p3d";
		count=999;
		ammoItems[]=
		{
			"CYX_Ammo_M4_v3_675",
			"Ammo_556x45Tracer",
			"Ammo_556x45"
		};
	};
};
