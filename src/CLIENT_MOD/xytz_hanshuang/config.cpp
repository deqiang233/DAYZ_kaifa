class CfgPatches
{
	class xytz_hanshuang
	{
		units[]={};
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
class OpticsInfoRifle;
class cfgWeapons
{
	class SVD;
	class xytz_hanshuang: SVD
	{
		scope=2;
		displayName="寒霜狙击步枪";
		descriptionShort="寒霜狙击步枪 CYX专属 使用高级狙击子弹";
		weight=1746;
		absorbency=0;
		model="xytz_hanshuang\xytz_hanshuang.p3d";
		itemSize[]={6,2};
		repairableWithKits[]={5,1};
		repairCosts[]={30,25};
		PPDOFProperties[]={1,0.60000002,50,200,4,10};
		WeaponLength=0;
		chamberSize=1;
		chamberedRound="";
		chamberableFrom[]=
		{
			"xytz_hanshuang_Ammo"
		};
		magazines[]=
		{
			"xytz_hanshuang_mag_rnd"
		};
		attachments[]=
		{
			"Lilai6_optic",
			"weaponOptics",
			"weaponMuzzleM4",
			"weaponFlashlight"
		};
		magazineSwitchTime=0.5;
		ejectType=1;
		recoilModifier[]={0.80000001,0.80000001,0.80000001};
		swayModifier[]={0.80000001,0.80000001,0.80000001};
		drySound[]=
		{
			"dz\sounds\weapons\firearms\m4a1\m4_dry",
			0.5,
			1,
			20
		};
		reloadAction="ReloadM4";
		reloadMagazineSound[]=
		{
			"dz\sounds\weapons\firearms\m4a1\m4_reload_0",
			0.80000001,
			1,
			20
		};
		modes[]=
		{
			"SemiAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"xytz_hanshuang_1",
				"xytz_hanshuang_2",
				"xytz_hanshuang_3"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"SVD_silencerHomeMade_SoundSet",
					"SVD_silencerHomeMadeTail_SoundSet",
					"SVD_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			begin1[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4_single_1",
				1,
				1,
				1000
			};
			begin2[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4_single_2",
				1,
				1,
				1000
			};
			begin3[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4_single_3",
				1,
				1,
				1000
			};
			soundBegin[]=
			{
				"begin1",
				0.33333001,
				"begin2",
				0.33333001,
				"begin3",
				0.33333001
			};
			reloadTime=0.15000001;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
			beginSilenced_Pro1[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4Silenced",
				1,
				1,
				75
			};
			beginSilenced_Pro2[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4Silenced2",
				1,
				1,
				75
			};
			beginSilenced_HomeMade[]=
			{
				"dz\sounds\weapons\firearms\m4a1\m4Silenced",
				1,
				1,
				150
			};
			soundBeginExt[]=
			{
				
				{
					"beginSilenced_Pro1",
					0.5,
					"beginSilenced_Pro2",
					0.5
				},
				
				{
					"beginSilenced_HomeMade",
					1
				}
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
				};
				class ChamberSmokeBurst
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
					overrideDirectionPoint="Nabojniceend";
				};
			};
			class OnOverheating
			{
				maxOverheatingValue=60;
				shotsToStartOverheating=25;
				overheatingDecayInterval=1;
				class SmokingBarrel1
				{
					positionOffset[]={0.2,0,0};
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0,0.2};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHot1
				{
					positionOffset[]={0.2,0,0};
					overrideParticle="smoking_barrel";
					onlyWithinOverheatLimits[]={0.2,0.60000002};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHot3
				{
					positionOffset[]={0.2,0,0};
					overrideParticle="smoking_barrel_heavy";
					onlyWithinOverheatLimits[]={0.60000002,1};
					onlyWithinRainLimits[]={0,0.2};
				};
				class SmokingBarrelHotSteam
				{
					overrideParticle="smoking_barrel_steam";
					positionOffset[]={0.34999999,0,0};
					onlyWithinOverheatLimits[]={0,1};
					onlyWithinRainLimits[]={0.2,1};
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
					overrideParticle="weapon_shot_chamber_smoke_raise";
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
					hitpoints=99999999999;
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
							0.2,
							
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
};
class CfgMagazines
{
	class Ammunition_Base;
	class Mag_CMAG_40Rnd;
	class xytz_hanshuang_mag_rnd: Mag_CMAG_40Rnd
	{
		scope=2;
		displayName="寒霜狙击弹夹";
		descriptionShort="可装寒冰子弹";
		itemSize[]={2,2};
		ammo="xytz_hanshuang_Bullet_50";
		ammoItems[]=
		{
			"xytz_hanshuang_Ammo"
		};
		model="xytz_hanshuang\mag.p3d";
		count=10;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=9999999999;
					healthLevels[]={};
				};
			};
		};
	};
	class xytz_hanshuang_Ammo: Ammunition_Base
	{
		scope=2;
		displayName="高级狙击子弹";
		descriptionShort="高级狙击子弹 BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="xytz_hanshuang_Bullet_50";
	};

	class xytz_hanshuang_Ammo_200: Ammunition_Base
	{
		scope=2;
		displayName="1级步枪子弹";
		descriptionShort="1级步枪子弹  BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="xytz_hanshuang_Bullet_200";
	};
	class xytz_hanshuang_Ammo_400: Ammunition_Base
	{
		scope=2;
		displayName="2级步枪子弹";
		descriptionShort="2级步枪子弹  BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="xytz_hanshuang_Bullet_400";
	};
	class xytz_hanshuang_Ammo_666: Ammunition_Base
	{
		scope=2;
		displayName="3级步枪子弹";
		descriptionShort="3级步枪子弹  BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="xytz_hanshuang_Bullet_666";
	};
	class xytz_hanshuang_Ammo_4000: Ammunition_Base
	{
		scope=2;
		displayName="高级栓狙子弹";
		descriptionShort="高级栓狙子弹  BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="xytz_hanshuang_Bullet_4000";
	};

	class CYX_Ammo_AK_v1_300: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹AK_V1";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_AK_v1_Bullet_300";
	};
	class CYX_Ammo_AK_v2_600: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹AK_V2";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_AK_v2_Bullet_600";
	};
	class CYX_Ammo_AK_v3_900: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹AK_V3";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_AK_v3_Bullet_900";
	};
	class CYX_Ammo_M4_v1_225: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹M4_V1";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_M4_v1_Bullet_225";
	};
	class CYX_Ammo_M4_v2_450: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹M4_V2";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_M4_v2_Bullet_450";
	};
	class CYX_Ammo_M4_v3_675: Ammunition_Base
	{
		scope=2;
		displayName="高级子弹M4_V3";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_M4_v3_Bullet_675";
	};

	class CYX_Ammo_lianju_v1_2000: Ammunition_Base
	{
		scope=2;
		displayName="高级连狙子弹v1";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_lianju_v1_Bullet_2000";
	};
	class CYX_Ammo_lianju_v2_2500: Ammunition_Base
	{
		scope=2;
		displayName="高级连狙子弹v2";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_lianju_v2_Bullet_2500";
	};
	class CYX_Ammo_lianju_v3_4000: Ammunition_Base
	{
		scope=2;
		displayName="高级连狙子弹v3";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_lianju_v3_Bullet_4000";
	};



	class CYX_Ammo_shuanju_v1_4000: Ammunition_Base
	{
		scope=2;
		displayName="高级栓狙子弹v1";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_shuanju_v1_Bullet_4000";
	};
	class CYX_Ammo_shuanju_v2_5500: Ammunition_Base
	{
		scope=2;
		displayName="高级栓狙子弹v2";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_shuanju_v2_Bullet_5500";
	};
	class CYX_Ammo_shuanju_v3_7000: Ammunition_Base
	{
		scope=2;
		displayName="高级栓狙子弹v3-7000";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_shuanju_v3_Bullet_7000";
	};
	class CYX_Ammo_shuanju_v3_15000: Ammunition_Base
	{
		scope=2;
		displayName="高级栓狙子弹v3-20000";
		descriptionShort="BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="CYX_Ammo_shuanju_v3_Bullet_15000";
	};
	class CYX_Ammo_100: Ammunition_Base
	{
		scope=2;
		displayName="高级步枪子弹";
		descriptionShort="高级步枪子弹  BY:CYX饥荒";
		model="xytz_hanshuang\ammo\Ammunition\xytz_hanshuang_Ammo.p3d";
		rotationFlags=34;
		itemSize[]={1,1};
		weight=0.041999999;
		count=100;
		ammo="Bullet_CYX_Ammo_100";
	};
};
class cfgAmmoTypes
{
	class xytz_hanshuang_Bullet_50
	{
		name="xytz_hanshuang_Bullet_50";
	};

	class xytz_hanshuang_Bullet_200
	{
		name="xytz_hanshuang_Bullet_200";
	};
	class xytz_hanshuang_Bullet_400
	{
		name="xytz_hanshuang_Bullet_400";
	};
	class xytz_hanshuang_Bullet_666
	{
		name="xytz_hanshuang_Bullet_666";
	};
	class xytz_hanshuang_Bullet_4000
	{
		name="xytz_hanshuang_Bullet_4000";
	};
	class CYX_Ammo_AK_v1_Bullet_300
	{
		name="CYX_Ammo_AK_v1_Bullet_300";
	};
	class CYX_Ammo_AK_v2_Bullet_600
	{
		name="CYX_Ammo_AK_v2_Bullet_600";
	};
	class CYX_Ammo_AK_v3_Bullet_900
	{
		name="CYX_Ammo_AK_v3_Bullet_900";
	};
	class CYX_Ammo_M4_v1_Bullet_225
	{
		name="CYX_Ammo_M4_v1_Bullet_225";
	};
	class CYX_Ammo_M4_v2_Bullet_450
	{
		name="CYX_Ammo_M4_v2_Bullet_450";
	};
	class CYX_Ammo_M4_v3_Bullet_675
	{
		name="CYX_Ammo_M4_v3_Bullet_675";
	};

	class CYX_Ammo_lianju_v1_Bullet_2000
	{
		name="CYX_Ammo_lianju_v1_Bullet_2000";
	};
	class CYX_Ammo_lianju_v2_Bullet_2500
	{
		name="CYX_Ammo_lianju_v2_Bullet_2500";
	};
	class CYX_Ammo_lianju_v3_Bullet_4000
	{
		name="CYX_Ammo_lianju_v3_Bullet_4000";
	};

	class CYX_Ammo_shuanju_v1_Bullet_4000
	{
		name="CYX_Ammo_shuanju_v1_Bullet_4000";
	};
	class CYX_Ammo_shuanju_v2_Bullet_5500
	{
		name="CYX_Ammo_shuanju_v2_Bullet_5500";
	};
	class CYX_Ammo_shuanju_v3_Bullet_7000
	{
		name="CYX_Ammo_shuanju_v3_Bullet_7000";
	};
	class CYX_Ammo_shuanju_v3_Bullet_15000
	{
		name="CYX_Ammo_shuanju_v3_Bullet_15000";
	};
	class Bullet_CYX_Ammo_100
	{
		name="Bullet_CYX_Ammo_100";
	};
};
class cfgAmmo
{
	class Bullet_308Win;
	class xytz_hanshuang_Bullet_50: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=2500;
			};
			class Blood
			{
				damage=2500;
			};
			class Shock
			{
				damage=2500;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};

	class xytz_hanshuang_Bullet_4000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=4000;
			};
			class Blood
			{
				damage=4000;
			};
			class Shock
			{
				damage=4000;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class xytz_hanshuang_Bullet_200: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=1.5;
		deflecting=30;
		airFriction=-0.00039900001;
		typicalSpeed=1500;
		initSpeed=1100;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=200;
			};
			class Blood
			{
				damage=200;
			};
			class Shock
			{
				damage=200;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class xytz_hanshuang_Bullet_400: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=1.5;
		deflecting=30;
		airFriction=-0.00039900001;
		typicalSpeed=1500;
		initSpeed=1100;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=400;
			};
			class Blood
			{
				damage=400;
			};
			class Shock
			{
				damage=400;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class xytz_hanshuang_Bullet_666: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=1.5;
		deflecting=30;
		airFriction=-0.00039900001;
		typicalSpeed=1500;
		initSpeed=1100;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=666;
			};
			class Blood
			{
				damage=666;
			};
			class Shock
			{
				damage=666;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};

	
	class CYX_Ammo_AK_v1_Bullet_300: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=300;
			};
			class Blood
			{
				damage=300;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_AK_v2_Bullet_600: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=600;
			};
			class Blood
			{
				damage=600;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_AK_v3_Bullet_900: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=900;
			};
			class Blood
			{
				damage=900;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_M4_v1_Bullet_225: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=300;
			};
			class Blood
			{
				damage=300;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_M4_v2_Bullet_450: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=600;
			};
			class Blood
			{
				damage=600;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_M4_v3_Bullet_675: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.0000000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=900;
			};
			class Blood
			{
				damage=900;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_lianju_v1_Bullet_2000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=2000;
			};
			class Blood
			{
				damage=2000;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_lianju_v2_Bullet_2500: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=2500;
			};
			class Blood
			{
				damage=2500;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_lianju_v3_Bullet_4000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.0000000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=4000;
			};
			class Blood
			{
				damage=4000;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_shuanju_v1_Bullet_4000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=4000;
			};
			class Blood
			{
				damage=4000;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_shuanju_v2_Bullet_5500: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.00080000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=5500;
			};
			class Blood
			{
				damage=5500;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_shuanju_v3_Bullet_7000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.0000000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=7000;
			};
			class Blood
			{
				damage=7000;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class CYX_Ammo_shuanju_v3_Bullet_15000: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="xytz_hanshuang_Ammo";
		hit=9;
		indirectHit=0;
		indirectHitRange=0;
		caliber=5;
		deflecting=30;
		airFriction=-0.00000008;
		typicalSpeed=3000;
		initSpeed=2900;
		weight=0.0000000004;
		tracerScale=1.2;
		tracerStartTime=0.075000003;
		tracerEndTime=11;
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=20000;
			};
			class Blood
			{
				damage=20000;
			};
			class Shock
			{
				damage=100;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
	class Bullet_CYX_Ammo_100: Bullet_308Win
	{
		scope=2;
		lootCategory="Crafted";
		model="xytz_hanshuang\ammo\Projectiles\xytz_hanshuang_Bullet_50.p3d";
		cartridge="FxCartridge_762";
		round="FxRound_762";
		spawnPileType="CYX_Ammo_100";
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.89999998,1}
			};
			class Health
			{
				damage=100;
			};
			class Blood
			{
				damage=100;
			};
			class Shock
			{
				damage=10;
			};
		};
		class NoiseHit
		{
			strength=10;
			type="shot";
		};
	};
};
class cfgVehicles
{
	class HuntingOptic;
	class xytz_hanshuang_MiaoJu: HuntingOptic
	{
		scope=2;
		displayName="寒霜狙击步枪专属8倍镜";
		descriptionShort="";
		model="xytz_hanshuang\xytz_hanshuang_optic.p3d";
		debug_ItemCategory=3;
		animClass="Binoculars";
		rotationFlags=4;
		reversed=0;
		weight=700;
		itemSize[]={4,1};
		inventorySlot[]=
		{
			"Lilai6_optic"
		};
		simulation="itemoptics";
		dispersionModifier=-0.001;
		dispersionCondition="true";
		recoilModifier[]={0,0,0};
		swayModifier[]={0,0,0};
		memoryPointCamera="eyeScope_temp";
		cameraDir="cameraDir";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=99999999;
					healthLevels[]={};
				};
			};
		};
		class OpticsInfo
		{
			memoryPointCamera="eyeScope";
			cameraDir="cameraDir";
			useModelOptics=1;
			modelOptics="\DZ\weapons\attachments\optics\opticview_longrange.p3d";
			preloadOpticType="Preload2DOptic_Longrange";
			opticsDisablePeripherialVision=0.67000002;
			opticsFlare=1;
			opticsPPEffects[]=
			{
				"OpticsCHAbera3",
				"OpticsBlur1"
			};
			opticsZoomMin="0.3926/4";
			opticsZoomMax="0.3926/12";
			opticsZoomInit="0.3926/4";
			discretefov[]=
			{
				"0.3926/4",
				"0.3926/8",
				"0.3926/12"
			};
			discreteInitIndex=0;
			distanceZoomMin=100;
			distanceZoomMax=1000;
			discreteDistance[]={200,300,400,500,600,700,800};
			discreteDistanceInitIndex=0;
			PPMaskProperties[]={0.5,0.5,0.43000001,0.1};
			PPLensProperties[]={0.30000001,0.15000001,0,0};
			PPBlurProperties=0.30000001;
		};
		class AnimationSources
		{
			class hide
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class rings_ris
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class rings_ris_pilot
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class rings_winchester
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class rings_winchester_pilot
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
		};
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class xytz_hanshuang_Sound_1
	{
		samples[]=
		{
			
			{
				"xytz_hanshuang\sounds\abc",
				1
			}
		};
		volume=1.3;
		range=200;
		rangeCurve="closeShotCurve";
	};
	class xytz_hanshuang_Sound_2
	{
		samples[]=
		{
			
			{
				"xytz_hanshuang\sounds\abc",
				1
			}
		};
		volume=0.56234133;
		range=200;
		rangeCurve[]=
		{
			{0,0.2},
			{200,1},
			{700,0},
			{2000,0}
		};
	};
	class xytz_hanshuang_Sound_3
	{
		samples[]=
		{
			
			{
				"xytz_hanshuang\sounds\abc",
				1
			}
		};
		volume=1;
		range=200;
		rangeCurve[]=
		{
			{0,0},
			{200,0},
			{700,1},
			{2000,1}
		};
	};
};
class CfgSoundSets
{
	class Rifle_Shot_Base_SoundSet;
	class xytz_hanshuang_1: Rifle_Shot_Base_SoundSet
	{
		soundShaders[]=
		{
			"xytz_hanshuang_Sound_1",
			"xytz_hanshuang_Sound_2",
			"xytz_hanshuang_Sound_3"
		};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class Proxyxytz_hanshuang_optic: ProxyAttachment
	{
		scope=0;
		inventorySlot="Lilai6_optic";
		model="xytz_hanshuang\xytz_hanshuang_optic.p3d";
	};
};
class CfgSlots
{
	class Slot_Lilai6_optic
	{
		name="Lilai6_optic";
		displayName="寒霜专属瞄具";
		ghostIcon="optics";
	};
};
