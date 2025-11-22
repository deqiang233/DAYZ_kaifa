modded class FreezeFurnace
{
	private bool m_HasLoggedInitialState = false;
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LogInitialCanisterState, 1000, false);
		}
	}
	
	void LogInitialCanisterState()
	{
		if (!GetGame().IsServer())
			return;
		
		LoggingUtility.LogDebug("[FreezeFurnace] ===== FURNACE INITIALIZATION =====");
		LogCanisterState("EEInit-InitialLoad");
		LoggingUtility.LogDebug("[FreezeFurnace] ====================================");
		m_HasLoggedInitialState = true;
	}
	
	override void SwitchOnServer()
	{
		super.SwitchOnServer();
		
		LogCanisterState("SwitchOnServer");
		ScheduleNextSmelt();
	}
	
	void LogCanisterState(string context)
	{
		if (!GetGame().IsServer())
			return;
		
		// Static furnaces don't have canisters
		FreezeFurnace_Static staticFurnace = FreezeFurnace_Static.Cast(this);
		if (staticFurnace)
		{
			LoggingUtility.LogDebug("[FreezeFurnace] " + context + " - Static furnace (no canister)");
			return;
		}
		
		int slotId_Canister = InventorySlots.GetSlotIdFromString("FMS_Propane_Canister");
		ItemBase canister = ItemBase.Cast(GetInventory().FindAttachment(slotId_Canister));
		
		if (canister)
		{
			float qty = canister.GetQuantity();
			float max = canister.GetQuantityMax();
			string canisterType = canister.GetType();
			LoggingUtility.LogDebug("[FreezeFurnace] " + context + " - Canister State: Type=" + canisterType + ", Qty=" + qty + "/" + max + " (" + (qty / max * 100) + "%)");
		}
		else
		{
			LoggingUtility.LogDebug("[FreezeFurnace] " + context + " - Canister State: NOT ATTACHED");
		}
	}
	
	bool HasPropaneSetup()
	{
		// Static furnaces work without parts (admin-placed)
		FreezeFurnace_Static staticFurnace = FreezeFurnace_Static.Cast(this);
		if (staticFurnace)
		{
			return true; // Static furnace works without propane setup
		}
		
		// Regular furnace requires propane canister, pipe, AND wooden crate
		int slotId_Canister = InventorySlots.GetSlotIdFromString("FMS_Propane_Canister");
		ItemBase canister = ItemBase.Cast(GetInventory().FindAttachment(slotId_Canister));
		
		int slotId_Pipe = InventorySlots.GetSlotIdFromString("FMS_Propane_Pipe");
		ItemBase pipe = ItemBase.Cast(GetInventory().FindAttachment(slotId_Pipe));
		
		// Check for wooden crate (required for FreezeFurnace, not Static)
		bool hasCrate = HasWoodenCrate();
		
		string canisterStatus = "missing";
		string pipeStatus = "missing";
		string crateStatus = "missing";
		
		if (canister && pipe && hasCrate)
		{
			float canisterQty = canister.GetQuantity();
			float canisterMax = canister.GetQuantityMax();
			canisterStatus = "attached";
			pipeStatus = "attached";
			crateStatus = "attached";
			LoggingUtility.LogDebug("[FreezeFurnace] HasPropaneSetup check - Canister Qty: " + canisterQty + "/" + canisterMax + ", Pipe: " + pipeStatus + ", Crate: " + crateStatus);
			
			if (canisterQty > 0)
			{
				return true;
			}
		}
		else
		{
			if (canister)
			{
				canisterStatus = "attached";
			}
			if (pipe)
			{
				pipeStatus = "attached";
			}
			if (hasCrate)
			{
				crateStatus = "attached";
			}
			LoggingUtility.LogDebug("[FreezeFurnace] HasPropaneSetup check - Canister: " + canisterStatus + ", Pipe: " + pipeStatus + ", Crate: " + crateStatus);
		}
		
		return false;
	}
	
	void DepletePropaneCanister()
	{
		// Static furnaces don't have parts to deplete
		FreezeFurnace_Static staticFurnace = FreezeFurnace_Static.Cast(this);
		if (staticFurnace)
		{
			return; // Static furnace doesn't deplete propane
		}
		
		FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
		float usageRate = settings.PropaneCanisterUsage;
		
		int slotId_Canister = InventorySlots.GetSlotIdFromString("FMS_Propane_Canister");
		ItemBase canister = ItemBase.Cast(GetInventory().FindAttachment(slotId_Canister));
		
		if (canister)
		{
			float currentQty = canister.GetQuantity();
			float canisterMax = canister.GetQuantityMax();
			float newQty = currentQty - usageRate;
			
			LoggingUtility.LogDebug("[FreezeFurnace] DepletePropaneCanister - BEFORE: Qty=" + currentQty + "/" + canisterMax + ", UsageRate=" + usageRate + ", NewQty=" + newQty);
			
			if (newQty <= 0)
			{
				canister.SetQuantity(0);
				canister.SetSynchDirty(); // Sync canister to save state
				SetSynchDirty(); // Sync parent furnace container to ensure attached item state persists
				LoggingUtility.LogDebug("[FreezeFurnace] DepletePropaneCanister - AFTER: Qty=0/" + canisterMax + " (EMPTY), CanisterSynced=true, FurnaceSynced=true");
				SwitchOffServer();
				LoggingUtility.LogDebug("[FreezeFurnace] Propane canister empty - furnace turned off");
			}
			else
			{
				canister.SetQuantity(newQty);
				canister.SetSynchDirty(); // Sync canister to save state
				SetSynchDirty(); // Sync parent furnace container to ensure attached item state persists
				LoggingUtility.LogDebug("[FreezeFurnace] DepletePropaneCanister - AFTER: Qty=" + newQty + "/" + canisterMax + ", CanisterSynced=true, FurnaceSynced=true");
			}
		}
		else
		{
			LoggingUtility.LogDebug("[FreezeFurnace] DepletePropaneCanister - ERROR: Canister not found!");
		}
	}

	bool CanCraftOreType(string oreSlotName)
	{
		// Only check attachment slots (not cargo)
		for (int i = 0; i < 4; i++)
		{
			string slotName = oreSlotName;
			if (i > 0)
			{
				slotName = oreSlotName + i;
			}
			
			int slotId = InventorySlots.GetSlotIdFromString(slotName);
			ItemBase ore = ItemBase.Cast(GetInventory().FindAttachment(slotId));
			
			if (ore && ore.GetQuantity() > 0)
			{
				return true;
			}
		}
		
		return false;
	}
	
	// Legacy methods for backward compatibility
	bool CanCraftBase()    { return CanCraftOreType("Freezestone_base"); }
	bool CanCraftGold()    { return CanCraftOreType("Freezestone_gold"); }
	bool CanCraftSilver()  { return CanCraftOreType("Freezestone_silver"); }
	bool CanCraftTin()     { return CanCraftOreType("Freezestone_tin"); }
	bool CanCraftIron()    { return CanCraftOreType("Freezestone_iron"); }
	bool CanCraftCopper()  { return CanCraftOreType("Freezestone_copper"); }
	bool CanCraftSulphur() { return CanCraftOreType("Freezestone_sulphur"); }
	bool CanCraftUranium() { return CanCraftOreType("Freezestone_uranium"); }

	bool HasWoodenCrate()
	{
		// Static furnaces don't require crates
		FreezeFurnace_Static staticFurnace = FreezeFurnace_Static.Cast(this);
		if (staticFurnace)
		{
			return true; // Static furnace doesn't need crate
		}
		
		// Check for vanilla wooden crate in any of the 4 slots
		// Minimum 1 crate required, but can have up to 4 attached
		array<string> crateSlots = {"Truck_01_WoodenCrate1", "Truck_01_WoodenCrate2", "Truck_01_WoodenCrate3", "Truck_01_WoodenCrate4"};
		
		for (int i = 0; i < crateSlots.Count(); i++)
		{
			int slotId = InventorySlots.GetSlotIdFromString(crateSlots[i]);
			ItemBase crate = ItemBase.Cast(GetInventory().FindAttachment(slotId));
			
			if (crate)
			{
				return true; // Found at least one crate (minimum requirement met)
			}
		}
		
		return false; // No crate found
	}
	
	ItemBase GetAttachedCrate()
	{
		// Check for vanilla wooden crate in any of the 4 slots
		// Returns the first crate found (can have up to 4 attached, but only need 1)
		array<string> crateSlots = {"Truck_01_WoodenCrate1", "Truck_01_WoodenCrate2", "Truck_01_WoodenCrate3", "Truck_01_WoodenCrate4"};
		
		for (int i = 0; i < crateSlots.Count(); i++)
		{
			int slotId = InventorySlots.GetSlotIdFromString(crateSlots[i]);
			ItemBase crate = ItemBase.Cast(GetInventory().FindAttachment(slotId));
			
			if (crate)
			{
				return crate; // Return first crate found (for requirement check)
			}
		}
		
		return null; // No crate found
	}
	
	ItemBase CreateNuggetInCargo(string itemClassName)
	{
		// Server-side only - inventory operations must be server authoritative
		if (!GetGame().IsServer())
			return null;
		
		// Static furnaces use their own cargo, regular furnaces use attached crates
		FreezeFurnace_Static staticFurnace = FreezeFurnace_Static.Cast(this);
		if (staticFurnace)
		{
			// Static furnace: use furnace's own cargo inventory
			GameInventory furnaceInventory = staticFurnace.GetInventory();
			if (furnaceInventory)
			{
				// Try to create nugget in furnace's cargo
				ItemBase FMS_NewItem1 = ItemBase.Cast(furnaceInventory.CreateInInventory(itemClassName));
				
				if (FMS_NewItem1)
				{
					// Successfully created nugget - try to stack it with existing stacks
					for (int FMS_j = 0; FMS_j < furnaceInventory.GetCargo().GetItemCount(); FMS_j++)
					{
						ItemBase FMS_existingItem1 = ItemBase.Cast(furnaceInventory.GetCargo().GetItem(FMS_j));
						
						if (FMS_existingItem1 && FMS_existingItem1 != FMS_NewItem1)
						{
							if (FMS_existingItem1.CanBeCombined(FMS_NewItem1))
							{
								FMS_existingItem1.CombineItems(FMS_NewItem1, false);
								FMS_existingItem1.SetSynchDirty();
								FMS_NewItem1.SetSynchDirty();
								
								if (FMS_NewItem1.GetQuantity() <= 0)
								{
									GetGame().ObjectDelete(FMS_NewItem1);
									FMS_NewItem1 = FMS_existingItem1;
								}
								
								staticFurnace.SetSynchDirty();
								return FMS_NewItem1;
							}
						}
					}
					
					// No existing stack found - return new item as-is
					staticFurnace.SetSynchDirty();
					return FMS_NewItem1;
				}
			}
			
			// Furnace cargo is full
			LoggingUtility.LogDebug("[FreezeFurnace] CreateNuggetInCargo - Static furnace cargo is full, cannot create nuggets");
			return null;
		}
		
		// Regular furnace: try to create nugget in any attached crate (check all 4 slots)
		// If crate 1 is full, try crate 2, then 3, then 4
		array<string> crateSlots = {"Truck_01_WoodenCrate1", "Truck_01_WoodenCrate2", "Truck_01_WoodenCrate3", "Truck_01_WoodenCrate4"};
		
		for (int i = 0; i < crateSlots.Count(); i++)
		{
			int slotId = InventorySlots.GetSlotIdFromString(crateSlots[i]);
			ItemBase crate = ItemBase.Cast(GetInventory().FindAttachment(slotId));
			
			if (!crate)
			{
				continue; // Skip empty slots
			}
			
			// Try to create nugget in this crate's cargo
			ItemBase FMS_NewItem2 = ItemBase.Cast(crate.GetInventory().CreateInInventory(itemClassName));
			
			if (FMS_NewItem2)
			{
				// Successfully created nugget - now try to stack it with existing stacks
				GameInventory inventory = crate.GetInventory();
				if (inventory)
				{
					// Iterate through all items in the crate's inventory (cargo)
					for (int FMS_j2 = 0; FMS_j2 < inventory.GetCargo().GetItemCount(); FMS_j2++)
					{
						ItemBase FMS_existingItem2 = ItemBase.Cast(inventory.GetCargo().GetItem(FMS_j2));
						
						if (FMS_existingItem2 && FMS_existingItem2 != FMS_NewItem2)
						{
							// Check if items can be combined
							if (FMS_existingItem2.CanBeCombined(FMS_NewItem2))
							{
								// Combine the new item into the existing stack
								FMS_existingItem2.CombineItems(FMS_NewItem2, false);
								
								// Sync both items
								FMS_existingItem2.SetSynchDirty();
								FMS_NewItem2.SetSynchDirty();
								
								// If new item was fully consumed, delete it
								if (FMS_NewItem2.GetQuantity() <= 0)
								{
									GetGame().ObjectDelete(FMS_NewItem2);
									FMS_NewItem2 = FMS_existingItem2; // Return the existing stack
								}
								
								// Sync the crate
								crate.SetSynchDirty();
								
								return FMS_NewItem2;
							}
						}
					}
				}
				
				// No existing stack found or couldn't combine - return new item as-is
				// Sync the crate to ensure cargo UI updates
				crate.SetSynchDirty();
				return FMS_NewItem2;
			}
			// If creation failed (crate full), try next crate
		}
		
		// All crates are full or no crates attached
		LoggingUtility.LogDebug("[FreezeFurnace] CreateNuggetInCargo - All crates full or no crate attached, cannot create nuggets");
		return null;
	}

	void ProcessOreType(string oreSlotName, string nuggetClassName)
	{
		// Only process ore from attachment slots (not cargo)
		// Process only 1 ore per cycle (time is per stone)
		for (int i = 0; i < 4; i++)
		{
			string slotName = oreSlotName;
			if (i > 0)
			{
				slotName = oreSlotName + i;
			}
			
			int slotId = InventorySlots.GetSlotIdFromString(slotName);
			ItemBase ore = ItemBase.Cast(GetInventory().FindAttachment(slotId));
			
			if (ore && ore.GetQuantity() > 0)
			{
				// Process only 1 ore per cycle (time is per stone)
				// Example: 10 stones × 5 seconds = 50 seconds total
				ItemBase nugget = CreateNuggetInCargo(nuggetClassName);
				ore.AddQuantity(-1);
				// Don't consolidate here - consolidate at end of ProcessAndCraftBars() to avoid sync issues
				
				return; // Process only one ore per cycle
			}
		}
	}


	void ProcessAndCraftBars()
	{
		if (!GetGame().IsServer())
			return;

		if (!HasPropaneSetup())
		{
			SwitchOffServer();
			LoggingUtility.LogDebug("[FreezeFurnace] Furnace turned off - missing propane setup, canister empty, or no wooden crate attached");
			return;
		}
		
		// Log canister state before depletion
		LogCanisterState("ProcessAndCraftBars-BEFORE");
		
		DepletePropaneCanister();
		
		// Log canister state after depletion
		LogCanisterState("ProcessAndCraftBars-AFTER");
		
		if (CanCraftBase())    { ProcessOreType("Freezestone_base", "FreezeNugget_base"); }
		if (CanCraftGold())    { ProcessOreType("Freezestone_gold", "FreezeNugget_gold"); }
		if (CanCraftSilver())  { ProcessOreType("Freezestone_silver", "FreezeNugget_silver"); }
		if (CanCraftTin())     { ProcessOreType("Freezestone_tin", "FreezeNugget_tin"); }
		if (CanCraftIron())    { ProcessOreType("Freezestone_iron", "FreezeNugget_iron"); }
		if (CanCraftCopper())  { ProcessOreType("Freezestone_copper", "FreezeNugget_copper"); }
		if (CanCraftSulphur()) { ProcessOreType("Freezestone_sulphur", "FreezeRef_Sulphur"); }
		if (CanCraftUranium()) { ProcessOreType("Freezestone_uranium", "FreezeNugget_uranium"); }

		// Check if any ore type can still be crafted
		bool hasOre = CanCraftBase() || CanCraftGold() || CanCraftSilver() || CanCraftTin() || CanCraftIron() || CanCraftCopper() || CanCraftSulphur() || CanCraftUranium();
		
		if (!hasOre)
		{
			SwitchOffServer();
			LoggingUtility.LogDebug("[FreezeFurnace] Furnace turned off - no more ore to process");
		}
		else
		{
			ScheduleNextSmelt();
		}
	}

	void ScheduleNextSmelt()
	{
		if (!GetGame().IsServer())
			return;
			
		FreezeCraftingTimesConfig craftConfig = FreezeCraftingTimesConfig.GetCached();
		if (!craftConfig)
			return;
			
		int fastestSmeltTime = 999;
		array<string> oreTypes = {"Freezestone_base", "Freezestone_gold", "Freezestone_silver", "Freezestone_tin", 
		                          "Freezestone_iron", "Freezestone_copper", "Freezestone_sulphur", "Freezestone_uranium"};
		array<string> configNames = {"SmeltStone", "SmeltGold", "SmeltSilver", "SmeltTin", 
		                             "SmeltIron", "SmeltCopper", "SmeltSulphur", "SmeltUranium"};
		
		for (int i = 0; i < oreTypes.Count(); i++)
		{
			if (CanCraftOreType(oreTypes[i]))
			{
				int time = craftConfig.GetCraftTimeSeconds(configNames[i]);
				if (time < fastestSmeltTime)
				{
					fastestSmeltTime = time;
				}
			}
		}
		
		if (fastestSmeltTime < 999)
		{
			int smeltTimeMs = fastestSmeltTime * 1000;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ProcessAndCraftBars, smeltTimeMs, false);
		}
	}
}

