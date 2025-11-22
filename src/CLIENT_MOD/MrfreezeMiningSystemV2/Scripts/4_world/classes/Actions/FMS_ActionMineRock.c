modded class ActionMineRock : ActionMineBase
{
    static ref array<string> validMiningNodes = {
        "FreezeNode_copper",
        "FreezeNode_gold",
        "FreezeNode_iron",
        "FreezeNode_silver",
        "FreezeNode_tin",
        "FreezeNode_stone",
        "FreezeNode_uranium",
        "FreezeNode_sulphur",
        "FreezeNode_AmberGemNode",
        "FreezeNode_AmethystGemNode",
        "FreezeNode_AquamarineGemNode",
        "FreezeNode_FancyColourDiamondGemNode",
        "FreezeNode_IoliteGemNode",
        "FreezeNode_JadeGemNode",
        "FreezeNode_RubyGemNode",
        "FreezeNode_TurquoiseGemNode"
    };

    bool IsValidMiningNode(string nodeType)
    {
        return validMiningNodes.Find(nodeType) > -1;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!item)
            return false;

        if (!(item.IsKindOf("Pickaxe") || item.IsKindOf("SledgeHammer")))
            return false;

        Object targetObject = target.GetObject();
        if (!targetObject)
            return false;

        string currentTargetType = targetObject.GetType();

        return targetObject.IsRock() || IsValidMiningNode(currentTargetType);
    }

    override void OnActionInfoUpdate(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Object targetObject = target.GetObject();
        EntityAI fTargetObject = EntityAI.Cast(targetObject);

        if (targetObject.IsRock())
        {
            m_Text = "#harvest" + " " + GetYieldName(player, target, item);
        }
        else if (fTargetObject)
        {
            string itemType = fTargetObject.GetType();

            if (g_FreezeMiningClientConfig && g_FreezeMiningClientConfig.Contains(itemType))
            {
                m_Text = g_FreezeMiningClientConfig.Get(itemType);
            }
            else
            {
                m_Text = "Mine (Unknown)";
            }
        }
    }
}

modded class CAContinuousMineRock : CAContinuousMineWood
{
    FreezeMiningConfig miningConfig;
    vector lastPosition = vector.Zero;
    float m_MiningSpeedMultiplier = 1.0; // 挖矿速度倍率

    override bool GetMiningData(ActionData action_data)
    {
        if (GetGame().IsServer() && !miningConfig)
        {
            miningConfig = FreezeMiningConfig.Cast(GetPlugin(FreezeMiningConfig));
        }

        // 先调用父类方法初始化基础数据
        bool result = super.GetMiningData(action_data);
        
        if (!result)
        {
            RockBase ntarget;
            if (Class.CastTo(ntarget, action_data.m_Target.GetObject()))
            {
                result = true;
            }
            else
            {
                Building starget;
                if (Class.CastTo(starget, action_data.m_Target.GetObject()))
                {
                    result = true;
                }
            }
        }

        // 获取挖矿速度倍率
        if (result && action_data.m_MainItem)
        {
            m_MiningSpeedMultiplier = GetMiningSpeedMultiplier(action_data.m_MainItem);
        }

        return result;
    }

    float GetMiningSpeedMultiplier(ItemBase tool)
    {
        if (!tool)
            return 1.0;

        string toolType = tool.GetType();
        
        // 根据镐子类型设置速度倍率（每级增加10%速度）
        if (toolType == "CYX_wakuanggao_t1")
        {
            return 1.2; // 110% (基础速度)
        }
        else if (toolType == "CYX_wakuanggao_t2")
        {
            return 1.4; // 120%
        }
        else if (toolType == "CYX_wakuanggao_t3")
        {
            return 1.6; // 130%
        }
        else if (toolType == "CYX_wakuanggao_t4")
        {
            return 1.8; // 140%
        }
        else if (toolType == "CYX_wakuanggao_t5")
        {
            return 2.0; // 150%
        }
        else if (toolType == "CYX_wakuanggao_t6")
        {
            return 2.2; // 160%
        }
        else if (toolType == "CYX_wakuanggao_t7")
        {
            return 2.4; // 170%
        }
        else if (toolType == "CYX_wakuanggao_t8")
        {
            return 2.6; // 180%
        }
        else if (toolType == "CYX_wakuanggao_t9")
        {
            return 2.8; // 190%
        }
        else if (toolType == "CYX_wakuanggao_t10")
        {
            return 4.0; // 190%
        }
        
        return 1.0; // 默认基础速度
    }

    override int Execute(ActionData action_data)
    {
        vector currentPosition = action_data.m_Player.GetPosition();

        if (lastPosition != vector.Zero && vector.Distance(currentPosition, lastPosition) > 0.02)
        {
            LoggingUtility.LogDebug("[Freeze_Mining] Player moved or jumped, canceling the mining action.");
            StopMiningAction(action_data);
            return UA_FINISHED;
        }
        lastPosition = currentPosition;

        if (!action_data.m_Player || !m_DataLoaded)
        {
            LoggingUtility.LogDebug("[Freeze_Mining] Error: Player or mining data not loaded.");
            StopMiningAction(action_data);
            return UA_ERROR;
        }

        Object targetObject = action_data.m_Target.GetObject();

        if (GetGame().IsServer())
        {
            if (targetObject && targetObject.IsDamageDestroyed())
            {
                LoggingUtility.LogDebug("[Freeze_Mining] Target object is destroyed, stopping mining.");
                StopMiningAction(action_data);
                return UA_FINISHED;
            }

            if (action_data.m_MainItem && action_data.m_MainItem.IsDamageDestroyed())
            {
                LoggingUtility.LogDebug("[Freeze_Mining] Tool is destroyed, stopping mining.");
                StopMiningAction(action_data);
                return UA_FINISHED;
            }
        }

        if (m_TimeElpased < m_AdjustedTimeBetweenMaterialDrops)
        {
            // 根据镐子类型调整时间累加速度（速度倍率越高，时间累加越快）
            m_TimeElpased += action_data.m_Player.GetDeltaT() * m_MiningSpeedMultiplier;
            return UA_PROCESSING;
        }

        m_TimeElpased = 0;

        OnCompleteProgress(action_data);
        return UA_PROCESSING;
    }

    void StopMiningAction(ActionData action_data)
    {
        if (action_data && action_data.m_Player)
        {
            ActionManagerClient actionManager = ActionManagerClient.Cast(action_data.m_Player.GetActionManager());
            if (actionManager)
            {
                actionManager.Interrupt();
                LoggingUtility.LogDebug("[Freeze_Mining] Stopped mining animation/action for player: " + action_data.m_Player.GetIdentity().GetName());
            }
        }
    }

    void OnCompleteProgress(ActionData action_data)
    {
        if (GetGame().IsServer() && action_data.m_Player && action_data.m_MainItem)
        {
            if (!miningConfig)
            {
                miningConfig = FreezeMiningConfig.Cast(GetPlugin(FreezeMiningConfig));
            }

            PlayerBase player = action_data.m_Player;
            ItemBase tool = action_data.m_MainItem;
            Object targetObject = action_data.m_Target.GetObject();

            if (targetObject)
            {
                string targetType = targetObject.GetType();
                int maxMine = miningConfig.GetMaxMineForNode(targetType);
                int damagePerHit = 1000 / maxMine;

                targetObject.DecreaseHealth("", "", damagePerHit);
                LoggingUtility.LogDebug("[Freeze_Mining] Node health decreased by " + damagePerHit + ". Remaining health: " + targetObject.GetHealth("", ""));

                if (targetObject.GetHealth("", "") <= 0)
                {
                    LoggingUtility.LogDebug("[Freeze_Mining] Node destroyed: " + targetType);
                    GetGame().ObjectDelete(targetObject);
                }

                string minedItem = "";
                ref FreezeMinableItemConfig config = miningConfig.getItemConfig(targetType);
                if (config)
                {
                    minedItem = GetItemBasedOnProbability(config.getProbabilities());
                }
                else
                {
                    minedItem = GetItemBasedOnProbability(miningConfig.getProbabilities());
                }

                if (minedItem != "")
                {
                    ItemBase minedItemInstance = ItemBase.Cast(GetGame().CreateObjectEx(minedItem, player.GetPosition(), ECE_PLACE_ON_SURFACE));
                    minedItemInstance.SetQuantity(1);
                    LoggingUtility.LogDebug("[Freeze_Mining] Mined item: " + minedItem + " created.");
                }

                if (tool && tool.GetHealth() > 0)
                {
                    float toolDamagePerUse = 10.0;
                    tool.DecreaseHealth("", "", toolDamagePerUse);
                    LoggingUtility.LogDebug("[Freeze_Mining] Tool health decreased by " + toolDamagePerUse + ". New health: " + tool.GetHealth());
                }
            }
        }
    }

    string GetItemBasedOnProbability(array<ref FreezeItemProbability> itemProbabilities)
    {
        int total = 0;
        FreezeItemProbability prob;

        for (int idx = 0; idx < itemProbabilities.Count(); idx++)
        {
            prob = itemProbabilities.Get(idx);
            total += prob.probability;
        }

        int randomnumber = Math.RandomInt(0, total);

        for (int idx2 = 0; idx2 < itemProbabilities.Count(); idx2++)
        {
            prob = itemProbabilities.Get(idx2);
            if (randomnumber < prob.probability)
            {
                return prob.item;
            }
            randomnumber -= prob.probability;
        }

        return "Stone";
    }

    string GetItemBasedOnProbability(map<string, int> itemProbabilities)
    {
        int total = 0;

        for (int i = 0; i < itemProbabilities.Count(); i++)
        {
            total += itemProbabilities.GetElement(i);
        }

        int randomnumber = Math.RandomInt(0, total);

        for (int j = 0; j < itemProbabilities.Count(); j++)
        {
            randomnumber -= itemProbabilities.GetElement(j);
            if (randomnumber < 0)
            {
                return itemProbabilities.GetKey(j);
            }
        }

        return "Stone";
    }
}
