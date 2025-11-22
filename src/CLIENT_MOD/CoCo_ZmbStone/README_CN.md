# CoCo_ZmbStone - 僵尸丢石头功能独立Mod

## 简介
这是一个独立的DayZ mod，实现了僵尸向玩家投掷石头的功能。该mod从PvZmoD_CustomisableZombies中独立出来，可以单独使用。

## 功能特性
- ✅ 僵尸可以向玩家投掷石头
- ✅ 可配置的伤害值（生命值和冲击值）
- ✅ **支持为不同僵尸类型独立设置伤害值**（新功能）
- ✅ 可配置的投掷距离和频率
- ✅ 支持只在玩家位于障碍物上时投掷
- ✅ 防止玩家被石头直接砸死（可设置最低生命值）
- ✅ 自动检测玩家是否在车内（不会向车内玩家投掷）
- ✅ 射线检测确保投掷路径无障碍

## 安装
1. 将 `CoCo_ZmbStone` 文件夹复制到服务器的mod目录（例如 `@CoCo_ZmbStone`）
2. 在服务器启动参数中添加 `-mod=@CoCo_ZmbStone`
3. 确保服务器和客户端都安装了该mod

## 配置

**重要：** 配置现在通过 `$profile:\CoCo_ZmbStone\CoCo_ZmbStone_Config.json` 文件进行管理，无需修改代码！

配置文件会在首次运行时自动创建在服务器的profiles目录下。修改配置后重启服务器即可生效，无需重新编译mod。

### 配置文件位置
- **服务器端：** `服务器profiles目录\CoCo_ZmbStone\CoCo_ZmbStone_Config.json`
- **示例路径：** `C:\dayz_serve\hutong1\profiles\CoCo_ZmbStone\CoCo_ZmbStone_Config.json`

### 配置文件格式

```json
{
	"enabled": 1,
	"onlyIfPlayerOnObstacle": 1,
	"defaultZombieCanThrow": 1,
	"damage": {
		"health": 2.5,
		"shock": 15.0,
		"keepMinimumHealth": 30.0
	},
	"throwRate": 5.0,
	"throwForce": 90.0,
	"throwDistanceMax": 10.0,
	"throwDistanceMin": 2.0,
	"zombieDamageConfigs": {
		"ZmbM_SoldierNormal_Base": {
			"health": 5.0,
			"shock": 25.0,
			"keepMinimumHealth": 30.0
		},
		"ZmbM_Jacket_Base": {
			"health": 3.5,
			"shock": 20.0,
			"keepMinimumHealth": 30.0
		}
	}
}
```

### 配置项说明

#### 基本设置
- **enabled** (int): 是否启用丢石头功能，`0`=禁用，`1`=启用
- **onlyIfPlayerOnObstacle** (int): 是否只在玩家在障碍物上时丢石头，`0`=总是丢，`1`=只在障碍物上
- **defaultZombieCanThrow** (int): 默认僵尸是否可以丢石头，`0`=禁用，`1`=启用但只在障碍物上，`2`=总是启用

#### 默认伤害设置
- **damage.health** (float): 默认生命值伤害
- **damage.shock** (float): 默认冲击伤害
- **damage.keepMinimumHealth** (float): 默认最低生命值（防止被石头砸死）

#### 投掷设置
- **throwRate** (float): 丢石头间隔（秒）
- **throwForce** (float): 投掷力度（影响距离，不影响伤害）
- **throwDistanceMax** (float): 最大投掷距离（米）
- **throwDistanceMin** (float): 最小投掷距离（米）

#### 独立伤害配置（按僵尸类型）
**zombieDamageConfigs** 对象允许为不同的僵尸类型设置不同的伤害值：

- **键名**：僵尸类型名称（例如 `"ZmbM_SoldierNormal_Base"`）
- **值**：包含以下字段的对象：
  - **health** (float): 该僵尸类型的生命值伤害
  - **shock** (float): 该僵尸类型的冲击伤害
  - **keepMinimumHealth** (float): 该僵尸类型的最低生命值

**示例：**
```json
"zombieDamageConfigs": {
	"ZmbM_SoldierNormal_Base": {
		"health": 5.0,
		"shock": 25.0,
		"keepMinimumHealth": 30.0
	},
	"ZmbM_Jacket_Base": {
		"health": 3.5,
		"shock": 20.0,
		"keepMinimumHealth": 30.0
	}
}
```

**说明：**
- 如果某个僵尸类型在 `zombieDamageConfigs` 中未定义，将使用 `damage` 中的默认配置值
- 僵尸类型名称可以通过游戏日志查看，或使用 `GetType()` 方法获取
- 修改配置后需要重启服务器才能生效

## 文件结构
```
CoCo_ZmbStone/
├── config.cpp                    # Mod配置文件
├── mod.cpp                       # Mod补丁文件
├── README.md                     # 英文说明文档
├── README_CN.md                  # 中文说明文档
├── data/
│   └── CoCo_ZmbStone_Config.json # JSON配置文件模板（实际配置文件在profiles目录）
└── Scripts/
    ├── 3_Game/
    │   └── CoCo_ZmbStone_3_Game/
    │       └── CoCo_ZmbStone_Config.c    # 主配置文件
    └── 4_World/
        └── CoCo_ZmbStone_4_World/
            ├── entities/
            │   ├── CoCo_ThrownStone.c     # 石头类
            │   ├── creatures/
            │   │   └── CoCo_ZombieBase.c # 僵尸基类扩展
            │   └── manbase/
            │       └── CoCo_PlayerBase.c  # 玩家基类扩展
            └── managers/
                ├── CoCo_ZombieStoneManager.c    # 丢石头管理器
                └── CoCo_PlayerStoneHandler.c     # 玩家伤害处理器
```

## 工作原理

### 1. 初始化
- 游戏启动时自动从 `$profile:\CoCo_ZmbStone\CoCo_ZmbStone_Config.json` 加载配置
- 如果配置文件不存在，会自动创建默认配置文件
- 每个僵尸在初始化时会创建 `CoCo_ZombieStoneManager`
- 管理器会定期检查是否可以投掷石头

### 2. 投掷检测
`CoCo_ZombieStoneManager.CheckThrowStone()` 会检查以下条件：
- 僵尸是否存活且非爬行状态
- 功能是否启用
- 僵尸是否有目标
- 目标距离是否在范围内（2-10米）
- 目标是否在车内（不会投掷）
- 僵尸是否面向目标
- 投掷路径是否无障碍（射线检测）
- 是否满足障碍物条件（如果启用）

### 3. 投掷执行
- 创建 `CoCo_ThrownStone` 对象
- 计算投掷方向（朝向目标）
- 应用物理力使石头飞向目标
- 播放攻击动画

### 4. 伤害处理
- 当石头击中玩家时，`CoCo_PlayerStoneHandler` 处理伤害
- 从石头对象读取伤害值（每个石头在生成时根据僵尸类型从JSON配置读取）
- 如果该僵尸类型在JSON配置中未定义独立伤害，则使用默认配置值
- 应用生命值和冲击伤害
- 确保玩家生命值不低于设定值

## 技术细节

### 类说明
- **CoCo_ThrownStone**: 继承自 `Stone`，标记为僵尸投掷的石头，存储独立伤害值，5秒后自动删除
- **CoCo_ZombieStoneManager**: 管理僵尸的投掷逻辑，包括检测、创建和投掷石头，在生成石头时根据僵尸类型设置伤害值
- **CoCo_PlayerStoneHandler**: 处理玩家被石头击中的伤害逻辑，从石头对象读取伤害值
- **CoCo_ZombieBase**: 扩展僵尸基类，添加投掷管理器
- **CoCo_PlayerBase**: 扩展玩家基类，添加伤害处理器
- **CoCo_ZmbStone_Config**: 配置类，负责从profiles目录加载JSON配置，包含 `GetDamageForZombie()` 方法用于根据僵尸类型从JSON配置返回伤害值
- **CoCo_ZmbStone_ConfigData**: JSON配置数据类，存储所有配置项
- **CoCo_ZombieDamageConfig**: 僵尸伤害配置类，存储单个僵尸类型的伤害值

### 投掷算法
1. 计算目标位置（玩家位置 + 高度偏移）
2. 计算投掷方向向量
3. 应用基础投掷力
4. 添加向上的力（4%的基础力）形成抛物线
5. 使用 `ThrowPhysically()` 应用物理力

### 碰撞检测
- 使用 `EOnContact` 检测玩家与石头的碰撞
- 通过 `coco_IsThrowStone` 标记识别僵尸投掷的石头
- 只在玩家被标记为目标时处理伤害

## 注意事项
- ⚠️ 需要DayZ服务器环境
- ⚠️ 需要 `DZ_Data` 和 `DZ_Scripts` 作为依赖
- ⚠️ 配置文件位于服务器的profiles目录，修改后需要重启服务器才能生效
- ⚠️ 确保服务器和客户端版本一致
- ⚠️ 与其他修改僵尸行为的mod可能有冲突
- ✅ **无需重新编译mod**：所有配置都通过JSON文件管理

## 兼容性
- ✅ 独立运行，不依赖PvZmoD_CustomisableZombies
- ✅ 可以与其他mod一起使用
- ⚠️ 如果同时使用PvZmoD_CustomisableZombies，可能会有功能重复

## 版本历史
- **v1.2** (2024) - 配置文件迁移到profiles目录，支持通过JSON文件动态配置，无需重新编译mod
- **v1.1** (2024) - 添加独立伤害配置功能，支持为不同僵尸类型设置不同伤害值
- **v1.0** (2024) - 初始版本，从PvZmoD_CustomisableZombies独立出来

## 作者
CoCo

## 许可证
根据原mod的许可证

