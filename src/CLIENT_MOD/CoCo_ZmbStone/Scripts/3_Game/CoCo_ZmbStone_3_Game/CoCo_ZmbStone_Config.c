// 僵尸类型伤害配置类
class CoCo_ZombieDamageConfig
{
	float health;
	float shock;
	float keepMinimumHealth;
	
	void CoCo_ZombieDamageConfig()
	{
		health = 2.5;
		shock = 15.0;
		keepMinimumHealth = 30.0;
	}
}

// JSON配置数据类
class CoCo_ZmbStone_ConfigData
{
	int enabled;
	int onlyIfPlayerOnObstacle;
	int defaultZombieCanThrow;
	float bleedChance;
	
	// 默认伤害设置
	ref CoCo_ZombieDamageConfig damage;
	
	// 投掷设置
	float throwRate;
	float throwForce;
	float throwDistanceMax;
	float throwDistanceMin;
	
	// 僵尸类型独立伤害配置（key=僵尸类型名称，value=伤害配置）
	ref map<string, ref CoCo_ZombieDamageConfig> zombieDamageConfigs;
	
	// 僵尸类型独立流血概率配置（key=僵尸类型名称，value=流血概率）
	ref map<string, float> zombieBleedChances;
	
	void CoCo_ZmbStone_ConfigData()
	{
		enabled = 1;
		onlyIfPlayerOnObstacle = 1;
		defaultZombieCanThrow = 1;
		bleedChance = 0.0;
		
		damage = new CoCo_ZombieDamageConfig();
		damage.health = 2.5;
		damage.shock = 15.0;
		damage.keepMinimumHealth = 30.0;
		
		throwRate = 5.0;
		throwForce = 90.0;
		throwDistanceMax = 10.0;
		throwDistanceMin = 2.0;
		
		zombieDamageConfigs = new map<string, ref CoCo_ZombieDamageConfig>();
		zombieBleedChances = new map<string, float>();
	}
}

class CoCo_ZmbStone_Config
{
	// 配置文件路径
	private const static string CONFIG_ROOT = "$profile:\\CoCo_ZmbStone\\";
	private const static string CONFIG_FILE = "CoCo_ZmbStone_Config.json";
	private static ref CoCo_ZmbStone_ConfigData m_ConfigData;
	private static bool m_ConfigLoaded = false;
	
	// 默认值（用于向后兼容和初始化）
	static int Enabled = 1; // 0=禁用, 1=启用
	static int OnlyIfPlayerOnObstacle = 1; // 0=总是丢, 1=只在障碍物上
	static float DamageHealth = 2.5; // 生命值伤害
	static float DamageShock = 15.0; // 冲击伤害
	static float KeepMinimumHealth = 30.0; // 最低生命值（防止被石头砸死）
	static float ThrowRate = 5.0; // 丢石头间隔（秒）
	static float ThrowForce = 90.0; // 投掷力度
	static float ThrowDistanceMax = 10.0; // 最大投掷距离
	static float ThrowDistanceMin = 2.0; // 最小投掷距离
	static int DefaultZombieCanThrow = 1; // 默认值
	static float BleedChance = 0.0; // 触发流血的概率（0-1）
	
	// 加载配置文件
	static void LoadConfig()
	{
		if (m_ConfigLoaded)
			return;
		
		// 确保配置目录存在
		if (!FileExist(CONFIG_ROOT))
		{
			MakeDirectory(CONFIG_ROOT);
		}
		
		string configPath = CONFIG_ROOT + CONFIG_FILE;
		
		if (FileExist(configPath))
		{
			// 从profiles加载配置
			JsonFileLoader<CoCo_ZmbStone_ConfigData>.JsonLoadFile(configPath, m_ConfigData);
			
			if (m_ConfigData)
			{
				// 同步到静态变量（向后兼容）
				Enabled = m_ConfigData.enabled;
				OnlyIfPlayerOnObstacle = m_ConfigData.onlyIfPlayerOnObstacle;
				DefaultZombieCanThrow = m_ConfigData.defaultZombieCanThrow;
				BleedChance = m_ConfigData.bleedChance;
				
				if (m_ConfigData.damage)
				{
					DamageHealth = m_ConfigData.damage.health;
					DamageShock = m_ConfigData.damage.shock;
					KeepMinimumHealth = m_ConfigData.damage.keepMinimumHealth;
				}
				
				ThrowRate = m_ConfigData.throwRate;
				ThrowForce = m_ConfigData.throwForce;
				ThrowDistanceMax = m_ConfigData.throwDistanceMax;
				ThrowDistanceMin = m_ConfigData.throwDistanceMin;
				
				// 确保zombieDamageConfigs不为null
				if (!m_ConfigData.zombieDamageConfigs)
				{
					m_ConfigData.zombieDamageConfigs = new map<string, ref CoCo_ZombieDamageConfig>();
				}
				
				// 确保zombieBleedChances不为null
				if (!m_ConfigData.zombieBleedChances)
				{
					m_ConfigData.zombieBleedChances = new map<string, float>();
				}
				
				Print("[CoCo_ZmbStone] 配置加载成功: " + configPath);
				Print("[CoCo_ZmbStone] 已配置 " + m_ConfigData.zombieDamageConfigs.Count() + " 种僵尸类型的独立伤害");
			}
			else
			{
				Print("[CoCo_ZmbStone] 配置文件解析失败，使用默认配置");
				CreateDefaultConfig();
			}
		}
		else
		{
			Print("[CoCo_ZmbStone] 配置文件不存在，创建默认配置: " + configPath);
			CreateDefaultConfig();
		}
		
		m_ConfigLoaded = true;
	}
	
	// 创建默认配置文件
	static void CreateDefaultConfig()
	{
		m_ConfigData = new CoCo_ZmbStone_ConfigData();
		
		// 同步默认值
		m_ConfigData.enabled = Enabled;
		m_ConfigData.onlyIfPlayerOnObstacle = OnlyIfPlayerOnObstacle;
		m_ConfigData.defaultZombieCanThrow = DefaultZombieCanThrow;
		m_ConfigData.damage.health = DamageHealth;
		m_ConfigData.damage.shock = DamageShock;
		m_ConfigData.damage.keepMinimumHealth = KeepMinimumHealth;
		m_ConfigData.throwRate = ThrowRate;
		m_ConfigData.throwForce = ThrowForce;
		m_ConfigData.throwDistanceMax = ThrowDistanceMax;
		m_ConfigData.throwDistanceMin = ThrowDistanceMin;
		m_ConfigData.bleedChance = BleedChance;
		if (!m_ConfigData.zombieBleedChances)
		{
			m_ConfigData.zombieBleedChances = new map<string, float>();
		}
		
		// 保存默认配置到文件
		string configPath = CONFIG_ROOT + CONFIG_FILE;
		JsonFileLoader<CoCo_ZmbStone_ConfigData>.JsonSaveFile(configPath, m_ConfigData);
		Print("[CoCo_ZmbStone] 默认配置已保存到: " + configPath);
	}
	
	// 根据僵尸类型获取伤害值
	// 优先从JSON配置读取，如果没有则使用默认配置
	// 参数：zombieType - 僵尸类型名称（字符串），如果为空则使用默认配置
	// 返回：array[0]=DamageHealth, array[1]=DamageShock, array[2]=KeepMinimumHealth
	static array<float> GetDamageForZombie(string zombieType = "")
	{
		array<float> damage = {-1.0, -1.0, -1.0};
		
		// 确保配置已加载
		if (!m_ConfigLoaded)
		{
			LoadConfig();
		}
		
		// 如果僵尸类型为空，使用默认配置
		if (zombieType == "")
		{
			damage[0] = DamageHealth;
			damage[1] = DamageShock;
			damage[2] = KeepMinimumHealth;
			return damage;
		}
		
		// 从JSON配置中查找该僵尸类型的独立伤害配置
		if (m_ConfigData && m_ConfigData.zombieDamageConfigs)
		{
			ref CoCo_ZombieDamageConfig zombieDamage = m_ConfigData.zombieDamageConfigs.Get(zombieType);
			
			if (zombieDamage)
			{
				// 找到该僵尸类型的独立配置
				damage[0] = zombieDamage.health;
				damage[1] = zombieDamage.shock;
				damage[2] = zombieDamage.keepMinimumHealth;
				return damage;
			}
		}
		
		// 没有找到独立配置，使用默认配置
		damage[0] = DamageHealth;
		damage[1] = DamageShock;
		damage[2] = KeepMinimumHealth;
		
		return damage;
	}
	
	// 获取僵尸的流血概率，优先使用独立配置
	static float GetBleedChanceForZombie(string zombieType = "")
	{
		if (!m_ConfigLoaded)
		{
			LoadConfig();
		}
		
		float chance = BleedChance;
		
		if (zombieType == "" || !m_ConfigData || !m_ConfigData.zombieBleedChances)
		{
			return chance;
		}
		
		float customChance;
		if (m_ConfigData.zombieBleedChances.Find(zombieType, customChance))
		{
			return customChance;
		}
		
		return chance;
	}
	
	// 获取配置数据（用于其他类访问）
	static CoCo_ZmbStone_ConfigData GetConfigData()
	{
		if (!m_ConfigLoaded)
		{
			LoadConfig();
		}
		return m_ConfigData;
	}
}

