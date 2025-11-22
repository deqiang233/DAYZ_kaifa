class CraftPrismaticFlawed extends RecipeBase
{	
	override void Init()
	{
		m_Name = "Craft Prismatic Fusion Bar (Flawed)";
		m_IsInstaRecipe = false;
		m_AnimationLength = 5; // AnimationLength = 4sec 5x15=20 = 20Sec
		m_Specialty = 0.02;
		
		m_MinDamageIngredient[0] = -1;
		m_MaxDamageIngredient[0] = -1;
		m_MinQuantityIngredient[0] = 1;
		m_MaxQuantityIngredient[0] = -1;
		
		m_MinDamageIngredient[1] = -1;
		m_MaxDamageIngredient[1] = -1;
		m_MinQuantityIngredient[1] = 10;
		m_MaxQuantityIngredient[1] = -1;
		
		//INGREDIENTS
		InsertIngredient(0, "FreezeBar_tin");
		m_IngredientAddHealth[0] = 0;
		m_IngredientSetHealth[0] = -1;
		m_IngredientAddQuantity[0] = -1;
		m_IngredientDestroy[0] = false;
		m_IngredientUseSoftSkills[0] = false;
		
		InsertIngredient(1,"FreezeGem_Turquoise_Flawed");
		m_IngredientAddHealth[1] = 0;
		m_IngredientSetHealth[1] = -1;
		m_IngredientAddQuantity[1] = -10;
		m_IngredientDestroy[1] = false;
		m_IngredientUseSoftSkills[1] = false;
		
		//RESULT
		AddResult("FreezeBar_Prismatic_Flawed");
		m_ResultSetFullQuantity[0] = false;
		m_ResultSetQuantity[0] = 1;
		m_ResultSetHealth[0] = 1.0;
		m_ResultInheritsHealth[0] = -2;
		m_ResultInheritsColor[0] = -1;
		m_ResultToInventory[0] = -2;
		m_ResultUseSoftSkills[0] = false;
		m_ResultReplacesIngredient[0] = -1;
	}

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("Tier1_CraftPrismaticFlawed"))
        {
            int seconds = g_FreezeCraftingTimes.Get("Tier1_CraftPrismaticFlawed");
            m_AnimationLength = seconds * 0.25;
        }
        else if (GetGame().IsServer())
        {
            FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
            if (craftConfig)
            {
                m_AnimationLength = craftConfig.GetAnimationLength("Tier1_CraftPrismaticFlawed");
            }
        }
        return true;
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {        if (GetGame().IsServer())
        {
            int configSeconds = 4;
            if (g_FreezeCraftingTimes && g_FreezeCraftingTimes.Contains("Tier1_CraftPrismaticFlawed"))
            {
                configSeconds = g_FreezeCraftingTimes.Get("Tier1_CraftPrismaticFlawed");
            }
            else
            {
                FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
                if (craftConfig)
                {
                    configSeconds = craftConfig.GetCraftTimeSeconds("Tier1_CraftPrismaticFlawed");
                }
            }
            
            float actualCraftTime = m_AnimationLength * 4;
            LoggingUtility.LogDebug("[InHand] Tier1_CraftPrismaticFlawed - Config: " + configSeconds + "s | Actual: " + actualCraftTime + "s | AnimLength: " + m_AnimationLength + " | Player: " + player.GetIdentity().GetName());
        }
    }
}; 