# CoCo_ZmbStone - 僵尸丢石头功能独立Mod

## 简介
这是一个独立的DayZ mod，实现了僵尸向玩家投掷石头的功能。该mod从PvZmoD_CustomisableZombies中独立出来，可以单独使用。

## 功能特性
- 僵尸可以向玩家投掷石头
- 可配置的伤害值（生命值和冲击值）
- 可配置的投掷距离和频率
- 可配置的流血概率（可全局或按僵尸类型独立设置）
- 支持只在玩家位于障碍物上时投掷
- 防止玩家被石头直接砸死（可设置最低生命值）

## 安装
1. 将 `CoCo_ZmbStone` 文件夹复制到服务器的 `@CoCo_ZmbStone` 目录
2. 在服务器启动参数中添加 `-mod=@CoCo_ZmbStone`

## 配置
编辑 `Scripts/3_Game/CoCo_ZmbStone_3_Game/CoCo_ZmbStone_Config.c` 文件来调整设置：

```c
// 是否启用丢石头功能
static int Enabled = 1; // 0=禁用, 1=启用

// 是否只在玩家在障碍物上时丢石头
static int OnlyIfPlayerOnObstacle = 1; // 0=总是丢, 1=只在障碍物上

// 伤害设置
static float DamageHealth = 2.5; // 生命值伤害
static float DamageShock = 15.0; // 冲击伤害
static float KeepMinimumHealth = 30.0; // 最低生命值
static float BleedChance = 0.2; // 流血概率（0=不流血, 1=必流血）

// 投掷设置
static float ThrowRate = 5.0; // 丢石头间隔（秒）
static float ThrowForce = 90.0; // 投掷力度
static float ThrowDistanceMax = 10.0; // 最大投掷距离
static float ThrowDistanceMin = 2.0; // 最小投掷距离

// 指定僵尸类型的独立流血概率（可选）
// 在 CoCo_ZmbStone_Config.json 中新增 "zombieBleedChances" 区块，例如：
// "zombieBleedChances": {
//     "ZmbM_Mummy": 0.75
// }
// 未配置的僵尸将使用全局 BleedChance
```

## 文件结构
```
CoCo_ZmbStone/
├── config.cpp                    # Mod配置文件
├── README.md                      # 说明文档
└── Scripts/
    ├── 3_Game/
    │   └── CoCo_ZmbStone_3_Game/
    │       └── CoCo_ZmbStone_Config.c    # 配置文件
    └── 4_World/
        └── CoCo_ZmbStone_4_World/
            ├── entities/
            │   ├── CoCo_ThrownStone.c    # 石头类
            │   ├── creatures/
            │   │   └── CoCo_ZombieBase.c # 僵尸基类扩展
            │   └── manbase/
            │       └── CoCo_PlayerBase.c # 玩家基类扩展
            └── managers/
                ├── CoCo_ZombieStoneManager.c    # 丢石头管理器
                └── CoCo_PlayerStoneHandler.c    # 玩家伤害处理器
```

## 工作原理
1. `CoCo_ZombieStoneManager` 定期检查僵尸是否可以投掷石头
2. 当条件满足时，创建 `CoCo_ThrownStone` 对象并应用物理力
3. 石头击中玩家时，`CoCo_PlayerStoneHandler` 处理伤害
4. 所有配置都在 `CoCo_ZmbStone_Config` 中集中管理

## 注意事项
- 需要DayZ服务器环境
- 需要DZ_Data和DZ_Scripts作为依赖
- 修改配置后需要重新编译mod

## 版本
v1.0 - 初始版本

## 作者
CoCo

