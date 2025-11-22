class CfgPatches
{
	class CoCo_m4_cfg
	{
		units[]=
		{
			"CoCo_m4_v1",
			"CoCo_m4_v2",
			"CoCo_m4_v3"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Firearms_M4",
			"DZ_Weapons_Magazines",
		};
		ammo[]=
		{
			"Bullet_CoCo_m4"
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
	class M4A1_Base;
	class CoCo_m4: M4A1_Base
	{
		scope=2;
		displayName="CoCo M4";
		descriptionShort="CoCo M4_by CoCo";
		model="\dz\weapons\firearms\m4\m4a1.p3d";
        hiddenSelectionsTextures[]=
		{
			"dz\weapons\firearms\m4\data\m4_body_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\m4\data\m4_body.rvmat"
		};
		itemSize[]={8,3};
		attachments[]=
		{
			"weaponButtstockM4",
			"WeaponHandguardM4",
			"weaponWrap",
			"weaponOptics",
			"weaponFlashlight",
			"weaponMuzzleM4",
			"weaponBayonet"
		};
		chamberableFrom[]=
		{
			"Ammo_CoCo_m4",
		};
		magazines[]=
		{
			"coco_m4_mag"
		};
		recoilModifier[]={1,1,1};
		swayModifier[]={2,2,0.75};
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
	};
	class CoCo_m4_v1: CoCo_m4
	{
		scope=2;
		displayName="CoCo M4 v1";
		descriptionShort="CoCo M4 v1_by CoCo";
		barrelArmor=2.5;
		initSpeedMultiplier=1.0;
		chamberableFrom[]=
		{
			"Ammo_CoCo_m4",
		};
		magazines[]=
		{
			"coco_m4_mag_v1",
			"coco_m4_mag_v2",
			"coco_m4_mag_v3",
		};
		recoilModifier[]={1,1,1};
		swayModifier[]={2,2,0.75};
	};
	class CoCo_m4_v2: CoCo_m4
	{
		scope=2;
		displayName="CoCo M4 v2";
		descriptionShort="CoCo M4 v2_by CoCo";
		chamberableFrom[]=
		{
			"Ammo_CoCo_m4",
		};
		magazines[]=
		{
			"coco_m4_mag_v1",
			"coco_m4_mag_v2",
			"coco_m4_mag_v3",
		};
		recoilModifier[]={0.7,0.7,0.7};
		swayModifier[]={1.5,1.5,0.6};
	};
	class CoCo_m4_v3: CoCo_m4
	{
		scope=2;
		displayName="CoCo M4 v3";
		descriptionShort="CoCo M4 v3_by CoCo";
		chamberableFrom[]=
		{
			"Ammo_CoCo_m4",
		};
		magazines[]=
		{
			"coco_m4_mag_v1",
			"coco_m4_mag_v2",
			"coco_m4_mag_v3",
		};
		recoilModifier[]={0.4,0.4,0.4};
		swayModifier[]={0.5,0.5,0.4};
	};
};


class CfgMagazines
{
	class Mag_STANAG_30Rnd;
	class Magazine_Base;
	class Ammunition_Base;
	
	class coco_m4_mag: Mag_STANAG_30Rnd
	{
		scope=2;
		displayName="CoCo M4弹夹";
		descriptionShort="CoCo M4弹夹";
		itemSize[]={1,3};
		count=100;
		ammo="Bullet_CoCo_m4";
		ammoItems[]=
		{
			"Ammo_CoCo_m4",
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
								"DZ\weapons\attachments\data\m4_mag.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\m4_mag.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\m4_mag_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\m4_mag_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\m4_mag_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};

	class coco_m4_mag_v1: coco_m4_mag
	{
		scope=2;
		displayName="CoCo M4弹夹_V1";
		descriptionShort="CoCo M4弹夹_V1";
		count=50;
		ammo="Bullet_CoCo_m4";
		ammoItems[]=
		{
			"Ammo_CoCo_m4",
		};
	};

	class coco_m4_mag_v2: coco_m4_mag
	{
		scope=2;
		displayName="CoCo M4弹夹_V2";
		descriptionShort="CoCo M4弹夹_V2";
		count=65;
		ammo="Bullet_CoCo_m4";
		ammoItems[]=
		{
			"Ammo_CoCo_m4",
		};
	};

	class coco_m4_mag_v3: coco_m4_mag
	{
		scope=2;
		displayName="CoCo M4弹夹_V3";
		descriptionShort="CoCo M4弹夹_V3";
		count=80;
		ammo="Bullet_CoCo_m4";
		ammoItems[]=
		{
			"Ammo_CoCo_m4",
		};
	};

	class Ammo_CoCo_m4: Ammunition_Base
	{
		scope=2;
		displayName="CoCo M4子弹";
		descriptionShort="CoCo M4子弹";
		model="\dz\weapons\ammunition\556_LooseRounds.p3d";
		iconCartridge=2;
		weight=4;
		count=100;
		ammo="Bullet_CoCo_m4";
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
								"DZ\weapons\ammunition\data\556_LooseRounds5.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\ammunition\data\556_LooseRounds5.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\ammunition\data\556_LooseRounds5_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\ammunition\data\556_LooseRounds5_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\ammunition\data\556_LooseRounds5_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
}

class CfgAmmo
{
	class Bullet_556x45;
	class Bullet_CoCo_m4: Bullet_556x45
	{
		scope=1;
		spawnPileType="Ammo_CoCo_m4";
		class DamageApplied
		{
			type="Projectile";
			dispersion=0;
			bleedThreshold=1;
			defaultDamageOverride[]=
			{
				{0.87,1}
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
				damage=100;
			};
		};
	};
}


class cfgAmmoTypes
{
	class Bullet_CoCo_m4
	{
		name="Bullet_CoCo_m4";
	};
}

