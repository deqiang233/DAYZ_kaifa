class LootScript
{
    static BSHCLootPool GetWeightedRandomLootPool(array<ref BSHCLootPool> pools)
    {
        if (!pools || pools.Count() == 0)
        {
            return null;
        }

        float totalWeight = 0;
        for (int i = 0; i < pools.Count(); i++)
        {
            if (pools[i] && pools[i].probability > 0) 
            {
                totalWeight += pools[i].probability; 
            }
        }

        if (totalWeight <= 0) 
        {
             BSHC_Log.GetInstance().Warning("GetWeightedRandomLootPool: No pools with positive probability found. Returning null or first valid pool if any.");
            if (pools.Count() > 0) return pools.GetRandomElement(); 
            return null;
        }

        float randomValue = Math.RandomFloat(0, totalWeight);
        float currentWeight = 0;

        for (int j = 0; j < pools.Count(); j++)
        {
            if (pools[j] && pools[j].probability > 0) 
            {
                currentWeight += pools[j].probability; 
                if (randomValue <= currentWeight)
                {
                    return pools[j];
                }
            }
        }
        
        BSHC_Log.GetInstance().Warning("GetWeightedRandomLootPool: Fallback, returning random element. This shouldn't happen if totalWeight > 0.");
        return pools.GetRandomElement();
    }
    static array<ref BSHCSpawnDefinition> GetWeightedRandomItemDefinitions(array<ref BSHCSpawnDefinition> itemDefs, int countToSelect)
    {
        array<ref BSHCSpawnDefinition> selectedItems = new array<ref BSHCSpawnDefinition>;
        if (!itemDefs || itemDefs.Count() == 0 || countToSelect <= 0)
        {
            return selectedItems;
        }

        array<ref BSHCSpawnDefinition> drawPool = new array<ref BSHCSpawnDefinition>;
        for (int i = 0; i < itemDefs.Count(); i++)
        {
            drawPool.Insert(itemDefs[i]);
        }

        if (countToSelect > drawPool.Count())
        {
            countToSelect = drawPool.Count();
        }

        for (int j = 0; j < countToSelect; j++)
        {
            float totalWeight = 0;
            for (int k = 0; k < drawPool.Count(); k++)
            {
                if (drawPool[k] && drawPool[k].probability > 0)
                {
                    totalWeight += drawPool[k].probability;
                }
            }

            if (totalWeight <= 0)
            {
                BSHC_Log.GetInstance().Warning("GetWeightedRandomItemDefinitions: No items with positive probability left in the draw pool. Stopping selection.");
                break;
            }
            
            float randomValue = Math.RandomFloat(0, totalWeight);
            float cumulativeWeight = 0;
            BSHCSpawnDefinition itemToSelect = null;
            int selectedIndex = -1;

            for (int l = 0; l < drawPool.Count(); l++)
            {
                BSHCSpawnDefinition currentDef = drawPool[l];
                if (currentDef && currentDef.probability > 0)
                {
                    cumulativeWeight += currentDef.probability;
                    if (randomValue <= cumulativeWeight)
                    {
                        itemToSelect = currentDef;
                        selectedIndex = l;
                        break; 
                    }
                }
            }

            if (itemToSelect && selectedIndex != -1)
            {
                selectedItems.Insert(itemToSelect);
                drawPool.Remove(selectedIndex);
            }
            else if (drawPool.Count() > 0)
            {
                int randomIndex = Math.RandomInt(0, drawPool.Count());
                selectedItems.Insert(drawPool[randomIndex]);
                drawPool.Remove(randomIndex);
            }
        }

        return selectedItems;
    }
}

class WeightedItemCandidate
{
    ref BSHCSpawnDefinition m_ItemDef;
    float m_Score;

    void WeightedItemCandidate(BSHCSpawnDefinition itemDef, float score)
    {
        m_ItemDef = itemDef;
        m_Score = score;
    }

    int Compare(WeightedItemCandidate other)
    {
        if (this.m_Score > other.m_Score) return -1;
        if (this.m_Score < other.m_Score) return 1;
        return 0;
    }
}