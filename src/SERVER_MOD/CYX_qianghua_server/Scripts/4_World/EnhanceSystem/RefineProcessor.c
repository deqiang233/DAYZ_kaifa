// 洗练处理逻辑
// 处理武器洗练请求

class RefineProcessor
{
    static void ProcessRefineRequest(PlayerBase player, string itemType)
    {
        if (!player || itemType == "")
        {
            return;
        }

        // 检查是否是武器
        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
        if (!itemInHands || itemInHands.GetType() != itemType)
        {
            SendRefineResult(player, false, "❌ 请手持需要洗练的武器");
            return;
        }

        Weapon_Base weapon = Weapon_Base.Cast(itemInHands);
        if (!weapon)
        {
            SendRefineResult(player, false, "❌ 只有武器可以进行洗练");
            return;
        }

        // 获取洗练配置 - 先通过 itemType 找到 ItemSetting，再获取配置
        EnhanceConfigManager.LoadConfig();
        EnhanceItem item = EnhanceConfigManager.FindItem(itemType);
        if (!item)
        {
            SendRefineResult(player, false, "❌ 该武器未配置强化系统");
            return;
        }
        
        ItemSettingConfig refineConfig = EnhanceConfigManager.GetSetting(item.ItemSetting);
        if (!refineConfig || !refineConfig.CanRefine)
        {
            SendRefineResult(player, false, "❌ 该武器无法洗练");
            return;
        }

        // 检查材料
        if (!CheckMaterials(player, refineConfig.RefineRequiredMaterials))
        {
            string missing = BuildMissingMaterialMessage(player, refineConfig.RefineRequiredMaterials);
            SendRefineResult(player, false, missing);
            return;
        }

        // 消耗材料
        ConsumeMaterials(player, refineConfig.RefineRequiredMaterials);

        // 生成随机倍率（0.6-1.3）
        float minMultiplier = refineConfig.RefineDamageMultiplierMin;
        float maxMultiplier = refineConfig.RefineDamageMultiplierMax;
        if (minMultiplier <= 0.0)
        {
            minMultiplier = 0.6;
        }
        if (maxMultiplier <= 0.0)
        {
            maxMultiplier = 1.3;
        }

        float newMultiplier = Math.RandomFloat(minMultiplier, maxMultiplier);
        
        // 设置洗练倍率
        weapon.SetRefineDamageMultiplier(newMultiplier);

        // 保存洗练数据到玩家文件
        PlayerRefineDataManager.SaveRefinedWeapon(player, itemType, newMultiplier);

        // 发送结果
        int percent = Math.Round(newMultiplier * 100);
        string message = "🎉 洗练成功! 伤害倍率: " + percent.ToString() + "%";
        SendRefineResult(player, true, message, newMultiplier);
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

    static void SendRefineResult(PlayerBase player, bool success, string message, float multiplier = 1.0)
    {
        if (!player || !player.GetIdentity())
        {
            return;
        }

        Param3<bool, string, float> payload = new Param3<bool, string, float>(success, message, multiplier);
        player.RPCSingleParam(EnhanceRPC.RPC_REFINE_RESULT, payload, true, player.GetIdentity());
    }
}

