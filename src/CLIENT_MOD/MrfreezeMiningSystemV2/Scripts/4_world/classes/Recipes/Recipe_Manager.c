modded class PluginRecipesManager 
{

 	override void RegisterRecipies()
	{
		super.RegisterRecipies();

		// Kits Deploy
		RegisterRecipe(new CraftAnvil);
		RegisterRecipe(new CraftFurnace);
		RegisterRecipe(new CraftGrindingStone);

		// Kits Disassemble
		RegisterRecipe(new DeCraftAnvil);
		RegisterRecipe(new DeCraftFurnace);
		RegisterRecipe(new DeCraftGrindingstone);

		//Anvil Gem Crafting
		RegisterRecipe(new CraftAmber);
		RegisterRecipe(new CraftAmethyst);
		RegisterRecipe(new CraftAquamarine);
		RegisterRecipe(new CraftFancyColourDiamond);
		RegisterRecipe(new CraftIolite);
		RegisterRecipe(new CraftJade);
		RegisterRecipe(new CraftRuby);
		RegisterRecipe(new CraftTurquoise);

		// NORMAL BARS - 6 recipes
		RegisterRecipe(new CraftCopperIngot);
		RegisterRecipe(new CraftGoldIngot);
		RegisterRecipe(new CraftIronIngot);
		RegisterRecipe(new CraftSilverIngot);
		RegisterRecipe(new CraftTinIngot);
		RegisterRecipe(new CraftUraniumIngot);

		RegisterRecipe(new CraftSulphurPowder);

		// NORMAL BARS (MiniGameOff) 5 recipes)
		RegisterRecipe(new CraftAdamantite);
		RegisterRecipe(new CraftCobalt);
		RegisterRecipe(new CraftCrimant);
		RegisterRecipe(new CraftEnchanted);
		RegisterRecipe(new CraftEridium);

		// PICKAXE UPGRADES - Tier progression tools
		RegisterRecipe(new CraftT1ReinforcedPickaxe);
		RegisterRecipe(new CraftT2CrystalforgePickaxe);
		RegisterRecipe(new CraftT3FusioncorePickaxe);

		// MiniGameOn
		// T1: FLAWED BARS - All 8 recipes
		RegisterRecipe(new CraftBronzeFlawed);
		RegisterRecipe(new CraftSteelFlawed);
		RegisterRecipe(new CraftElectrumFlawed);
		RegisterRecipe(new CraftCompositeFlawed);
		RegisterRecipe(new CraftCrystalFlawed);
		RegisterRecipe(new CraftPrismaticFlawed);
		RegisterRecipe(new CraftVoidFlawed);
		RegisterRecipe(new CraftRubyFlawed);
		
		// T2: STANDARD BARS - All 8 recipes
		RegisterRecipe(new CraftBronzeStandard);
		RegisterRecipe(new CraftSteelStandard);
		RegisterRecipe(new CraftElectrumStandard);
		RegisterRecipe(new CraftCompositeStandard);
		RegisterRecipe(new CraftCrystalStandard);
		RegisterRecipe(new CraftPrismaticStandard);
		RegisterRecipe(new CraftVoidStandard);
		RegisterRecipe(new CraftRubyStandard);
		
		// T3: PERFECT BARS - All 8 recipes
		RegisterRecipe(new CraftBronzePerfect);
		RegisterRecipe(new CraftSteelPerfect);
		RegisterRecipe(new CraftElectrumPerfect);
		RegisterRecipe(new CraftCompositePerfect);
		RegisterRecipe(new CraftCrystalPerfect);
		RegisterRecipe(new CraftPrismaticPerfect);
		RegisterRecipe(new CraftVoidPerfect);
		RegisterRecipe(new CraftRubyPerfect);
		
		// T4: LEGENDARY BARS - All 4 recipes
		RegisterRecipe(new CraftCelestial);
		RegisterRecipe(new CraftInfinity);
		RegisterRecipe(new CraftAscendant);
		RegisterRecipe(new CraftTitanforge);
		
		// T5: MYTHIC BARS - All 2 recipes
		RegisterRecipe(new CraftVoidsteel);
		RegisterRecipe(new CraftBloodmetal);
		
		// T6: ULTIMATE BAR - The final recipe
		RegisterRecipe(new CraftNexus);
		
	}
};