modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("FreezeFurnace_Pipe", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_pipe.asi", pBehavior, "dz/anims/anm/player/ik/gear/LongWoodenStick.anm");
		
		// Raw gems - Small Stone animation
		pType.AddItemInHandsProfileIK("FreezeGem_Jade", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amber", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Iolite", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amethyst", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Aquamarine", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Ruby", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Turquoise", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_FancyColourDiamond", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/SmallStone.anm");
		
		// Flawed gems - Potato animation
		pType.AddItemInHandsProfileIK("FreezeGem_Jade_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amber_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Iolite_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amethyst_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Aquamarine_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Ruby_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Turquoise_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_FancyColourDiamond_Flawed", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		
		// Standard gems - Apple animation
		pType.AddItemInHandsProfileIK("FreezeGem_Jade_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amber_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Iolite_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amethyst_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Aquamarine_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Ruby_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Turquoise_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_FancyColourDiamond_Standard", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		
		// Perfect gems - Apple animation
		pType.AddItemInHandsProfileIK("FreezeGem_Jade_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amber_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Iolite_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amethyst_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Aquamarine_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Ruby_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Turquoise_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_FancyColourDiamond_Perfect", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		
		// Cut gems - Apple animation
		pType.AddItemInHandsProfileIK("FreezeGem_Jade_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amber_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Iolite_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Amethyst_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Aquamarine_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Ruby_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_Turquoise_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
		pType.AddItemInHandsProfileIK("FreezeGem_FancyColourDiamond_Cut", "dz/anims/workspaces/player/player_main/props/player_main_1h_fruit.asi", pBehavior, "dz/anims/anm/player/ik/gear/apple.anm");
	}
	
	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("FreezeFurnace_Canister", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/spotlight.anm");
		pType.AddItemInHandsProfileIK("FreezeBar_base", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/BatteryCar.anm");
	}
	
	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterHeavy(pType, pBehavior);
		pType.AddItemInHandsProfileIK("FreezeGrindingStoneWheel", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Wheel.anm");
	}
};
