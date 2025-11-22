class FreezeHammer extends ItemBase
{
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LogHammerState, 2000, false);
		}
	}
	
	void LogHammerState()
	{
		if (!GetGame().IsServer())
			return;
		
		float health = GetHealth("", "");
		float maxHealth = GetMaxHealth("", "");
		string parentInfo = "standalone";
		EntityAI parent = GetHierarchyParent();
		if (parent)
		{
			parentInfo = "attached to " + parent.GetType();
		}
		LoggingUtility.LogDebug("[FreezeHammer] EEInit (delayed) - Health=" + health + "/" + maxHealth + " (" + (health / maxHealth * 100) + "%), Parent=" + parentInfo);
	}
}

