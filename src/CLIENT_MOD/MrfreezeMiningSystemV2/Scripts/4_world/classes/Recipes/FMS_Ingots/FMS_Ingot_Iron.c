class CraftIronIngot extends RecipeBase
{	

    override void Init()
    {
        m_Name = "Craft Iron Ingot";
        m_IsInstaRecipe = false;
        m_AnimationLength = 1;
        m_Specialty = 0.02; // value > 0 for roughness, value < 0 for precision

        // conditions
        m_MinDamageIngredient[0] = -1; // -1 = disable check
        m_MaxDamageIngredient[0] = -1; // -1 = disable check
        
        m_MinQuantityIngredient[0] = 10; // -1 = disable check
        m_MaxQuantityIngredient[0] = -1; // -1 = disable check
        
        m_MinDamageIngredient[1] = -1; // -1 = disable check
        m_MaxDamageIngredient[1] = -1; // -1 = disable check
        
        m_MinQuantityIngredient[1] = -1; // -1 = disable check
        m_MaxQuantityIngredient[1] = -1; // -1 = disable check
        //----------------------------------------------------------------------------------------------------------------------

        // INGREDIENTS
        // ingredient 1
        InsertIngredient(0, "FreezeNugget_iron"); // you can insert multiple ingredients this way
        
        m_IngredientAddHealth[0] = 0; // 0 = do nothing
        m_IngredientSetHealth[0] = -1; // -1 = do nothing
        m_IngredientAddQuantity[0] = -10; // 0 = do nothing
        m_IngredientDestroy[0] = true; // true = destroy, false = do nothing
        m_IngredientUseSoftSkills[0] = false; // set 'true' to allow modification of the values by softskills on this ingredient

        // ingredient 2
        InsertIngredient(1, "FreezeAnvil"); // you can insert multiple ingredients this way
        InsertIngredient(1, "FreezeAnvil_Static"); // you can insert multiple ingredients this way

        m_IngredientAddHealth[1] = 0; // 0 = do nothing
        m_IngredientSetHealth[1] = -1; // -1 = do nothing
        m_IngredientAddQuantity[1] = 0; // 0 = do nothing
        m_IngredientDestroy[1] = false; // false = do nothing
        m_IngredientUseSoftSkills[1] = false; // set 'true' to allow modification of the values by softskills on this ingredient
        //----------------------------------------------------------------------------------------------------------------------

        // result1
        AddResult("FreezeBar_iron"); // add results here
        
        m_ResultSetFullQuantity[0] = false; // true = set full quantity, false = do nothing
        m_ResultSetQuantity[0] = 1; // -1 = do nothing
        m_ResultSetHealth[0] = -1; // -1 = do nothing
        m_ResultInheritsHealth[0] = -2; // (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
        m_ResultInheritsColor[0] = -1; // (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
        m_ResultToInventory[0] = -2; // (value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
        m_ResultUseSoftSkills[0] = false; // set 'true' to allow modification of the values by softskills on this result
        m_ResultReplacesIngredient[0] = -1; // value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player) // final check for recipe's validity
    {
        if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftIronIngot"))
        {
            int seconds = g_FreezeCraftingTimes.Get("CraftIronIngot");
            m_AnimationLength = seconds * 0.25;
        }
        else if (GetGame().IsServer())
        {
            FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
            if (craftConfig)
            {
                m_AnimationLength = craftConfig.GetAnimationLength("CraftIronIngot");
            }
        }
        
        // Check for Static version first (admin-placed, no parts required)
        FreezeAnvil_Static staticAnvil = FreezeAnvil_Static.Cast(ingredients[1]);
        if (staticAnvil)
        {
            return true; // Static anvil works without parts
        }
        
        // Regular anvil requires hammer
        FreezeAnvil anvil = FreezeAnvil.Cast(ingredients[1]);
        if (anvil)
        {
            if (!anvil.HasAnvilHammer())
            {
                return false;
            }
            return true;
        }
        
        return false;
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight) // gets called upon recipe's completion
    {        // Handle both Static and regular anvils
        FreezeAnvil_Static staticAnvil = FreezeAnvil_Static.Cast(ingredients[1]);
        FreezeAnvil anvil = FreezeAnvil.Cast(ingredients[1]);
        
		if (GetGame().IsServer())
		{
			if (staticAnvil)
			{
				staticAnvil.SetForging(true);
			}
			else if (anvil)
			{
				anvil.SetForging(true);
			}
		}

		if (anvil && GetGame().IsServer())
		{
			// Only damage hammer on regular anvil (Static doesn't have parts)
			if (!staticAnvil)
			{
				anvil.DamageAnvilHammer();
			}
			
			int configSeconds = 4;
			if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("CraftIronIngot"))
			{
				configSeconds = g_FreezeCraftingTimes.Get("CraftIronIngot");
			}
			else
			{
				FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
				if (craftConfig)
				{
					configSeconds = craftConfig.GetCraftTimeSeconds("CraftIronIngot");
				}
			}
			
			float actualCraftTime = m_AnimationLength * 4;
			LoggingUtility.LogDebug("[Anvil] CraftIronIngot - Config: " + configSeconds + "s | Actual: " + actualCraftTime + "s | AnimLength: " + m_AnimationLength + " | Player: " + player.GetIdentity().GetName());
		}
		
		if (GetGame().IsServer())
		{
			if (staticAnvil)
			{
				staticAnvil.SetForging(false);
			}

			if (anvil)
			{
				anvil.SetForging(false);
			}
		}
    }
};
