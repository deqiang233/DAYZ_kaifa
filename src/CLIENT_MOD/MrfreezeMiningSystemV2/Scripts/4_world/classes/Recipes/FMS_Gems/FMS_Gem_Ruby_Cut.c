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
			player.LocalTakeEntityToInventory(InventoryMode.LOCAL, newGem);
			
			// FIX: Set quantity to 1 for stackable gems AFTER adding to inventory
			if (GetGame().IsServer() && newGem && newGem.HasQuantity())
			{
				// Set quantity immediately after adding to inventory
				SetGemQuantity(newGem);
				// Also use CallLater to ensure quantity is set (in case of timing issues)
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetGemQuantity, 50, false, newGem);
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetGemQuantity, 200, false, newGem);
			}
			
			// FIX: Set health to 100% for all gem types
			if (GetGame().IsServer())
			{
				// Try to set health immediately
				SetGemHealth(newGem);
				// Also use CallLater to set health after item is fully initialized
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetGemHealth, 100, false, newGem);
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetGemHealth, 500, false, newGem);
			}
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
	
	// Helper method to set gem quantity after adding to inventory
	static void SetGemQuantity(ItemBase gem)
	{
		if (!gem || !GetGame().IsServer())
			return;
		
		if (gem.HasQuantity())
		{
			int currentQty = gem.GetQuantity();
			int maxQty = gem.GetQuantityMax();
			
			// Set quantity to 1 if it's 0 or invalid
			if (currentQty <= 0 && maxQty > 0)
			{
				gem.SetQuantity(1);
				gem.SetSynchDirty(); // Sync to ensure quantity is saved
				
				// Debug log
				int newQty = gem.GetQuantity();
				LoggingUtility.LogDebug("[CraftRuby] SetGemQuantity - Type: " + gem.GetType() + " | MaxQty: " + maxQty + " | Set to: " + newQty);
			}
		}
	}
	
	// Helper method to set gem health after initialization
	static void SetGemHealth(ItemBase gem)
	{
		if (!gem || !GetGame().IsServer())
			return;
		
		// Try to get max health - use empty strings as that's the standard way
		float maxHealth = gem.GetMaxHealth("", "");
		if (maxHealth <= 0)
		{
			maxHealth = gem.GetMaxHealth("GlobalHealth", "Health");
		}
		// If maxHealth is still 0 or invalid, use default value of 100
		if (maxHealth <= 0)
		{
			maxHealth = 100;
		}
		
		// Set health to maximum value - try both methods
		if (maxHealth > 0)
		{
			// Use empty strings first as that's the standard way in DayZ
			gem.SetHealth("", "", maxHealth);
			// Also try with GlobalHealth as fallback
			gem.SetHealth("GlobalHealth", "Health", maxHealth);
			
			// Debug log
			float currentHealth = gem.GetHealth("", "");
			LoggingUtility.LogDebug("[CraftRuby] SetGemHealth - Type: " + gem.GetType() + " | MaxHealth: " + maxHealth + " | CurrentHealth: " + currentHealth);
		}
	}
};
