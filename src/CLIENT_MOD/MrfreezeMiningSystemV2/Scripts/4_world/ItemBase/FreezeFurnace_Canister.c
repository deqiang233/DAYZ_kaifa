class FreezeFurnace_Canister extends Inventory_Base
{
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LogCanisterState, 2000, false);
		}
	}
	
	void LogCanisterState()
	{
		if (!GetGame().IsServer())
			return;
		
		float qty = GetQuantity();
		float max = GetQuantityMax();
		string parentInfo = "standalone";
		EntityAI parent = GetHierarchyParent();
		if (parent)
		{
			parentInfo = "attached to " + parent.GetType();
		}
		LoggingUtility.LogDebug("[FreezeFurnace_Canister] EEInit (delayed) - Qty=" + qty + "/" + max + " (" + (qty / max * 100) + "%), Parent=" + parentInfo);
	}
}

