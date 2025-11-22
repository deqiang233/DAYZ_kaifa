class CraftRuby extends RecipeBase
{	
	static bool ENABLE_MINIGAME = true;

	override void Init()
	{
		m_Name = "Craft Ruby Gem";
		m_IsInstaRecipe = false;
		m_AnimationLength = 1;
		m_Specialty = 0.02;
		
		LoadConfig();

		InsertIngredient(0, "FreezeGem_Ruby");
		m_IngredientDestroy[0] = true;

		InsertIngredient(1, "FreezeGrindingStone");
		InsertIngredient(1, "FreezeGrindingStone_Static");
		m_IngredientDestroy[1] = false;
		m_IngredientAddHealth[1] = 0;
		m_IngredientSetHealth[1] = -1;

		
		AddResult("FreezeGem_Ruby_Cut");

		
		m_ResultSetQuantity[0] = 1;
		m_ResultSetHealth[0] = -1;
		m_ResultToInventory[0] = -1;
	}

	void LoadConfig()
	{
		if (GetGame().IsServer())
		{
			FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
			if (settings)
			{
				ENABLE_MINIGAME = (settings.EnableGemCuttingMiniGame == 1);
			}
		}
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftRuby"))
		{
			int seconds = g_FreezeCraftingTimes.Get("CraftRuby");
			m_AnimationLength = seconds * 0.25;
		}
		else if (GetGame().IsServer())
		{
			FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
			if (craftConfig)
			{
				m_AnimationLength = craftConfig.GetAnimationLength("CraftRuby");
			}
		}
		
		// Check for Static version first (admin-placed, no parts required)
		FreezeGrindingStone_Static staticGrindstone = FreezeGrindingStone_Static.Cast(ingredients[1]);
		if (staticGrindstone)
		{
			return true; // Static grindstone works without parts
		}
		
		// Regular grindstone requires wheel
		FreezeGrindingStone grindingStone = FreezeGrindingStone.Cast(ingredients[1]);
		if (grindingStone)
		{
			if (!grindingStone.HasGrindingWheel())
			{
				return false;
			}
		}
		
		return true;
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		// Handle both Static and regular grindstones
		FreezeGrindingStone_Static staticGrindstone = FreezeGrindingStone_Static.Cast(ingredients[1]);
		FreezeGrindingStone grindingStone = FreezeGrindingStone.Cast(ingredients[1]);
		
		if (GetGame().IsServer())
		{
			if (staticGrindstone)
			{
				staticGrindstone.SetGrinding(true);
			}
			else if (grindingStone)
			{
				grindingStone.SetGrinding(true);
			}
		}

		if (grindingStone && GetGame().IsServer())
		{
			// Only deplete wheel on regular grindstone (Static doesn't have parts)
			if (!staticGrindstone)
			{
				grindingStone.DepleteGrindingWheel();
			}
			
			int configSeconds = 15;
			if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftRuby"))
			{
				configSeconds = g_FreezeCraftingTimes.Get("CraftRuby");
			}
			else
			{
				FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
				if (craftConfig)
				{
					configSeconds = craftConfig.GetCraftTimeSeconds("CraftRuby");
				}
			}
			
			float actualCraftTime = m_AnimationLength * 4;
			LoggingUtility.LogDebug("[GrindingStone] CraftRuby - Config: " + configSeconds + "s | Actual: " + actualCraftTime + "s | AnimLength: " + m_AnimationLength + " | Player: " + player.GetIdentity().GetName());
		}

		string gemResult;

		
		if (!ENABLE_MINIGAME)
		{
			gemResult = "FreezeGem_Ruby_Cut";
		}
		else
		{
			
			float roll = Math.RandomFloatInclusive(0, 1);

			if (roll <= 0.50)
			{
				gemResult = "FreezeGem_Ruby_Flawed";
			}
			else if (roll <= 0.85)
			{
				gemResult = "FreezeGem_Ruby_Standard";
			}
			else
			{
				gemResult = "FreezeGem_Ruby_Perfect";
			}
		}


		if (results.Count() > 0)
		{
			ItemBase oldResult = results[0];
			GetGame().ObjectDelete(oldResult);
		}


		ItemBase newGem = ItemBase.Cast(GetGame().CreateObjectEx(gemResult, player.GetPosition(), ECE_PLACE_ON_SURFACE));
		if (newGem)
		{
			// FIX: Set quantity to 1 for stackable gems
			if (newGem.IsSplitable())
			{
				newGem.SetQuantity(1);
			}
			player.LocalTakeEntityToInventory(InventoryMode.LOCAL, newGem);
		}
		
		if (GetGame().IsServer())
		{
			if (staticGrindstone)
			{
				staticGrindstone.SetGrinding(false);
			}

			if (grindingStone)
			{
				grindingStone.SetGrinding(false);
			}
		}
	}
};
