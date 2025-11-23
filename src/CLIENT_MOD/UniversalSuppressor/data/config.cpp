class CfgPatches
{
	class UniversalSuppressor
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Muzzles"
		};
	};
};

class cfgVehicles
{
	class M4_Suppressor;
	class ItemBarrel;
	class ItemSuppressor;
	
	class UniversalSuppressorBlackRed: ItemSuppressor
	{
		scope=2;
		displayName="黑红消音";
		descriptionShort="黑红消音|by_cyx";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		swayModifier[]={1,1,1};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\redtriangles.paa",
			"UniversalSuppressor\data\redtriangles.paa",
			"UniversalSuppressor\data\redtriangles.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=9999999;
				};
			};
		};
	};
	
	
	class CoCo_xiaoyin_heihong_v1: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.90";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_heihong_v2: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.80";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_heihong_v3: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.70";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_heihong_v4: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.60";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_heihong_v5: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.50";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_heihong_v6: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.40";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_heihong_v7: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.30";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_heihong_v8: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.20";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_heihong_v9: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.10";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_heihong_v10: UniversalSuppressorBlackRed
	{
		displayName="黑红消音_后座 0.00";
		descriptionShort="黑红消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
	
	
	class UniversalSuppressorBlueHex: ItemSuppressor
	{
		scope=2;
		displayName="Blue Hex Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\bluehex.paa",
			"UniversalSuppressor\data\bluehex.paa",
			"UniversalSuppressor\data\bluehex.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};

	class CoCo_xiaoyin_lanse_v1: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.90";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_lanse_v2: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.80";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_lanse_v3: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.70";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_lanse_v4: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.60";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_lanse_v5: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.50";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_lanse_v6: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.40";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_lanse_v7: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.30";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_lanse_v8: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.20";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_lanse_v9: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.10";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	
	
	class CoCo_xiaoyin_lanse_v10: UniversalSuppressorBlueHex
	{
		displayName="蓝色消音_后座 0.00";
		descriptionShort="蓝色消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};


	
	class UniversalSuppressorSnow: ItemSuppressor
	{
		scope=2;
		displayName="Snow Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\wintercam.paa",
			"UniversalSuppressor\data\wintercam.paa",
			"UniversalSuppressor\data\wintercam.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};
	class CoCo_xiaoyin_xuedi_v1: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.90";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_xuedi_v2: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.80";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_xuedi_v3: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.70";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_xuedi_v4: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.60";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_xuedi_v5: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.50";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_xuedi_v6: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.40";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_xuedi_v7: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.30";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_xuedi_v8: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.20";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_xuedi_v9: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.10";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_xuedi_v10: UniversalSuppressorSnow
	{
		displayName="雪地消音_后座 0.00";
		descriptionShort="雪地消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
	
	class UniversalSuppressorGalaxy: ItemSuppressor
	{
		scope=2;
		displayName="Galaxy Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\galaxy.paa",
			"UniversalSuppressor\data\galaxy.paa",
			"UniversalSuppressor\data\galaxy.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};
	class CoCo_xiaoyin_yinhe_v1: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.90";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_yinhe_v2: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.80";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_yinhe_v3: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.70";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_yinhe_v4: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.60";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_yinhe_v5: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.50";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_yinhe_v6: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.40";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_yinhe_v7: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.30";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_yinhe_v8: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.20";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_yinhe_v9: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.10";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_yinhe_v10: UniversalSuppressorGalaxy
	{
		displayName="银河消音_后座 0.00";
		descriptionShort="银河消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
	
	class UniversalSuppressorTan: ItemSuppressor
	{
		scope=2;
		displayName="Tan Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\solidtan.paa",
			"UniversalSuppressor\data\solidtan.paa",
			"UniversalSuppressor\data\solidtan.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};
	class CoCo_xiaoyin_micai_v1: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.90";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_micai_v2: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.80";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_micai_v3: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.70";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_micai_v4: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.60";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_micai_v5: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.50";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_micai_v6: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.40";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_micai_v7: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.30";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_micai_v8: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.20";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_micai_v9: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.10";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_micai_v10: UniversalSuppressorTan
	{
		displayName="迷彩消音_后座 0.00";
		descriptionShort="迷彩消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
	
	class UniversalSuppressorBlack: ItemSuppressor
	{
		scope=2;
		displayName="Black Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\solidblack.paa",
			"UniversalSuppressor\data\solidblack.paa",
			"UniversalSuppressor\data\solidblack.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};

	class CoCo_xiaoyin_hei_v1: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.90";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_hei_v2: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.80";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_hei_v3: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.70";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_hei_v4: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.60";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_hei_v5: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.50";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_hei_v6: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.40";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_hei_v7: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.30";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_hei_v8: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.20";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_hei_v9: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.10";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_hei_v10: UniversalSuppressorBlack
	{
		displayName="黑色消音_后座 0.00";
		descriptionShort="黑色消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
	
	class UniversalSuppressorGreen: ItemSuppressor
	{
		scope=2;
		displayName="Green Universal Suppressor";
		descriptionShort="An awesome universal suppressor that'll fit any weapon with a native suppressor slot. Made by Quantum.";
		model="\dz\weapons\attachments\muzzle\suppressor_556.p3d";
		rotationFlags=17;
		reversed=0;
		weight=73;
		itemSize[]={3,1};
		itemModelLength=0.148;
		barrelArmor=2250;
		lootCategory="Attachments";
		lootTag[]=
		{
			"Military_west"
		};
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro",
			"weaponMuzzleAK",
			"pistolMuzzle"
		};
		simulation="ItemSuppressor";
		dispersionModifier=-0.00050000002;
		dispersionCondition="true";
		noiseShootModifier=-0.89999998;
		recoilModifier[]={0.89999998,0.89999998,0.89999998};
		swayModifier[]={1.3,1.3,1.3};
		selectionFireAnim="zasleh";
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"UniversalSuppressor\data\solidgreen.paa",
			"UniversalSuppressor\data\solidgreen.paa",
			"UniversalSuppressor\data\solidgreen.paa"
		};
		soundIndex=1;
		muzzlePos="usti hlavne";
	};
		class CoCo_xiaoyin_lv_v1: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.90";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.9,0.9,0.9};
	};
	

	class CoCo_xiaoyin_lv_v2: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.80";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.8,0.8,0.8};
	};
	

	
	class CoCo_xiaoyin_lv_v3: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.70";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.7,0.7,0.7};
	};
	

	class CoCo_xiaoyin_lv_v4: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.60";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.6,0.6,0.6};
	};
	

	
	class CoCo_xiaoyin_lv_v5: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.50";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.5,0.5,0.5};
	};
	

	class CoCo_xiaoyin_lv_v6: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.40";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.4,0.4,0.4};
	};
	
	
	class CoCo_xiaoyin_lv_v7: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.30";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.3,0.3,0.3};
	};

	
	class CoCo_xiaoyin_lv_v8: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.20";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.2,0.2,0.2};
	};
	
	
	class CoCo_xiaoyin_lv_v9: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.10";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.1,0.1,0.1};
	};
	

	
	class CoCo_xiaoyin_lv_v10: UniversalSuppressorGreen
	{
		displayName="绿色消音_后座 0.00";
		descriptionShort="绿色消音 | by_cyx";
		recoilModifier[]={0.0,0.0,0.0};
	};
};