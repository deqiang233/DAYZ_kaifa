class EnhanceProcessor
{
    static void ProcessEnhanceRequest(PlayerBase player, string itemType, bool useProtection)
    {
        if (!player || itemType == "")
        {
            return;
        }

        EnhanceItem itemConfig = EnhanceConfigManager.FindItem(itemType);
        if (!itemConfig || !itemConfig.LevelConfig)
        {
            SendEnhanceResult(player, false, "", 0, "❌ 该物品无法强化");
            return;
        }

        EnhanceLevel level = itemConfig.LevelConfig;
        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
        if (!itemInHands || itemInHands.GetType() != itemType)
        {
            SendEnhanceResult(player, false, "", 0, "❌ 请手持需要强化的物品");
            return;
        }

        if (!CheckMaterials(player, level.RequiredMaterials))
        {
            string missing = BuildMissingMaterialMessage(player, level.RequiredMaterials);
            SendEnhanceResult(player, false, "", 0, missing);
            return;
        }

        bool canUseProtection = useProtection && level.ProtectionCardItem != "" && level.ProtectionCardQuantity > 0;
        if (canUseProtection)
        {
            int protectionHave = CountItem(player, level.ProtectionCardItem);
            if (protectionHave < level.ProtectionCardQuantity)
            {
                SendEnhanceResult(player, false, "", 0, "❌ 保护石不足");
                return;
            }
        }

        ConsumeMaterials(player, level.RequiredMaterials);

        if (canUseProtection)
        {
            RemoveItem(player, level.ProtectionCardItem, level.ProtectionCardQuantity);
        }

        GetGame().ObjectDelete(itemInHands);

        bool success = Math.RandomFloat01() <= level.SuccessRate;
        string resultItemType = "";
        int resultQuantity = 1;

        if (success && level.SuccessOutput && level.SuccessOutput.Count() > 0)
        {
            resultItemType = level.SuccessOutput[0].ItemType;
            resultQuantity = level.SuccessOutput[0].Quantity;
        }
        else if (!success)
        {
            ref array<ref EnhanceResultItem> fallback;
            if (canUseProtection)
            {
                fallback = level.ProtectionCardOutput;
            }
            else
            {
                fallback = level.FailureOutput;
            }

            if (fallback && fallback.Count() > 0)
            {
                resultItemType = fallback[0].ItemType;
                resultQuantity = fallback[0].Quantity;
            }
        }

        if (resultItemType == "")
        {
            SendEnhanceResult(player, success, "", 0, "⚠️ 强化完成，但未配置结果物品");
            return;
        }

        GiveResult(player, resultItemType, resultQuantity);

        string message;
        if (success)
        {
            message = "🎉 强化成功!";
        }
        else if (canUseProtection)
        {
            message = "🛡️ 保护石生效，物品已保留";
        }
        else
        {
            message = "❌ 强化失败!";
        }

        SendEnhanceResult(player, success, resultItemType, resultQuantity, message);
    }

    static bool CheckMaterials(PlayerBase player, array<ref EnhanceMaterial> materials)
    {
        if (!materials || materials.Count() == 0)
        {
            return true;
        }

        foreach (EnhanceMaterial material : materials)
        {
            if (!material)
            {
                continue;
            }

            int have = CountItem(player, material.MaterialType);
            if (have < material.Quantity)
            {
                return false;
            }
        }

        return true;
    }

    static string BuildMissingMaterialMessage(PlayerBase player, array<ref EnhanceMaterial> materials)
    {
        string result = "❌ 材料不足: ";
        bool first = true;

        foreach (EnhanceMaterial material : materials)
        {
            if (!material)
            {
                continue;
            }

            int have = CountItem(player, material.MaterialType);
            if (have >= material.Quantity)
            {
                continue;
            }

            if (!first)
            {
                result += ", ";
            }

            string displayName;
            if (material.DisplayName != "")
            {
                displayName = material.DisplayName;
            }
            else
            {
                displayName = material.MaterialType;
            }

            result += displayName + "(" + have.ToString() + "/" + material.Quantity.ToString() + ")";
            first = false;
        }

        return result;
    }

    static void ConsumeMaterials(PlayerBase player, array<ref EnhanceMaterial> materials)
    {
        foreach (EnhanceMaterial material : materials)
        {
            if (!material)
            {
                continue;
            }

            RemoveItem(player, material.MaterialType, material.Quantity);
        }
    }

    static int CountItem(PlayerBase player, string typeName)
    {
        if (!player || typeName == "")
        {
            return 0;
        }

        int total = 0;
        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (!item)
            {
                continue;
            }

            if (!item.IsKindOf(typeName))
            {
                continue;
            }

            ItemBase itemBase = ItemBase.Cast(item);
            if (itemBase && itemBase.HasQuantity())
            {
                total += itemBase.GetQuantity();
            }
            else
            {
                total += 1;
            }
        }

        return total;
    }

    static void RemoveItem(PlayerBase player, string typeName, int quantity)
    {
        if (!player || typeName == "" || quantity <= 0)
        {
            return;
        }

        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        int remaining = quantity;
        foreach (EntityAI item : items)
        {
            if (remaining <= 0)
            {
                break;
            }

            if (!item || !item.IsKindOf(typeName))
            {
                continue;
            }

            ItemBase itemBase = ItemBase.Cast(item);
            if (itemBase && itemBase.HasQuantity())
            {
                int qty = itemBase.GetQuantity();
                if (qty > remaining)
                {
                    itemBase.AddQuantity(-remaining);
                    remaining = 0;
                }
                else
                {
                    remaining -= qty;
                    GetGame().ObjectDelete(item);
                }
            }
            else
            {
                GetGame().ObjectDelete(item);
                remaining -= 1;
            }
        }
    }

    static void GiveResult(PlayerBase player, string typeName, int quantity)
    {
        if (!player || typeName == "" || quantity <= 0)
        {
            return;
        }

        for (int i = 0; i < quantity; i++)
        {
            EntityAI toHands = player.GetHumanInventory().CreateInHands(typeName);
            if (toHands)
            {
                continue;
            }

            EntityAI toInventory = player.GetInventory().CreateInInventory(typeName);
            if (toInventory)
            {
                continue;
            }

            vector pos = player.GetPosition();
            GetGame().CreateObject(typeName, pos, false, true, false);
        }
    }

    static void SendEnhanceResult(PlayerBase player, bool success, string itemType, int quantity, string message)
    {
        if (!player || !player.GetIdentity())
        {
            return;
        }

        Param4<bool, string, int, string> payload = new Param4<bool, string, int, string>(success, itemType, quantity, message);
        player.RPCSingleParam(EnhanceRPC.RPC_ENHANCE_RESULT, payload, true, player.GetIdentity());
    }
}

