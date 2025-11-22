// 武器洗练数据扩展
// 为武器添加洗练倍率存储功能

modded class Weapon_Base
{
    private float m_RefineDamageMultiplier;
    private bool m_HasRefineData;

    void Weapon_Base()
    {
        m_RefineDamageMultiplier = 1.0;  // 默认倍率为1.0（无洗练）
        m_HasRefineData = false;
    }

    // 获取洗练倍率
    float GetRefineDamageMultiplier()
    {
        return m_RefineDamageMultiplier;
    }

    // 设置洗练倍率
    void SetRefineDamageMultiplier(float multiplier)
    {
        m_RefineDamageMultiplier = multiplier;
        m_HasRefineData = true;
        SetSynchDirty();
    }

    // 检查是否有洗练数据
    bool HasRefineData()
    {
        return m_HasRefineData;
    }

    // 保存洗练数据
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_RefineDamageMultiplier);
        ctx.Write(m_HasRefineData);
    }

    // 加载洗练数据
    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
        {
            return false;
        }

        // 先初始化默认值
        m_RefineDamageMultiplier = 1.0;
        m_HasRefineData = false;

        // 尝试读取数据（如果存在）
        // 使用临时变量来避免在读取失败时污染成员变量
        float tempMultiplier;
        bool tempHasData;
        
        if (ctx.Read(tempMultiplier))
        {
            m_RefineDamageMultiplier = tempMultiplier;
            
            // 尝试读取 HasRefineData（可能不存在于旧版本）
            if (ctx.Read(tempHasData))
            {
                m_HasRefineData = tempHasData;
            }
            else
            {
                // 兼容旧版本：如果没有HasRefineData，根据倍率判断
                m_HasRefineData = (m_RefineDamageMultiplier != 1.0);
            }
        }
        // 如果读取失败（旧版本武器没有这些数据），使用默认值（已经在上面初始化）

        // 尝试从玩家数据中恢复洗练数据（如果武器没有保存的洗练数据）
        if (!m_HasRefineData)
        {
            RestoreRefineDataFromPlayer();
        }

        return true;
    }

    // 从玩家数据中恢复洗练数据
    void RestoreRefineDataFromPlayer()
    {
        if (!GetGame().IsServer())
        {
            return;
        }

        // 获取武器的所有者（玩家）
        PlayerBase owner = null;
        EntityAI parent = null;
        
        // 方法1: 从库存位置获取所有者
        InventoryLocation inventoryLocation = new InventoryLocation();
        if (GetInventory().GetCurrentInventoryLocation(inventoryLocation))
        {
            parent = inventoryLocation.GetParent();
            if (parent)
            {
                owner = PlayerBase.Cast(parent);
            }
        }

        // 方法2: 如果方法1失败，尝试从层级父级获取
        if (!owner)
        {
            parent = GetHierarchyParent();
            while (parent)
            {
                owner = PlayerBase.Cast(parent);
                if (owner)
                {
                    break;
                }
                parent = parent.GetHierarchyParent();
            }
        }

        if (!owner)
        {
            return;
        }

        // 从玩家数据中恢复洗练数据
        PlayerRefineDataManager.RestoreWeaponRefineData(owner, this);
    }
}

