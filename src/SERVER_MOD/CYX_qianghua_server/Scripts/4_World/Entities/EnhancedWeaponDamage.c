// 强化武器伤害系统
// 让强化后的武器可以应用 FixedDamageBonus 固定伤害加成
// 服务端版本

// 防抖机制：防止短时间内重复处理伤害
const int DEBOUNCE_ARRAY_SIZE = 64;  // 防抖数组大小
const int DEBOUNCE_TIME_MS = 50;     // 防抖时间（毫秒）- 设置为50ms，既能防止同一发子弹重复处理，又不会影响全自动射击（AK射速约100ms/发）

// 防抖记录结构
class DamageDebounceRecord
{
    int entityID;
    int lastProcessTime;
}

// 延迟检查记录结构
class DelayedDamageCheck
{
    EntityAI target;
    float healthBeforeSuper;
    TotalDamageResult damageResult;
    float savedDamageValue;  // 保存的伤害值（在damageResult失效时使用）
    int damageType;
    EntityAI source;
    int component;
    string dmgZone;
    string ammo;
    vector modelPos;
    float speedCoef;
}

// 静态防抖数组
static ref array<ref DamageDebounceRecord> g_DamageDebounceArray = new array<ref DamageDebounceRecord>;

// 检查是否在防抖时间内
bool IsInDebounceTime(EntityAI entity)
{
    if (!entity)
    {
        return false;
    }
    
    int currentTime = GetGame().GetTime();
    int entityID = entity.GetID();
    
    // 查找该实体的记录
    for (int i = 0; i < g_DamageDebounceArray.Count(); i++)
    {
        DamageDebounceRecord record = g_DamageDebounceArray.Get(i);
        if (record && record.entityID == entityID)
        {
            // 检查是否在防抖时间内
            int timeDiff = currentTime - record.lastProcessTime;
            if (timeDiff < DEBOUNCE_TIME_MS)
            {
                Print("[CYX_ENHANCE] 防抖: 实体 " + entityID.ToString() + " 在 " + timeDiff.ToString() + "ms 前刚处理过，跳过");
                return true;
            }
            else
            {
                // 更新时间为当前时间
                record.lastProcessTime = currentTime;
                return false;
            }
        }
    }
    
    // 如果没有找到记录，创建新记录
    DamageDebounceRecord newRecord = new DamageDebounceRecord;
    newRecord.entityID = entityID;
    newRecord.lastProcessTime = currentTime;
    
    // 如果数组已满，清理最旧的记录
    if (g_DamageDebounceArray.Count() >= DEBOUNCE_ARRAY_SIZE)
    {
        // 移除最旧的记录（第一个）
        g_DamageDebounceArray.Remove(0);
    }
    
    g_DamageDebounceArray.Insert(newRecord);
    return false;
}

// 延迟检查伤害（用于处理血量更新延迟的情况）
void DelayedDamageCheckCallback(DelayedDamageCheck checkData)
{
    if (!checkData || !checkData.target)
    {
        return;
    }
    
    EntityAI target = checkData.target;
    float healthBeforeSuper = checkData.healthBeforeSuper;
    
    // 检查目标是否还活着
    if (!target)
    {
        return;
    }
    
    float healthAfterSuper = target.GetHealth("", "Health");
    
    // 详细打印 healthBefore 和 healthAfter 的值（延迟检查）
    Print("========================================");
    Print("[CYX_ENHANCE] [延迟检查-最后备用] 血量差值计算详情:");
    Print("[CYX_ENHANCE] [延迟检查-最后备用] healthBeforeSuper (调用super.EEHitBy之前): " + healthBeforeSuper.ToString());
    Print("[CYX_ENHANCE] [延迟检查-最后备用] healthAfterSuper (延迟50ms后检查): " + healthAfterSuper.ToString());
    Print("[CYX_ENHANCE] [延迟检查-最后备用] 血量差值 (healthBefore - healthAfter): " + (healthBeforeSuper - healthAfterSuper).ToString());
    Print("========================================");
    
    if (healthAfterSuper <= 0.0)
    {
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 目标在应用原始伤害后已死亡，跳过额外伤害");
        return;
    }
    
    // 优先使用保存的伤害值（在调用super.EEHitBy之前保存的，最可靠）
    float actualDamage = 0.0;
    if (checkData.savedDamageValue > 0.0)
    {
        actualDamage = checkData.savedDamageValue;
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 使用保存的伤害值: " + actualDamage.ToString());
    }
    // 如果保存的伤害值无效，尝试从 damageResult 获取
    else if (checkData.damageResult)
    {
        // 尝试多种方式获取伤害值
        float damageFromZone = checkData.damageResult.GetDamage(checkData.dmgZone, "Health");
        float damageFromGlobal = checkData.damageResult.GetDamage("", "Health");
        float highestDamage = checkData.damageResult.GetHighestDamage("Health");
        
        Print("[CYX_ENHANCE] [延迟检查-最后备用] GetDamage() 方法获取的伤害值:");
        Print("  - GetDamage(区域: " + checkData.dmgZone + ", Health): " + damageFromZone.ToString());
        Print("  - GetDamage(全局, Health): " + damageFromGlobal.ToString());
        Print("  - GetHighestDamage(Health): " + highestDamage.ToString());
        
        // 优先使用全局伤害值（因为全局伤害值更准确，特别是对于触发多次伤害的情况）
        if (damageFromGlobal > 0.0)
        {
            actualDamage = damageFromGlobal;
            Print("[CYX_ENHANCE] [延迟检查-最后备用] 使用全局伤害值: " + actualDamage.ToString());
        }
        else if (damageFromZone > 0.0)
        {
            actualDamage = damageFromZone;
            Print("[CYX_ENHANCE] [延迟检查-最后备用] 全局伤害为0，使用指定区域的伤害值: " + actualDamage.ToString());
        }
        else if (highestDamage > 0.0)
        {
            actualDamage = highestDamage;
            Print("[CYX_ENHANCE] [延迟检查-最后备用] 使用最高伤害值: " + actualDamage.ToString());
        }
    }
    
    // 如果 GetDamage() 获取失败，使用血量差值作为备用方案
    float healthDiffDamage = healthBeforeSuper - healthAfterSuper;
    if (actualDamage <= 0.0 && healthDiffDamage > 0.0)
    {
        actualDamage = healthDiffDamage;
        Print("[CYX_ENHANCE] [延迟检查-最后备用] GetDamage() 获取失败，使用血量差值作为备用: " + actualDamage.ToString());
    }
    else if (actualDamage > 0.0 && healthDiffDamage > 0.0)
    {
        // 如果两种方法都成功，进行对比验证
        float diff = Math.AbsFloat(actualDamage - healthDiffDamage);
        float diffPercent = (diff / Math.Max(actualDamage, healthDiffDamage)) * 100.0;
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 伤害值对比: GetDamage()=" + actualDamage.ToString() + " vs 血量差值=" + healthDiffDamage.ToString() + " (差异: " + diffPercent.ToString() + "%)");
        
        // 如果差异超过20%，使用血量差值（更准确）
        if (diffPercent > 20.0)
        {
            Print("[CYX_ENHANCE] [延迟检查-最后备用] 警告: 两种方法差异较大，使用血量差值（更准确）");
            actualDamage = healthDiffDamage;
        }
    }
    
    // 验证伤害值是否有效
    if (actualDamage <= 0.0)
    {
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 错误: 无法获取有效伤害值，跳过强化武器伤害");
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 保存的伤害值=" + checkData.savedDamageValue.ToString() + ", 血量差值=" + healthDiffDamage.ToString());
        string damageStr = "null";
        if (checkData.damageResult)
        {
            damageStr = checkData.damageResult.GetDamage(checkData.dmgZone, "Health").ToString();
        }
        Print("[CYX_ENHANCE] [延迟检查-最后备用] GetDamage()=" + damageStr);
        return;
    }
    
    // 防抖检查：防止短时间内重复处理伤害
    if (IsInDebounceTime(target))
    {
        Print("[CYX_ENHANCE] [延迟检查-最后备用] 防抖: 目标在防抖时间内，跳过强化武器伤害");
        return;
    }
    
    // 应用强化武器伤害
    Print("[CYX_ENHANCE] [延迟检查-最后备用] 开始应用强化武器伤害，使用伤害值: " + actualDamage.ToString());
    ApplyEnhancedWeaponDamage(target, actualDamage, checkData.damageType, checkData.source, checkData.component, checkData.dmgZone, checkData.ammo, checkData.modelPos, checkData.speedCoef);
}

// 查找武器类型对应的强化等级配置
EnhanceLevel FindWeaponEnhanceLevel(string weaponType)
{
    // 查找武器自身的配置
    EnhanceItem item = EnhanceConfigManager.FindItem(weaponType);
    if (item && item.LevelConfig)
    {
        EnhanceLevel level = item.LevelConfig;
        // 检查是否有伤害配置（固定伤害加成或基础伤害不为默认值）
        if (level.FixedDamageBonus != 0.0 || level.WeaponDamage > 0.0)
        {
            return level;
        }
    }
    
    return null;
}

// 通用的强化武器伤害处理函数
// actualDamage: super.EEHitBy() 调用前后血量的实际差值（实际造成的伤害）
void ApplyEnhancedWeaponDamage(EntityAI target, float actualDamage, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
{
    if (!GetGame().IsServer())
    {
        return;
    }
    
    // 只处理 Health 伤害类型（避免对其他伤害类型如 Blood、Shock 等重复应用）
    if (damageType != 0 && damageType != 1)
    {
        return;
    }
    
    // 检查 target 是否为空
    if (!target)
    {
        return;
    }
    
    // 检查是否是武器
    Weapon_Base weapon = Weapon_Base.Cast(source);
    if (!weapon)
    {
        return;
    }
    
    string weaponType = weapon.GetType();
    
    Print("[CYX_ENHANCE] 检测到武器攻击: " + weaponType);
    
    // 查找该武器类型对应的强化等级配置
    EnhanceLevel levelConfig = FindWeaponEnhanceLevel(weaponType);
    if (!levelConfig)
    {
        Print("[CYX_ENHANCE] 未找到武器强化配置: " + weaponType);
        return;
    }
    
    Print("[CYX_ENHANCE] 找到武器强化配置 - WeaponDamage: " + levelConfig.WeaponDamage.ToString() + " | FixedDamageBonus: " + levelConfig.FixedDamageBonus.ToString());
    
    // 如果配置了FixedDamageBonus，必须配置WeaponDamage才能计算减伤比例
    if (levelConfig.FixedDamageBonus != 0.0 && levelConfig.WeaponDamage <= 0.0)
    {
        // 如果只配置了FixedDamageBonus但没有WeaponDamage，无法计算减伤比例，跳过
        Print("[CYX_ENHANCE] 警告: 配置了FixedDamageBonus但没有WeaponDamage，无法计算减伤比例");
        return;
    }
    
    // 如果没有配置固定伤害加成，不修改伤害
    if (levelConfig.FixedDamageBonus == 0.0)
    {
        Print("[CYX_ENHANCE] FixedDamageBonus为0，跳过伤害加成");
        return;
    }
    
    // 使用实际造成的伤害值（从血量差值计算得出）
    float actualHealthDamage = actualDamage;
    
    // 如果实际伤害为0或负数，说明没有造成伤害，跳过
    if (actualHealthDamage <= 0.0)
    {
        Print("[CYX_ENHANCE] 警告: 实际伤害为0或负数 (actualHealthDamage = " + actualHealthDamage.ToString() + ")，跳过伤害加成");
        return;
    }
    
    // 如果伤害值异常小（小于0.1），可能是计算错误，跳过伤害加成
    if (actualHealthDamage < 0.1)
    {
        Print("[CYX_ENHANCE] 警告: 伤害值过小 (" + actualHealthDamage.ToString() + " < 0.1)，跳过伤害加成");
        return;
    }
    
    // 计算减伤系数：实际伤害 / 基础伤害（WeaponDamage）
    // 例如：WeaponDamage = 100（子弹基础伤害），实际伤害 = 45，减伤系数 = 45/100 = 0.45
    // 例如：WeaponDamage = 100，实际伤害 = 55（打腿部），减伤系数 = 55/100 = 0.55
    // 例如：WeaponDamage = 100，实际伤害 = 20（打甲上），减伤系数 = 20/100 = 0.2
    float damageReductionRatio = actualHealthDamage / levelConfig.WeaponDamage;
    
    // 限制减伤系数在合理范围内（0.01 到 1.0）
    // 如果实际伤害大于基础伤害，说明可能有其他加成，使用1.0
    if (damageReductionRatio > 1.0)
    {
        damageReductionRatio = 1.0;
    }
    else if (damageReductionRatio < 0.01)
    {
        damageReductionRatio = 0.01;  // 最小减伤系数，避免完全无伤害
    }
    
    // 固定伤害加成根据减伤系数缩放
    // 例如：FixedDamageBonus = 400，减伤系数 = 0.45，则额外伤害 = 400 * 0.45 = 180
    float additionalDamage = levelConfig.FixedDamageBonus * damageReductionRatio;
    
    // 获取目标当前血量（应用前）
    float healthBeforeApply = 0.0;
    if (target)
    {
        healthBeforeApply = target.GetHealth("", "Health");
    }
    
    // 详细调试日志 - 打印所有伤害信息
    Print("========================================");
    Print("[CYX_ENHANCE] 强化武器伤害计算详情:");
    Print("武器类型: " + weaponType);
    Print("WeaponDamage (基础伤害): " + levelConfig.WeaponDamage.ToString());
    Print("ActualDamage (实际伤害，从血量差值计算): " + actualHealthDamage.ToString());
    Print("ReductionRatio (减伤比例): " + damageReductionRatio.ToString());
    Print("FixedBonus (固定加成): " + levelConfig.FixedDamageBonus.ToString());
    Print("AdditionalDamage (额外伤害): " + additionalDamage.ToString());
    Print("目标血量 (应用前): " + healthBeforeApply.ToString());
    Print("目标类型: " + target.GetType());
    Print("伤害区域: " + dmgZone);
    Print("========================================");
    
    // 如果没有额外伤害，直接返回
    if (additionalDamage <= 0.0)
    {
        Print("[CYX_ENHANCE] 警告: 额外伤害为0或负数，跳过应用");
        return;
    }
    
    // 应用额外的伤害差值
    // 再次检查目标是否还活着（应用伤害前）
    if (target)
    {
        if (healthBeforeApply <= 0.0)
        {
            Print("[CYX_ENHANCE] 警告: 目标已死亡，跳过应用额外伤害");
            return;
        }
        
        // 直接应用额外伤害（确保是负数，造成伤害）
        target.AddHealth("", "Health", -additionalDamage);
        
        // 获取应用后的血量
        float healthAfterApply = target.GetHealth("", "Health");
        Print("[CYX_ENHANCE] 目标血量 (应用后): " + healthAfterApply.ToString());
        Print("[CYX_ENHANCE] 实际扣除血量: " + (healthBeforeApply - healthAfterApply).ToString());
    }
}

// 玩家支持
modded class PlayerBase
{
    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        // 只处理 Health 伤害类型
        if (damageType != 0 && damageType != 1)
        {
            super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
            return;
        }
        
        // 优先通过血量差值计算实际伤害（这是最准确的方法，反映真实造成的伤害）
        // damageResult.GetDamage() 返回的是理论伤害，可能包含加成但未考虑护甲、部位减伤等
        float actualDamage = 0.0;
        float healthAfterSuper = 0.0;
        
        // 在调用 super.EEHitBy() 之前保存初始血量
        float healthBeforeSuper = 0.0;
        if (this)
        {
            healthBeforeSuper = this.GetHealth("", "Health");
            if (healthBeforeSuper <= 0.0)
            {
                super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
                return;
            }
        }
        
        // 先调用父类方法应用原始伤害
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        
        // 检查玩家是否还活着（super.EEHitBy之后）
        if (!this)
        {
            return;
        }
        
        healthAfterSuper = this.GetHealth("", "Health");
        if (healthAfterSuper <= 0.0)
        {
            return;
        }
        
        // 计算实际造成的伤害（血量差值）- 这是最准确的实际伤害值
        actualDamage = healthBeforeSuper - healthAfterSuper;
        
        // 如果血量差值计算失败，尝试从 damageResult 获取（作为备用方案）
        if (actualDamage <= 0.0 && damageResult)
        {
            float theoreticalDamage = damageResult.GetDamage(dmgZone, "Health");
            if (theoreticalDamage > 0.0)
            {
                actualDamage = theoreticalDamage;
            }
        }
        
        // 验证伤害值是否有效
        if (actualDamage <= 0.0)
        {
            return;
        }
        
        // 防抖检查：防止短时间内重复处理伤害
        if (IsInDebounceTime(this))
        {
            return;
        }
        
        // 应用强化武器伤害
        ApplyEnhancedWeaponDamage(this, actualDamage, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}

// 打印 EEHitBy 的所有参数信息（用于调试）
void PrintEEHitByParameters(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
{
    Print("========================================");
    Print("[CYX_ENHANCE] ====== EEHitBy 所有参数信息 ======");
    Print("========================================");
    
    // 1. TotalDamageResult damageResult
    Print("[CYX_ENHANCE] 1. TotalDamageResult damageResult:");
    if (damageResult)
    {
        // 尝试获取不同部位的伤害值
        Print("   - damageResult 不为空");
        
        // 尝试获取 Health 伤害（使用传入的 dmgZone）
        float damageHealth = damageResult.GetDamage(dmgZone, "Health");
        Print("   - GetDamage(\"" + dmgZone + "\", \"Health\"): " + damageHealth.ToString());
        
        // 尝试获取其他常见部位的伤害
        array<string> commonZones = {"Head", "Torso", "Arms", "Legs", "Body"};
        for (int i = 0; i < commonZones.Count(); i++)
        {
            string zone = commonZones.Get(i);
            if (zone != dmgZone)
            {
                float dmg = damageResult.GetDamage(zone, "Health");
                if (dmg > 0.0)
                {
                    Print("   - GetDamage(\"" + zone + "\", \"Health\"): " + dmg.ToString());
                }
            }
        }
        
        // 尝试获取其他伤害类型（Blood, Shock等）
        array<string> damageTypes = {"Blood", "Shock"};
        for (int j = 0; j < damageTypes.Count(); j++)
        {
            string dmgType = damageTypes.Get(j);
            float dmgValue = damageResult.GetDamage(dmgZone, dmgType);
            if (dmgValue > 0.0)
            {
                Print("   - GetDamage(\"" + dmgZone + "\", \"" + dmgType + "\"): " + dmgValue.ToString());
            }
        }
    }
    else
    {
        Print("   - damageResult 为空");
    }
    
    // 2. int damageType
    Print("[CYX_ENHANCE] 2. int damageType: " + damageType.ToString());
    Print("   - 0 = DT_UNKNOWN, 1 = DT_CLOSE_COMBAT, 2 = DT_FIREARM, 3 = DT_EXPLOSIVE, 4 = DT_FALL, 5 = DT_BLEEDING, 6 = DT_STUN, 7 = DT_SHOCK, 8 = DT_DROWNING, 9 = DT_ELECTRIC, 10 = DT_ENERGY, 11 = DT_MELEE, 12 = DT_OTHER");
    
    // 3. EntityAI source
    Print("[CYX_ENHANCE] 3. EntityAI source:");
    if (source)
    {
        Print("   - source 不为空");
        Print("   - GetType(): " + source.GetType());
        Print("   - GetID(): " + source.GetID().ToString());
        
        // 如果是武器，尝试获取武器信息
        if (source.IsInherited(Weapon_Base))
        {
            Weapon_Base weapon = Weapon_Base.Cast(source);
            if (weapon)
            {
                Print("   - 是武器: " + weapon.GetType());
            }
        }
    }
    else
    {
        Print("   - source 为空");
    }
    
    // 4. int component
    Print("[CYX_ENHANCE] 4. int component: " + component.ToString());
    
    // 5. string dmgZone
    Print("[CYX_ENHANCE] 5. string dmgZone: \"" + dmgZone + "\"");
    
    // 6. string ammo
    Print("[CYX_ENHANCE] 6. string ammo: \"" + ammo + "\"");
    
    // 7. vector modelPos
    Print("[CYX_ENHANCE] 7. vector modelPos: " + modelPos.ToString());
    Print("   - X: " + modelPos[0].ToString() + ", Y: " + modelPos[1].ToString() + ", Z: " + modelPos[2].ToString());
    
    // 8. float speedCoef
    Print("[CYX_ENHANCE] 8. float speedCoef: " + speedCoef.ToString());
    
    Print("========================================");
}

// 僵尸支持
modded class ZombieBase
{
    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        // 打印所有参数信息
        PrintEEHitByParameters(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        
        string sourceType = "null";
        if (source)
        {
            sourceType = source.GetType();
        }
        Print("[CYX_ENHANCE] ZombieBase.EEHitBy 被调用 - 伤害类型: " + damageType.ToString() + " | 来源: " + sourceType);
        
        // 只处理 Health 伤害类型
        if (damageType != 0 && damageType != 1)
        {
            Print("[CYX_ENHANCE] 非Health伤害类型，跳过");
            super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
            return;
        }
        
        // 在调用 super.EEHitBy() 之前保存初始血量和伤害值
        float healthBeforeSuper = 0.0;
        float savedDamageValue = 0.0;
        if (this)
        {
            healthBeforeSuper = this.GetHealth("", "Health");
            Print("[CYX_ENHANCE] 僵尸初始血量: " + healthBeforeSuper.ToString());
            
            if (healthBeforeSuper <= 0.0)
            {
                Print("[CYX_ENHANCE] 僵尸已死亡，跳过");
                super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
                return;
            }
        }
        
        // 在调用super.EEHitBy之前保存伤害值（此时damageResult是有效的）
        if (damageResult)
        {
            // 优先使用全局伤害值（因为全局伤害值更准确，特别是对于触发多次伤害的情况）
            savedDamageValue = damageResult.GetDamage("", "Health");
            if (savedDamageValue <= 0.0)
            {
                // 如果全局伤害为0，尝试指定区域的伤害值
                savedDamageValue = damageResult.GetDamage(dmgZone, "Health");
            }
            if (savedDamageValue <= 0.0)
            {
                // 如果区域伤害也为0，尝试最高伤害值
                savedDamageValue = damageResult.GetHighestDamage("Health");
            }
            Print("[CYX_ENHANCE] 保存的伤害值: " + savedDamageValue.ToString());
        }
        
        // 先调用父类方法应用原始伤害
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        
        // 根据官方脚本的做法，在 super.EEHitBy 之后，damageResult 仍然有效
        // 优先从 damageResult 获取伤害值（官方脚本的做法）
        float actualDamage = 0.0;
        if (damageResult)
        {
            // 尝试从 damageResult 获取伤害值（官方脚本的做法）
            float damageFromZone = damageResult.GetDamage(dmgZone, "Health");
            float damageFromGlobal = damageResult.GetDamage("", "Health");
            float highestDamage = damageResult.GetHighestDamage("Health");
            
            Print("[CYX_ENHANCE] [super.EEHitBy后] 从 damageResult 获取伤害值:");
            Print("  - GetDamage(区域: " + dmgZone + ", Health): " + damageFromZone.ToString());
            Print("  - GetDamage(全局, Health): " + damageFromGlobal.ToString());
            Print("  - GetHighestDamage(Health): " + highestDamage.ToString());
            
            // 优先使用全局伤害值（因为全局伤害值更准确，特别是对于触发多次伤害的情况）
            if (damageFromGlobal > 0.0)
            {
                actualDamage = damageFromGlobal;
                Print("[CYX_ENHANCE] [super.EEHitBy后] 使用全局伤害值: " + actualDamage.ToString());
            }
            else if (damageFromZone > 0.0)
            {
                actualDamage = damageFromZone;
                Print("[CYX_ENHANCE] [super.EEHitBy后] 全局伤害为0，使用指定区域的伤害值: " + actualDamage.ToString());
            }
            else if (highestDamage > 0.0)
            {
                actualDamage = highestDamage;
                Print("[CYX_ENHANCE] [super.EEHitBy后] 使用最高伤害值: " + actualDamage.ToString());
            }
        }
        
        // 如果 damageResult 获取失败，尝试使用保存的伤害值
        if (actualDamage <= 0.0 && savedDamageValue > 0.0)
        {
            actualDamage = savedDamageValue;
            Print("[CYX_ENHANCE] [super.EEHitBy后] damageResult 获取失败，使用保存的伤害值: " + actualDamage.ToString());
        }
        
        // 如果仍然失败，尝试通过血量差值计算（作为最后备用方案）
        float healthAfterSuper = 0.0;
        if (actualDamage <= 0.0 && this)
        {
            healthAfterSuper = this.GetHealth("", "Health");
            float healthDiff = healthBeforeSuper - healthAfterSuper;
            Print("[CYX_ENHANCE] [super.EEHitBy后] 血量差值: " + healthBeforeSuper.ToString() + " - " + healthAfterSuper.ToString() + " = " + healthDiff.ToString());
            
            if (healthDiff > 0.0)
            {
                actualDamage = healthDiff;
                Print("[CYX_ENHANCE] [super.EEHitBy后] 使用血量差值作为伤害值: " + actualDamage.ToString());
            }
        }
        
        // 如果仍然没有获取到血量，获取当前血量用于后续判断
        if (healthAfterSuper <= 0.0 && this)
        {
            healthAfterSuper = this.GetHealth("", "Health");
        }
        
        // 如果成功获取到伤害值，直接应用伤害
        if (actualDamage > 0.0)
        {
            if (this && healthAfterSuper > 0.0)
            {
                // 防抖检查
                if (!IsInDebounceTime(this))
                {
                    Print("[CYX_ENHANCE] [super.EEHitBy后] 开始应用强化武器伤害，使用伤害值: " + actualDamage.ToString());
                    ApplyEnhancedWeaponDamage(this, actualDamage, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
                }
                else
                {
                    Print("[CYX_ENHANCE] [super.EEHitBy后] 防抖: 目标在防抖时间内，跳过强化武器伤害");
                }
            }
            return;
        }
        
        // 如果所有方法都失败，使用延迟检查作为最后备用方案
        Print("[CYX_ENHANCE] [super.EEHitBy后] 所有方法都无法获取伤害值，使用延迟检查作为最后备用（延迟50ms）");
        
        // 创建延迟检查数据
        DelayedDamageCheck checkData = new DelayedDamageCheck;
        checkData.target = this;
        checkData.healthBeforeSuper = healthBeforeSuper;
        checkData.damageResult = damageResult;
        checkData.savedDamageValue = savedDamageValue;  // 保存的伤害值
        checkData.damageType = damageType;
        checkData.source = source;
        checkData.component = component;
        checkData.dmgZone = dmgZone;
        checkData.ammo = ammo;
        checkData.modelPos = modelPos;
        checkData.speedCoef = speedCoef;
        
        // 延迟50ms后检查血量（确保血量已更新，但尽量缩短延迟）
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedDamageCheckCallback, 50, false, checkData);
    }
}

// 动物支持
modded class AnimalBase
{
    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        // 只处理 Health 伤害类型
        if (damageType != 0 && damageType != 1)
        {
            super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
            return;
        }
        
        // 优先通过血量差值计算实际伤害（这是最准确的方法，反映真实造成的伤害）
        // damageResult.GetDamage() 返回的是理论伤害，可能包含加成但未考虑护甲、部位减伤等
        float actualDamage = 0.0;
        float healthAfterSuper = 0.0;
        
        // 在调用 super.EEHitBy() 之前保存初始血量
        float healthBeforeSuper = 0.0;
        if (this)
        {
            healthBeforeSuper = this.GetHealth("", "Health");
            if (healthBeforeSuper <= 0.0)
            {
                super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
                return;
            }
        }
        
        // 先调用父类方法应用原始伤害
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        
        // 检查动物是否还活着（super.EEHitBy之后）
        if (!this)
        {
            return;
        }
        
        healthAfterSuper = this.GetHealth("", "Health");
        if (healthAfterSuper <= 0.0)
        {
            return;
        }
        
        // 计算实际造成的伤害（血量差值）- 这是最准确的实际伤害值
        actualDamage = healthBeforeSuper - healthAfterSuper;
        
        // 如果血量差值计算失败，尝试从 damageResult 获取（作为备用方案）
        if (actualDamage <= 0.0 && damageResult)
        {
            float theoreticalDamage = damageResult.GetDamage(dmgZone, "Health");
            if (theoreticalDamage > 0.0)
            {
                actualDamage = theoreticalDamage;
            }
        }
        
        // 验证伤害值是否有效
        if (actualDamage <= 0.0)
        {
            return;
        }
        
        // 防抖检查：防止短时间内重复处理伤害
        if (IsInDebounceTime(this))
        {
            return;
        }
        
        // 应用强化武器伤害
        ApplyEnhancedWeaponDamage(this, actualDamage, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}

