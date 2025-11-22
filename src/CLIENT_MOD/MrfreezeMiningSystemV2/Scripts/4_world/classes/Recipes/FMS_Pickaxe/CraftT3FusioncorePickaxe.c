class CraftT3FusioncorePickaxe extends RecipeBase
{	
	override void Init()
	{
		m_Name = "Craft T3 Fusioncore Pickaxe";
		m_IsInstaRecipe = false;
		m_AnimationLength = 15; // AnimationLength = 4sec 4x15=60 = 1min
		m_Specialty = 0.02;
		
		//conditions
		m_MinDamageIngredient[0] = -1;
		m_MaxDamageIngredient[0] = 3;
		
		m_MinQuantityIngredient[0] = 1;
		m_MaxQuantityIngredient[0] = -1;
		
		m_MinDamageIngredient[1] = -1;
		m_MaxDamageIngredient[1] = 3;
		
		m_MinQuantityIngredient[1] = 20;
		m_MaxQuantityIngredient[1] = -1;
		
		//ingredient 1
		InsertIngredient(0,"Pickaxe");
		
		m_IngredientAddHealth[0] = 0;
		m_IngredientSetHealth[0] = -1;
		m_IngredientAddQuantity[0] = 0;
		m_IngredientDestroy[0] = true;
		m_IngredientUseSoftSkills[0] = false;

		//ingredient 2
		InsertIngredient(1,"FreezeGem_Amethyst_Perfect");
		
		m_IngredientAddHealth[1] = 0;
		m_IngredientSetHealth[1] = -1;
		m_IngredientAddQuantity[1] = -20;
		m_IngredientDestroy[1] = false;
		m_IngredientUseSoftSkills[1] = false;
		
		//result1
		AddResult("Freeze_T3Fusioncore_Pickaxe");

		m_ResultSetFullQuantity[0] = false;
		m_ResultSetQuantity[0] = -1;
		m_ResultSetHealth[0] = -1;
		m_ResultInheritsHealth[0] = -1;
		m_ResultInheritsColor[0] = -1;
		m_ResultToInventory[0] = -2;
		m_ResultUseSoftSkills[0] = false;
		m_ResultReplacesIngredient[0] = -1;
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftT3FusioncorePickaxe"))
		{
			int seconds = g_FreezeCraftingTimes.Get("CraftT3FusioncorePickaxe");
			m_AnimationLength = seconds * 0.25;
		}
		else if (GetGame().IsServer())
		{
			FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
			if (craftConfig)
			{
				m_AnimationLength = craftConfig.GetAnimationLength("CraftT3FusioncorePickaxe");
			}
		}
		return true;
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{		if (GetGame().IsServer())
		{
			int configSeconds = 4;
			if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftT3FusioncorePickaxe"))
			{
				configSeconds = g_FreezeCraftingTimes.Get("CraftT3FusioncorePickaxe");
			}
			else
			{
				FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
				if (craftConfig)
				{
					configSeconds = craftConfig.GetCraftTimeSeconds("CraftT3FusioncorePickaxe");
				}
			}
			
			float actualCraftTime = m_AnimationLength * 4;
			LoggingUtility.LogDebug("[InHand] CraftT3FusioncorePickaxe - Config: " + configSeconds + "s | Actual: " + actualCraftTime + "s | AnimLength: " + m_AnimationLength + " | Player: " + player.GetIdentity().GetName());
		}
	}
}; 