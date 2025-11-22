modded class FreezeAnvil
{
	// Mining/Crafting process methods moved from FMS_Anvil_Kit.c
	
	bool HasAnvilHammer()
	{
		int slotId_Hammer = InventorySlots.GetSlotIdFromString("FMS_Anvil_HammerActive");
		ItemBase hammer = ItemBase.Cast(GetInventory().FindAttachment(slotId_Hammer));
		
		if (hammer && !hammer.IsRuined())
		{
			return true;
		}
		
		return false;
	}

	void DamageAnvilHammer(float damageAmount = -1)
	{
		FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
		float damage = damageAmount;
		
		if (damageAmount < 0)
		{
			damage = settings.AnvilHammerDamage;
		}
		
		int slotId_Hammer = InventorySlots.GetSlotIdFromString("FMS_Anvil_HammerActive");
		ItemBase hammer = ItemBase.Cast(GetInventory().FindAttachment(slotId_Hammer));
		
		if (hammer)
		{
			hammer.DecreaseHealth("", "", damage);
			hammer.SetSynchDirty();
			LoggingUtility.LogDebug("[FreezeAnvil] Hammer damaged by " + damage + ", remaining health: " + hammer.GetHealth());
		}
	}
}

