// ========================================
// CYX 复活装备恢复系统 - 服务端版本
// 功能：玩家死亡后重生自动恢复装备
// 包括：装备转移、断线续传
// ========================================

// 尸体转移状态
class CorpseTransferInfo {
    EntityAI corpse;
    float timestamp;  // 保存时间戳，避免过期
    
    void CorpseTransferInfo(EntityAI corpseRef) {
        corpse = corpseRef;
        timestamp = GetGame().GetTime();
    }
}

modded class PlayerBase extends ManBase {
    // 静态变量：保存所有玩家的尸体引用和转移状态
    static ref map<string, ref CorpseTransferInfo> s_RespawnCorpses;
    
    protected bool m_IsTransferringEquipment;  // 标记是否正在转移装备
    
    void PlayerBase() {
        m_IsTransferringEquipment = false;
        
        // 只在服务端初始化
        if (GetGame().IsServer()) {
            // 初始化静态变量
            if (!s_RespawnCorpses) {
                s_RespawnCorpses = new map<string, ref CorpseTransferInfo>();
            }
        }
    }
    
    override void OnSelectPlayer() {
        super.OnSelectPlayer();
        
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        
        Print("[CYX_RespawnEquipment] OnSelectPlayer 被调用");
        
        // 检查是否有待转移的装备
        if (GetIdentity()) {
            string playerId = GetIdentity().GetId();
            if (s_RespawnCorpses.Contains(playerId)) {
                CorpseTransferInfo transferInfo = s_RespawnCorpses.Get(playerId);
                // 检查尸体是否仍然有效（1小时内）
                float timeDiff = GetGame().GetTime() - transferInfo.timestamp;
                if (timeDiff < 3600000) { // 1小时 = 3600秒 * 1000毫秒
                    Print("[CYX_RespawnEquipment] 检测到待转移的装备，准备恢复...");
                    // 缩短倒计时到5秒（玩家重新登录）
                    RespawnShowCountdownMessage(5);
                } else {
                    Print("[CYX_RespawnEquipment] 尸体引用已过期，清理...");
                    s_RespawnCorpses.Remove(playerId);
                }
            } else {
                Print("[CYX_RespawnEquipment] 无待转移装备");
            }
        }
    }
    
    // 显示倒计时消息
    void RespawnShowCountdownMessage(int seconds) {
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        
        // 检查玩家是否还在线
        if (!IsAlive() || !GetIdentity()) {
            Print("[CYX_RespawnEquipment] 玩家已下线或死亡，停止倒计时");
            return;
        }
        
        if (seconds > 0) {
            MessageImportant("正在恢复装备中，请等待 " + seconds + " 秒...");
            Print("[CYX_RespawnEquipment] 倒计时: " + seconds + " 秒");
            // 每秒递减一次
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RespawnShowCountdownMessage, 1000, false, seconds - 1);
        } else {
            // 倒计时结束，开始转移装备
            MessageImportant("开始恢复装备...");
            Print("[CYX_RespawnEquipment] 倒计时结束，开始转移装备");
            m_IsTransferringEquipment = true;
            RespawnTransferClothingFromCorpse();
        }
    }
    
    // 玩家死亡时保存尸体引用
    override void EEKilled(Object killer) {
        // 只在服务端执行
        if (GetGame().IsServer()) {
            if (GetIdentity()) {
                string playerId = GetIdentity().GetId();
                vector deathPos = GetPosition();
                Print("[CYX_RespawnEquipment] 玩家 " + playerId + " 在位置 " + deathPos.ToString() + " 死亡");
                
                // 延迟保存尸体引用，确保尸体已创建
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RespawnSaveCorpseReferenceAtPosition, 500, false, playerId, deathPos);
            }
        }
        
        super.EEKilled(killer);
    }
    
    
    // 在指定位置保存尸体引用
    void RespawnSaveCorpseReferenceAtPosition(string playerId, vector deathPos) {
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        
        Print("[CYX_RespawnEquipment] 正在查找玩家 " + playerId + " 在位置 " + deathPos.ToString() + " 的尸体...");
        
        // 查找该位置附近的所有尸体
        array<Object> nearbyObjects = new array<Object>();
        GetGame().GetObjectsAtPosition(deathPos, 10, nearbyObjects, null);
        
        Print("[CYX_RespawnEquipment] 找到 " + nearbyObjects.Count() + " 个附近对象");
        
        for (int i = 0; i < nearbyObjects.Count(); i++) {
            PlayerBase corpse = PlayerBase.Cast(nearbyObjects.Get(i));
            if (corpse && !corpse.IsAlive()) {
                vector corpsePos = corpse.GetPosition();
                float distance = vector.Distance(corpsePos, deathPos);
                Print("[CYX_RespawnEquipment] 发现尸体在位置 " + corpsePos.ToString() + "，距离: " + distance);
                
                // 找到最近的尸体（5米内）
                if (distance < 5) {
                    CorpseTransferInfo transferInfo = new CorpseTransferInfo(corpse);
                    s_RespawnCorpses.Set(playerId, transferInfo);
                    Print("[CYX_RespawnEquipment] ✓ 已保存玩家 " + playerId + " 的尸体引用，时间戳: " + transferInfo.timestamp);
                    return;
                }
            }
        }
        
        Print("[CYX_RespawnEquipment] ✗ 未找到玩家 " + playerId + " 的尸体");
    }
    
    // 从尸体转移装备到新玩家
    void RespawnTransferClothingFromCorpse() {
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        if (!IsAlive()) return;
        if (!GetIdentity()) return;
        
        string playerId = GetIdentity().GetId();
        Print("[CYX_RespawnEquipment] 准备从尸体转移装备，玩家ID: " + playerId);
        
        // 获取该玩家的尸体
        if (!s_RespawnCorpses.Contains(playerId)) {
            Print("[CYX_RespawnEquipment] 没有找到玩家 " + playerId + " 的尸体");
            return;
        }
        
        CorpseTransferInfo transferInfo = s_RespawnCorpses.Get(playerId);
        if (!transferInfo || !transferInfo.corpse) {
            Print("[CYX_RespawnEquipment] 尸体引用无效");
            s_RespawnCorpses.Remove(playerId);
            return;
        }
        
        EntityAI corpse = transferInfo.corpse;
        
        Print("[CYX_RespawnEquipment] 开始转移装备...");
        
        // 要转移的装备插槽
        array<string> clothingSlots = {
            "Body", "Legs", "Feet", "Back", "Vest", 
            "Headgear", "Mask", "Eyewear", "Gloves", 
            "Armband", "Shoulder", "Melee",
            "sample_Pouch","Murasama_sheath","head","Hips"
        };
        
        // 第一步：删除新玩家身上的默认装备
        Print("[CYX_RespawnEquipment] 清空新玩家身上的默认装备...");
        string slotName;
        for (int j = 0; j < clothingSlots.Count(); j++) {
            slotName = clothingSlots.Get(j);
            EntityAI existingItem = FindAttachmentBySlotName(slotName);
            if (existingItem) {
                Print("[CYX_RespawnEquipment] 删除默认装备: " + slotName + " = " + existingItem.GetType());
                GetGame().ObjectDelete(existingItem);
            }
        }
        
        // 第二步：开始逐个转移装备（使用延迟队列）
        Print("[CYX_RespawnEquipment] 开始逐个转移装备...");
        RespawnTransferItemByIndex(corpse, clothingSlots, 0);
    }
    
    // 逐个转移装备（递归方式，每件装备间隔200ms）
    void RespawnTransferItemByIndex(EntityAI corpse, array<string> clothingSlots, int index) {
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        
        // 检查玩家是否还在线
        if (!IsAlive() || !GetIdentity()) {
            Print("[CYX_RespawnEquipment] 玩家已下线或死亡，停止转移装备");
            m_IsTransferringEquipment = false;
            return;
        }
        
        if (!corpse || index >= clothingSlots.Count()) {
            // 所有装备转移完成
            Print("[CYX_RespawnEquipment] 所有装备转移完成！");
            
            // 强制同步玩家状态
            SetSynchDirty();
            
            // 显示提示消息
            MessageImportant("CYX服务器：装备已恢复");
            
            // 清理尸体引用
            if (GetIdentity()) {
                string playerId = GetIdentity().GetId();
                s_RespawnCorpses.Remove(playerId);
            }
            
            // 标记转移完成
            m_IsTransferringEquipment = false;
            
            // 删除空尸体
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RespawnDeleteEmptyCorpse, 2000, false, corpse);
            return;
        }
        
        string slotName = clothingSlots.Get(index);
        EntityAI item = corpse.FindAttachmentBySlotName(slotName);
        
        if (item) {
            // 装备到新玩家身上
            int slotId = InventorySlots.GetSlotIdFromString(slotName);
            
            // 先删除远程对象树（准备重新创建）
            GetGame().RemoteObjectTreeDelete(item);
            
            if (LocalTakeEntityAsAttachmentEx(item, slotId)) {
                // 重新创建远程对象树（同步到客户端）
                GetGame().RemoteObjectTreeCreate(item);
                Print("[CYX_RespawnEquipment] ✓ 转移装备[" + index + "]: " + slotName + " = " + item.GetType());
            } else {
                // 如果失败，恢复远程对象树
                GetGame().RemoteObjectTreeCreate(item);
                Print("[CYX_RespawnEquipment] ✗ 转移装备失败[" + index + "]: " + slotName);
            }
        }
        
        // 延迟200ms后转移下一件装备
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RespawnTransferItemByIndex, 200, false, corpse, clothingSlots, index + 1);
    }
    
    // 删除空尸体
    void RespawnDeleteEmptyCorpse(EntityAI corpse) {
        // 只在服务端执行
        if (!GetGame().IsServer()) return;
        
        if (corpse) {
            Print("[CYX_RespawnEquipment] 删除空尸体");
            GetGame().ObjectDelete(corpse);
        }
    }
}

