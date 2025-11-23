// 文件路径: SpecialClothingFeatures.c
// 功能: 管理不同宝石和特殊服装的功能
// CYX_yinxin_bizhang: 跳高、无限体力、防坠落伤害功能
// CYX_baoshi_v1: 无需吃喝自动恢复
// CYX_baoshi_v2: v1功能 + 缓慢回血
// CYX_baoshi_v3: v2功能 + 缓慢回健康
// CYX_baoshi_v4: v3功能 + 自动攻击10米范围内的僵尸（每0.5秒一次，每次50血）

// 1. 扩展PlayerBase添加通用检测逻辑
modded class PlayerBase extends ManBase
{
    // 特殊服装列表 - 在此添加需要拥有功能的服装类名
    private ref array<string> m_SpecialClothes = {
        "CYX_yinxin_bizhang",  // 已有的外骨骼
        "CYX_baoshi_v1" , //能力宝石v1  
        "CYX_baoshi_v2" , //能力宝石v2
        "CYX_baoshi_v3" , //能力宝石v3
        "CYX_baoshi_v4" , //能力宝石v4
    };

    // 拥有跳高和无限体力功能的服装
    private ref array<string> m_JumpAndStaminaClothes = {
        "CYX_yinxin_bizhang"
    };

    // 拥有免疫下坠伤害功能的服装
    private ref array<string> m_FallDamageImmuneClothes = {
        "CYX_yinxin_bizhang"
    };

    // 检测是否穿戴了坠落伤害免疫功能的服装
    bool IsWearingFallDamageImmuneClothing()
    {
        foreach (string slot : m_CheckSlots)
        {
            ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(slot));
            if (!item) continue;

            foreach (string clothType : m_FallDamageImmuneClothes)
            {
                if (item.IsKindOf(clothType))
                {
                    return true;
                }
            }
        }
        return false;
    }

    // 需要检查的装备槽位
    private ref array<string> m_CheckSlots = {
        "Armband", "Chest", "Legs", "Back", "sample_Pouch"  // 覆盖主要装备槽
    };

    // 检测是否穿戴了任何特殊服装
    bool IsWearingSpecialClothing()
    {
        foreach (string slot : m_CheckSlots)
        {
            ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(slot));
            if (!item) continue;

            foreach (string clothType : m_SpecialClothes)
            {
                if (item.IsKindOf(clothType))
                {
                    return true;
                }
            }
        }
        return false;
    }

    // 检测是否穿戴了跳高和无限体力功能的服装
    bool IsWearingJumpAndStaminaClothing()
    {
        foreach (string slot : m_CheckSlots)
        {
            ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(slot));
            if (!item) continue;

            foreach (string clothType : m_JumpAndStaminaClothes)
            {
                if (item.IsKindOf(clothType))
                {
                    return true;
                }
            }
        }
        return false;
    }

    // 获取当前穿戴的宝石等级（v1-v4），如果没穿返回0
    int GetBaoshiLevel()
    {
        foreach (string slot : m_CheckSlots)
        {
            ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(slot));
            if (!item) continue;

            if (item.IsKindOf("CYX_baoshi_v4"))
                return 4;
            if (item.IsKindOf("CYX_baoshi_v3"))
                return 3;
            if (item.IsKindOf("CYX_baoshi_v2"))
                return 2;
            if (item.IsKindOf("CYX_baoshi_v1"))
                return 1;
        }
        return 0;
    }

    // v4自动攻击僵尸的计时器
    private float m_AutoAttackZombieTimer = 0.0;
    private const float AUTO_ATTACK_INTERVAL = 0.5;  // 每0.5秒攻击一次
    private const float AUTO_ATTACK_RANGE = 10.0;     // 10米范围
    private const float AUTO_ATTACK_DAMAGE = 50.0;    // 每次50血
    
    // 调试打印计时器（每5秒打印一次状态）
    private float m_DebugPrintTimer = 0.0;
    private const float DEBUG_PRINT_INTERVAL = 5.0;  // 每5秒打印一次
    
    // 定时器是否已启动
    private bool m_AutoAttackTimerStarted = false;
    
    // 检查并攻击范围内的僵尸（仅在服务器端执行）
    void CheckAndAttackZombies()
    {
        // 只在服务器端执行
        if (!GetGame().IsServer())
            return;
            
        // 检查是否穿戴了v4宝石
        if (GetBaoshiLevel() != 4)
            return;
            
        // 获取玩家位置
        vector playerPos = GetPosition();
        
        // 获取范围内的所有对象
        array<Object> objects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition(playerPos, AUTO_ATTACK_RANGE, objects, proxyCargos);
        
        int zombieCount = 0;  // 统计检测到的僵尸数量
        int attackedCount = 0;  // 统计攻击的僵尸数量
        
        // 遍历所有对象，找到僵尸并攻击
        for (int i = 0; i < objects.Count(); i++)
        {
            Object obj = objects.Get(i);
            if (!obj)
                continue;
            
            // 检查是否是僵尸
            EntityAI entity = EntityAI.Cast(obj);
            if (!entity)
                continue;
                
            if (!entity.IsZombie())
                continue;
            
            zombieCount++;  // 统计僵尸数量
                
            // 检查是否存活
            if (!entity.IsAlive())
            {
                Print("[v4宝石] 检测到死亡僵尸，跳过");
                continue;
            }
            
            // 检查距离（确保在10米范围内）
            vector zombiePos = entity.GetPosition();
            float distance = vector.Distance(playerPos, zombiePos);
            if (distance > AUTO_ATTACK_RANGE)
            {
                Print(string.Format("[v4宝石] 僵尸距离 %.1f 米，超出攻击范围 %.1f 米", distance, AUTO_ATTACK_RANGE));
                continue;
            }
            
            // 获取僵尸当前生命值（用于打印）
            float currentHealth = entity.GetHealth("", "Health");
            
            // 对僵尸造成伤害（每次50血），使用 EEHitBy 触发受击效果
            ZombieBase zombie = ZombieBase.Cast(entity);
            if (zombie)
            {
                // 计算攻击位置（僵尸的模型空间坐标，使用僵尸躯干位置）
                vector zombieCenter = zombiePos;
                zombieCenter[1] = zombieCenter[1] + 1.0; // 稍微向上偏移到躯干位置
                vector modelPos = zombie.WorldToModel(zombieCenter);
                
                // 创建伤害结果对象
                TotalDamageResult damageResult = new TotalDamageResult();
                
                // 设置伤害值（使用 AddDamage 方法）
                damageResult.AddDamage("Torso", "Health", AUTO_ATTACK_DAMAGE);
                damageResult.AddDamage("", "Health", AUTO_ATTACK_DAMAGE); // 全局伤害
                
                // 调用 EEHitBy 触发受击效果（伤害类型：DT_CLOSE_COMBAT = 1）
                // 参数：damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef
                zombie.EEHitBy(damageResult, 1, this, -1, "Torso", "", modelPos, 1.0);
            }
            else
            {
                // 如果不是 ZombieBase，直接扣血
                entity.AddHealth("", "Health", -AUTO_ATTACK_DAMAGE);
            }
            
            attackedCount++;  // 统计攻击数量
            
            // 打印攻击信息
            Print(string.Format("[v4宝石] 自动攻击僵尸！距离: %.1f 米，伤害: %.0f 血，僵尸生命值: %.0f -> %.0f", 
                distance, AUTO_ATTACK_DAMAGE, currentHealth, entity.GetHealth("", "Health")));
        }
        
        // 如果检测到僵尸但没有攻击，打印信息
        if (zombieCount > 0 && attackedCount == 0)
        {
            Print(string.Format("[v4宝石] 检测到 %d 个僵尸，但未进行攻击（可能已死亡或超出范围）", zombieCount));
        }
    }
    
    // 打印状态信息
    void PrintDebugStatus()
    {
        // 只在服务器端执行
        if (!GetGame().IsServer())
            return;
            
        // 检查是否穿戴了v4宝石
        if (GetBaoshiLevel() != 4)
            return;
            
        // 获取玩家位置
        vector playerPos = GetPosition();
        
        // 获取范围内的所有对象
        array<Object> objects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition(playerPos, AUTO_ATTACK_RANGE, objects, proxyCargos);
        
        int aliveZombieCount = 0;
        int deadZombieCount = 0;
        
        // 统计僵尸数量
        for (int i = 0; i < objects.Count(); i++)
        {
            Object obj = objects.Get(i);
            if (!obj)
                continue;
            
            EntityAI entity = EntityAI.Cast(obj);
            if (!entity || !entity.IsZombie())
                continue;
            
            if (entity.IsAlive())
                aliveZombieCount++;
            else
                deadZombieCount++;
        }
        
        // 打印状态信息
        Print(string.Format("[v4宝石] 状态检查 - 玩家位置: [%.1f, %.1f, %.1f]，10米范围内: 存活僵尸 %d 个，死亡僵尸 %d 个", 
            playerPos[0], playerPos[1], playerPos[2], aliveZombieCount, deadZombieCount));
    }
    
    // 启动自动攻击定时器
    void StartAutoAttackTimer()
    {
        // 只在服务器端执行
        if (!GetGame().IsServer())
            return;
            
        // 如果定时器已启动，不重复启动
        if (m_AutoAttackTimerStarted)
            return;
            
        m_AutoAttackTimerStarted = true;
        
        // 启动攻击检查定时器（每0.5秒执行一次，500毫秒）
        int attackIntervalMs = AUTO_ATTACK_INTERVAL * 1000;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.CheckAndAttackZombies, attackIntervalMs, true);
        
        // 启动调试打印定时器（每5秒执行一次，5000毫秒）
        int debugIntervalMs = DEBUG_PRINT_INTERVAL * 1000;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.PrintDebugStatus, debugIntervalMs, true);
        
        Print("[v4宝石] 自动攻击定时器已启动");
    }
    
    // 重写 EOnPostFrame 方法以启动定时器（如果尚未启动）
    override void EOnPostFrame(IEntity other, int extra)
    {
        super.EOnPostFrame(other, extra);
        
        // 只在服务器端执行，且穿戴了v4宝石时启动定时器
        if (GetGame().IsServer() && GetBaoshiLevel() == 4 && !m_AutoAttackTimerStarted)
        {
            StartAutoAttackTimer();
        }
        // 如果不再穿戴v4宝石，停止定时器（通过不重新启动来实现）
        else if (GetGame().IsServer() && GetBaoshiLevel() != 4 && m_AutoAttackTimerStarted)
        {
            m_AutoAttackTimerStarted = false;
            Print("[v4宝石] 已移除v4宝石，停止自动攻击");
        }
    }

};



// 3. 修改体力系统应用无限体力
modded class StaminaHandler
{
    override protected void StaminaProcessor_Move(HumanMovementState pHumanMovementState)
    {
        // 只有CYX_yinxin_bizhang能获得无限体力功能
        if (m_Player && m_Player.IsWearingJumpAndStaminaClothing())
        {
            switch (pHumanMovementState.m_iMovement)
            {
                case DayZPlayerConstants.MOVEMENTIDX_SPRINT:
                case DayZPlayerConstants.MOVEMENTIDX_RUN:
                case DayZPlayerConstants.MOVEMENTIDX_WALK:
                case DayZPlayerConstants.MOVEMENTIDX_IDLE:
                    m_StaminaDelta = 0;  // 所有移动状态体力无消耗
                    break;
                default:
                    m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC * 100;
                    break;
            }
        }
        else
        {
            super.StaminaProcessor_Move(pHumanMovementState);
        }
    }

    override protected void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
    {
        // 只有CYX_yinxin_bizhang能获得无限体力功能
        if (m_Player && m_Player.IsWearingJumpAndStaminaClothing())
        {
            m_StaminaDelta = 0;  // 攀爬不消耗体力
        }
        else
        {
            super.StaminaProcessor_Ladder(pHumanMovementState);
        }
    }

    override protected void StaminaProcessor_Swimming(HumanMovementState pHumanMovementState)
    {
        // 只有CYX_yinxin_bizhang能获得无限体力功能
        if (m_Player && m_Player.IsWearingJumpAndStaminaClothing())
        {
            m_StaminaDelta = 0;  // 游泳不消耗体力
        }
        else
        {
            super.StaminaProcessor_Swimming(pHumanMovementState);
        }
    }

    override void DepleteStamina(EStaminaModifiers modifier, float dT = -1)
    {
        // 只有CYX_yinxin_bizhang能获得无限体力功能
        if (m_Player && m_Player.IsWearingJumpAndStaminaClothing())
        {
            return;  // 完全禁用体力消耗
        }
        super.DepleteStamina(modifier, dT);
    }
};

// 4. 修改跳跃系统应用高跳功能（仅CYX_yinxin_bizhang）
modded class DayZPlayerImplementJumpClimb
{
    // 检测是否穿戴了跳高和无限体力功能的服装
    bool IsWearingJumpAndStaminaClothing()
    {
        PlayerBase player = PlayerBase.Cast(m_Player);
        return player && player.IsWearingJumpAndStaminaClothing();
    }

    override void JumpOrClimb()
    {
        // 只有CYX_yinxin_bizhang能获得跳高功能
        if (IsWearingJumpAndStaminaClothing())
        {
            m_bWasClimb = false;

            if (m_Player.IsInFullbodyDamageAnimation())
                return;

            // 提高攀爬距离（跳高辅助）
            SHumanCommandClimbSettings hcls = m_Player.GetDayZPlayerType().CommandClimbSettingsW();
            hcls.m_fFwMaxDistance = 3.5;  // 高跳模式攀爬距离

            SHumanCommandClimbResult climbRes = new SHumanCommandClimbResult();
            HumanCommandClimb.DoClimbTest(m_Player, climbRes, 0);

            if (climbRes.m_bIsClimb || climbRes.m_bIsClimbOver)
            {
                int climbType = GetClimbType(climbRes.m_fClimbHeight);
                if (m_Player.CanClimb(climbType, climbRes) && Climb(climbRes))
                    return;
            }

            if (m_Player.CanJump())
                Jump();
        }
        else
        {
            super.JumpOrClimb();
        }
    }

    override private void Jump()
    {
        Print("[CYX_DEBUG] ========== 我跳了! ==========");
        // 只有CYX_yinxin_bizhang能获得跳高功能
        if (IsWearingJumpAndStaminaClothing())
        {
            m_bIsJumpInProgress = true;
            m_Player.SetFallYDiff(m_Player.GetPosition()[1]);
            m_Player.OnJumpStart();
            m_Player.StartCommand_Fall(9.6);  // 高跳高度
            m_Player.StopHandEvent();
        }
        else
        {
            super.Jump();
        }
    }
};

// 5. 添加饱食度和水分缓慢恢复功能（v1及以上）
modded class HungerMdfr: ModifierBase
{
    override void OnTick(PlayerBase player, float deltaT)
    {
        // 穿戴v1及以上宝石能获得饱食度自动恢复功能
        int baoshiLevel = player.GetBaoshiLevel();
        if (baoshiLevel >= 1)
        {
            float energy = player.GetStatEnergy().Get();
            // 只在饱食度未满时恢复，每秒恢复最大饱食度的1%
            if (energy < PlayerConstants.SL_ENERGY_MAX)
            {
                float recoveryRate = PlayerConstants.SL_ENERGY_MAX * 0.01 * deltaT;
                player.GetStatEnergy().Add(recoveryRate);
                
                // 确保不超过最大值
                if (player.GetStatEnergy().Get() > PlayerConstants.SL_ENERGY_MAX)
                {
                    player.GetStatEnergy().Set(PlayerConstants.SL_ENERGY_MAX);
                }
            }
            
            // 移除饥饿状态
            player.UnsetMixedSoundState(eMixedSoundStates.HUNGRY);
        }
        else
        {
            // 调用原版逻辑
            super.OnTick(player, deltaT);
        }
    }
};

modded class ThirstMdfr: ModifierBase
{
    override void OnTick(PlayerBase player, float deltaT)
    {
        // 穿戴v1及以上宝石能获得水分自动恢复功能
        int baoshiLevel = player.GetBaoshiLevel();
        if (baoshiLevel >= 1)
        {
            float water = player.GetStatWater().Get();
            // 只在水分未满时恢复，每秒恢复最大水分的1%
            if (water < PlayerConstants.SL_WATER_MAX)
            {
                float recoveryRate = PlayerConstants.SL_WATER_MAX * 0.01 * deltaT;
                player.GetStatWater().Add(recoveryRate);
                
                // 确保不超过最大值
                if (player.GetStatWater().Get() > PlayerConstants.SL_WATER_MAX)
                {
                    player.GetStatWater().Set(PlayerConstants.SL_WATER_MAX);
                }
            }
            
            // 移除口渴状态
            player.UnsetMixedSoundState(eMixedSoundStates.THIRSTY);
        }
        else
        {
            // 调用原版逻辑
            super.OnTick(player, deltaT);
        }
    }
};

// 6. 添加血液和健康值自动恢复功能
// v2: 缓慢回血
// v3: 缓慢回血 + 缓慢回健康
modded class BloodRegenMdfr
{
    // 血液恢复倍数（直接在代码中设置）
    static const float BLOOD_REGEN_MULTIPLIER = 20.0;
    
    override void OnTick(PlayerBase player, float deltaT)
    {
        int baoshiLevel = player.GetBaoshiLevel();
        
        // v2及以上才有血液恢复功能
        if (baoshiLevel < 2)
        {
            super.OnTick(player, deltaT);
            return;
        }

        if (player.IsBleeding())
            return;

        float regen_modifier_water = GetRegenModifierWater(player.GetStatWater().Get());
        float regen_modifier_energy = GetRegenModifierEnergy(player.GetStatEnergy().Get());
        float blood_regen_speed = PlayerConstants.BLOOD_REGEN_RATE_PER_SEC * regen_modifier_water * regen_modifier_energy;

        // v2及以上：恢复血液值
        if (baoshiLevel >= 2)
        {
            player.AddHealth("", "Blood", blood_regen_speed * deltaT * BLOOD_REGEN_MULTIPLIER);
        }
        
        // v3及以上：同时恢复健康值（整体生命值）- 每秒回复1点
        if (baoshiLevel >= 3)
        {
            player.AddHealth("", "Health", 1.0 * deltaT);
        }
    }
};

// 7. 添加坠落伤害免疫功能
modded class DayZPlayerImplementFallDamage
{
    const string FD_AMMOCYX = "FallDamageCYX";  // 自定义的0伤害弹药类型
    
    // 检测玩家是否穿戴了具有防坠落伤害功能的服装
    bool IsWearingFallDamageImmuneClothing()
    {
        PlayerBase player = PlayerBase.Cast(m_Player);
        if (player && player.IsWearingFallDamageImmuneClothing())
        {
            return true;
        }
        return false;
    }
    
    // 重写坠落伤害处理
    override void HandleFallDamage(FallDamageData pData)
    {
        m_FallDamageData = pData;
        
        // 如果穿戴了防坠落伤害装备
        if (IsWearingFallDamageImmuneClothing())
        {
            if (GetGame().IsServer())
            {
                // 只在高度超过3米时造成极小伤害（高度/50）
                if (GetHeight() >= 3)
                {
                    vector posMS = m_Player.WorldToModel(m_Player.GetPosition());
                    m_Player.ProcessDirectDamage(DT_CUSTOM, m_Player, "", FD_AMMOCYX, posMS, (GetHeight()/50));
                }
            }
        }
        else
        {
            // 没有防护装备，使用原版坠落伤害
            super.HandleFallDamage(pData);
        }
    }
};
