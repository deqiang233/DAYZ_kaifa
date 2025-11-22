// 玩家洗练数据管理器
// 管理每个玩家的洗练武器数据，使用 Steam ID 作为唯一标识

class RefinedWeaponData
{
    string ItemType;        // 武器类型
    float RefineMultiplier; // 洗练倍率
    int RefineTime;         // 洗练时间戳（可选，用于记录）

    void RefinedWeaponData()
    {
        ItemType = "";
        RefineMultiplier = 1.0;
        RefineTime = 0;
    }
}

class PlayerRefineData
{
    string SteamId;                              // 玩家 Steam ID
    ref map<string, ref RefinedWeaponData> Weapons; // 武器数据映射 (ItemType -> RefinedWeaponData)

    void PlayerRefineData()
    {
        SteamId = "";
        Weapons = new map<string, ref RefinedWeaponData>();
    }
}

class PlayerRefineDataManager
{
    private static const string DATA_DIR = "$profile:cyx_qianghua/player_refine/";
    private static ref map<string, ref PlayerRefineData> m_PlayerDataCache = new map<string, ref PlayerRefineData>();

    // 获取玩家 Steam ID
    static string GetPlayerSteamId(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
        {
            return "";
        }

        string steamId = player.GetIdentity().GetPlainId();
        return steamId;
    }

    // 获取玩家数据文件路径
    static string GetPlayerDataFile(string steamId)
    {
        if (steamId == "")
        {
            return "";
        }

        return DATA_DIR + steamId + ".json";
    }

    // 加载玩家洗练数据
    static PlayerRefineData LoadPlayerData(string steamId)
    {
        if (steamId == "")
        {
            return null;
        }

        // 先检查缓存
        if (m_PlayerDataCache.Contains(steamId))
        {
            return m_PlayerDataCache.Get(steamId);
        }

        // 从文件加载
        string filePath = GetPlayerDataFile(steamId);
        if (!FileExist(filePath))
        {
            // 文件不存在，创建新数据
            ref PlayerRefineData newData = new PlayerRefineData();
            newData.SteamId = steamId;
            m_PlayerDataCache.Set(steamId, newData);
            return newData;
        }

        ref PlayerRefineData data;
        JsonFileLoader<PlayerRefineData>.JsonLoadFile(filePath, data);

        if (!data)
        {
            // 加载失败，创建新数据
            data = new PlayerRefineData();
            data.SteamId = steamId;
        }
        else if (data.SteamId == "")
        {
            // 确保 SteamId 正确
            data.SteamId = steamId;
        }

        // 确保 Weapons 映射存在
        if (!data.Weapons)
        {
            data.Weapons = new map<string, ref RefinedWeaponData>();
        }

        // 存入缓存
        m_PlayerDataCache.Set(steamId, data);

        Debug.Log("[CYX_ENHANCE][SERVER] LoadPlayerData: loaded data for SteamId=" + steamId + ", weapons count=" + data.Weapons.Count().ToString(), "CYX_ENHANCE");

        return data;
    }

    // 保存玩家洗练数据
    static void SavePlayerData(string steamId, PlayerRefineData data)
    {
        if (steamId == "" || !data)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: invalid parameters, steamId=" + steamId, "CYX_ENHANCE");
            return;
        }

        // 确保 SteamId 正确
        data.SteamId = steamId;

        // 更新缓存
        m_PlayerDataCache.Set(steamId, data);

        // 保存到文件
        string filePath = GetPlayerDataFile(steamId);
        Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: filePath=" + filePath, "CYX_ENHANCE");
        
        if (filePath == "")
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: invalid file path", "CYX_ENHANCE");
            return;
        }
        
        // 确保目录存在
        string dirPath = DATA_DIR;
        Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: DATA_DIR=" + dirPath, "CYX_ENHANCE");
        
        if (!FileExist(dirPath))
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: directory does not exist, creating...", "CYX_ENHANCE");
            if (MakeDirectory(dirPath))
            {
                Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: directory created successfully", "CYX_ENHANCE");
            }
            else
            {
                Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: WARNING - failed to create directory!", "CYX_ENHANCE");
            }
        }
        else
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: directory exists", "CYX_ENHANCE");
        }
        
        // 保存文件
        Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: calling JsonSaveFile...", "CYX_ENHANCE");
        JsonFileLoader<PlayerRefineData>.JsonSaveFile(filePath, data);
        Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: JsonSaveFile returned", "CYX_ENHANCE");
        
        // 验证文件是否保存成功
        bool fileExists = FileExist(filePath);
        string existsText = "false";
        if (fileExists)
        {
            existsText = "true";
        }
        Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: FileExist(" + filePath + ")=" + existsText, "CYX_ENHANCE");
        
        if (fileExists)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: SUCCESS - saved data for SteamId=" + steamId + ", weapons count=" + data.Weapons.Count().ToString() + ", file=" + filePath, "CYX_ENHANCE");
        }
        else
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SavePlayerData: FAILED - file not found after save! SteamId=" + steamId + ", file=" + filePath, "CYX_ENHANCE");
        }
    }

    // 保存玩家洗练的武器
    static void SaveRefinedWeapon(PlayerBase player, string itemType, float multiplier)
    {
        string playerStatus = "null";
        if (player)
        {
            playerStatus = "valid";
        }
        Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: START - player=" + playerStatus + ", itemType=" + itemType + ", multiplier=" + multiplier.ToString(), "CYX_ENHANCE");
        
        if (!player || itemType == "" || multiplier <= 0.0)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: invalid parameters", "CYX_ENHANCE");
            return;
        }

        string steamId = GetPlayerSteamId(player);
        Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: SteamId=" + steamId, "CYX_ENHANCE");
        
        if (steamId == "")
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: failed to get SteamId", "CYX_ENHANCE");
            return;
        }

        // 加载玩家数据
        ref PlayerRefineData data = LoadPlayerData(steamId);
        if (!data)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: failed to load player data", "CYX_ENHANCE");
            return;
        }

        // 创建或更新武器数据
        ref RefinedWeaponData weaponData;
        if (data.Weapons.Contains(itemType))
        {
            weaponData = data.Weapons.Get(itemType);
        }
        else
        {
            weaponData = new RefinedWeaponData();
            data.Weapons.Set(itemType, weaponData);
        }

        weaponData.ItemType = itemType;
        weaponData.RefineMultiplier = multiplier;
        weaponData.RefineTime = GetGame().GetTime();

        // 保存数据
        SavePlayerData(steamId, data);

        Debug.Log("[CYX_ENHANCE][SERVER] SaveRefinedWeapon: saved weapon " + itemType + " with multiplier " + multiplier.ToString() + " for player " + steamId, "CYX_ENHANCE");
    }

    // 获取玩家洗练的武器倍率
    static float GetRefinedWeaponMultiplier(PlayerBase player, string itemType)
    {
        if (!player || itemType == "")
        {
            return 1.0;
        }

        string steamId = GetPlayerSteamId(player);
        if (steamId == "")
        {
            return 1.0;
        }

        // 加载玩家数据
        ref PlayerRefineData data = LoadPlayerData(steamId);
        if (!data || !data.Weapons || !data.Weapons.Contains(itemType))
        {
            return 1.0;
        }

        ref RefinedWeaponData weaponData = data.Weapons.Get(itemType);
        if (!weaponData)
        {
            return 1.0;
        }

        return weaponData.RefineMultiplier;
    }

    // 恢复武器的洗练数据（在武器加载时调用）
    static void RestoreWeaponRefineData(PlayerBase player, Weapon_Base weapon)
    {
        if (!player || !weapon)
        {
            return;
        }

        string itemType = weapon.GetType();
        if (itemType == "")
        {
            return;
        }

        // 如果武器已经有洗练数据，不覆盖
        if (weapon.HasRefineData())
        {
            return;
        }

        // 从玩家数据中获取洗练倍率
        float multiplier = GetRefinedWeaponMultiplier(player, itemType);
        if (multiplier != 1.0)
        {
            weapon.SetRefineDamageMultiplier(multiplier);
            Debug.Log("[CYX_ENHANCE][SERVER] RestoreWeaponRefineData: restored multiplier " + multiplier.ToString() + " for weapon " + itemType, "CYX_ENHANCE");
        }
    }

    // 清除玩家数据缓存（可选，用于内存管理）
    static void ClearCache()
    {
        m_PlayerDataCache.Clear();
    }

    // 清除特定玩家的缓存
    static void ClearPlayerCache(string steamId)
    {
        if (steamId != "" && m_PlayerDataCache.Contains(steamId))
        {
            m_PlayerDataCache.Remove(steamId);
        }
    }
}

