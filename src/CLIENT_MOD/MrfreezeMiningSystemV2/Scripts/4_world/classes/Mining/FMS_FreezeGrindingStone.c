modded class FreezeGrindingStone
{
	// Mining/Crafting process methods moved from FMS_GrindingStone_Kit.c
	
	bool HasGrindingWheel()
	{
		int slotId_Wheel = InventorySlots.GetSlotIdFromString("FMS_GrindingStoneWheel");
		ItemBase wheel = ItemBase.Cast(GetInventory().FindAttachment(slotId_Wheel));
		
		if (wheel)
		{
			if (wheel.GetQuantity() > 0)
			{
				return true;
			}
		}
		
		return false;
	}

	void DepleteGrindingWheel(float amount = -1)
	{
		FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
		float usageRate = amount;
		
		if (amount < 0)
		{
			usageRate = settings.GrindingWheelUsage;
		}
		
		int slotId_Wheel = InventorySlots.GetSlotIdFromString("FMS_GrindingStoneWheel");
		ItemBase wheel = ItemBase.Cast(GetInventory().FindAttachment(slotId_Wheel));
		
		if (wheel)
		{
			float currentQty = wheel.GetQuantity();
			float newQty = currentQty - usageRate;
			
			if (newQty <= 0)
			{
				wheel.SetQuantity(0);
				wheel.SetSynchDirty();
				LoggingUtility.LogDebug("[FreezeGrindingStone] Grinding wheel depleted");
			}
			else
			{
				wheel.SetQuantity(newQty);
				wheel.SetSynchDirty();
			}
		}
	}
}

