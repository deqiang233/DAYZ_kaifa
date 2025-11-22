class ItemSettingConfig
{
    ref array<ref EnhanceMaterial> RequiredMaterials;
    float SuccessRate;
    bool RequireBinding;
    string ProtectionCardName;
    string ProtectionCardItem;
    int ProtectionCardQuantity;
    float WeaponDamage;
    float FixedDamageBonus;

    void ItemSettingConfig()
    {
        RequiredMaterials = new array<ref EnhanceMaterial>();
        SuccessRate = 0.0;
        RequireBinding = false;
        ProtectionCardName = "";
        ProtectionCardItem = "";
        ProtectionCardQuantity = 0;
        WeaponDamage = 0.0;
        FixedDamageBonus = 0.0;
    }
}

class EnhanceLevel
{
    float SuccessRate;
    ref array<ref EnhanceMaterial> RequiredMaterials;
    bool RequireBinding;
    string ProtectionCardItem;
    string ProtectionCardName;
    int ProtectionCardQuantity;
    ref array<ref EnhanceResultItem> SuccessOutput;
    ref array<ref EnhanceResultItem> FailureOutput;
    ref array<ref EnhanceResultItem> ProtectionCardOutput;
    float WeaponDamage;
    float FixedDamageBonus;

    void EnhanceLevel()
    {
        RequiredMaterials = new array<ref EnhanceMaterial>();
        SuccessOutput = new array<ref EnhanceResultItem>();
        FailureOutput = new array<ref EnhanceResultItem>();
        ProtectionCardOutput = new array<ref EnhanceResultItem>();
        SuccessRate = 0.0;
        RequireBinding = false;
        ProtectionCardItem = "";
        ProtectionCardName = "";
        ProtectionCardQuantity = 0;
        WeaponDamage = 0.0;
        FixedDamageBonus = 0.0;
    }
}

class EnhanceItem
{
    string ItemType;
    string DisplayName;
    string ItemSetting;
    ref array<ref EnhanceResultItem> SuccessOutput;
    ref array<ref EnhanceResultItem> FailureOutput;
    ref array<ref EnhanceResultItem> ProtectionCardOutput;
    ref EnhanceLevel LevelConfig;

    void EnhanceItem()
    {
        SuccessOutput = new array<ref EnhanceResultItem>();
        FailureOutput = new array<ref EnhanceResultItem>();
        ProtectionCardOutput = new array<ref EnhanceResultItem>();
    }
}

class EnhanceCategory
{
    string CategoryName;
    ref array<ref EnhanceItem> EnhanceItems;

    void EnhanceCategory()
    {
        EnhanceItems = new array<ref EnhanceItem>();
    }
}

class EnhanceConfig
{
    ref array<ref EnhanceCategory> EnhancementCategories;
    ref map<string, ref ItemSettingConfig> DefaultItemSettings;

    void EnhanceConfig()
    {
        EnhancementCategories = new array<ref EnhanceCategory>();
        DefaultItemSettings = new map<string, ref ItemSettingConfig>();
    }
}

class DefaultItemSettingsConfig
{
    ref map<string, ref ItemSettingConfig> DefaultItemSettings;

    void DefaultItemSettingsConfig()
    {
        DefaultItemSettings = new map<string, ref ItemSettingConfig>();
    }
}

class EnhanceConfigManager
{
    // 注意：DayZ 的虚拟路径分隔符使用正斜杠（/）。旧版脚本也是用 /，
    // 如果改成反斜杠（\）会导致 FileExist/JsonLoadFile 找不到文件。
    private const static string CONFIG_ROOT = "$profile:cyx_qianghua/";
    private const static string CONFIG_FILE = CONFIG_ROOT + "EnhanceConfig.json";
    private const static string SETTINGS_FILE = CONFIG_ROOT + "DefaultItemSettings.json";

    private static ref EnhanceConfig m_Config;
    private static ref map<string, ref EnhanceItem> m_ItemIndex;

    static void LoadConfig()
    {
        if (m_Config)
        {
            return;
        }

        if (FileExist(CONFIG_FILE))
        {
            JsonFileLoader<EnhanceConfig>.JsonLoadFile(CONFIG_FILE, m_Config);
        }

        if (!m_Config)
        {
            m_Config = new EnhanceConfig();
        }

        LoadDefaultSettings();
        ProcessConfig();
    }

    static void LoadDefaultSettings()
    {
        Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: checking file=" + SETTINGS_FILE, "CYX_ENHANCE");
        if (!FileExist(SETTINGS_FILE))
        {
            Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: file does not exist", "CYX_ENHANCE");
            return;
        }

        Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: file exists, loading...", "CYX_ENHANCE");
        ref DefaultItemSettingsConfig wrapper;
        JsonFileLoader<DefaultItemSettingsConfig>.JsonLoadFile(SETTINGS_FILE, wrapper);

        if (!wrapper || !wrapper.DefaultItemSettings)
        {
            string wrapperText = "null";
            if (wrapper)
            {
                wrapperText = "not null";
            }
            string settingsText = "null";
            if (wrapper && wrapper.DefaultItemSettings)
            {
                settingsText = "not null";
            }
            Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: wrapper=" + wrapperText + " DefaultItemSettings=" + settingsText, "CYX_ENHANCE");
            return;
        }

        int settingsCount = wrapper.DefaultItemSettings.Count();
        Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: loaded " + settingsCount.ToString() + " item settings", "CYX_ENHANCE");

        if (!m_Config.DefaultItemSettings)
        {
            m_Config.DefaultItemSettings = new map<string, ref ItemSettingConfig>();
        }

        int loadedCount = 0;
        foreach (string key, ItemSettingConfig value : wrapper.DefaultItemSettings)
        {
            int materialsCount = 0;
            if (value && value.RequiredMaterials)
            {
                materialsCount = value.RequiredMaterials.Count();
            }
            Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: setting[" + key + "] has " + materialsCount.ToString() + " materials", "CYX_ENHANCE");
            
            // 打印每个材料的详细信息
            if (value && value.RequiredMaterials)
            {
                for (int i = 0; i < value.RequiredMaterials.Count(); i++)
                {
                    EnhanceMaterial mat = value.RequiredMaterials.Get(i);
                    if (mat)
                    {
                        Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: setting[" + key + "] Material[" + i.ToString() + "] type=" + mat.MaterialType + " qty=" + mat.Quantity.ToString() + " display=" + mat.DisplayName, "CYX_ENHANCE");
                    }
                }
            }
            
            m_Config.DefaultItemSettings.Set(key, value);
            loadedCount++;
        }
        Debug.Log("[CYX_ENHANCE][SERVER] LoadDefaultSettings: loaded " + loadedCount.ToString() + " settings into m_Config", "CYX_ENHANCE");
    }

    static void ProcessConfig()
    {
        m_ItemIndex = new map<string, ref EnhanceItem>();

        if (!m_Config || !m_Config.EnhancementCategories)
        {
            return;
        }

        foreach (EnhanceCategory category : m_Config.EnhancementCategories)
        {
            if (!category || !category.EnhanceItems)
            {
                continue;
            }

            foreach (EnhanceItem item : category.EnhanceItems)
            {
                if (!item)
                {
                    continue;
                }

                PrepareItem(item);

                if (item.ItemType != "")
                {
                    m_ItemIndex.Set(item.ItemType, item);
                }
            }
        }
    }

    static void PrepareItem(EnhanceItem item)
    {
        ItemSettingConfig setting = GetSetting(item.ItemSetting);
        ref EnhanceLevel level = new EnhanceLevel();

        if (setting)
        {
            int settingMaterialsCount = 0;
            if (setting.RequiredMaterials)
            {
                settingMaterialsCount = setting.RequiredMaterials.Count();
            }
            Debug.Log("[CYX_ENHANCE][SERVER] PrepareItem: ItemSetting=" + item.ItemSetting + " has " + settingMaterialsCount.ToString() + " materials in setting", "CYX_ENHANCE");
            
            level.SuccessRate = setting.SuccessRate;
            level.RequireBinding = setting.RequireBinding;
            level.ProtectionCardItem = setting.ProtectionCardItem;
            level.ProtectionCardName = setting.ProtectionCardName;
            level.ProtectionCardQuantity = setting.ProtectionCardQuantity;
            level.WeaponDamage = setting.WeaponDamage;
            level.FixedDamageBonus = setting.FixedDamageBonus;
            level.RequiredMaterials = CloneMaterials(setting.RequiredMaterials);
            
            int levelMaterialsCount = 0;
            if (level.RequiredMaterials)
            {
                levelMaterialsCount = level.RequiredMaterials.Count();
            }
            Debug.Log("[CYX_ENHANCE][SERVER] PrepareItem: After cloning, level.RequiredMaterials has " + levelMaterialsCount.ToString() + " materials", "CYX_ENHANCE");
        }
        else
        {
            Debug.Log("[CYX_ENHANCE][SERVER] PrepareItem: ItemSetting=" + item.ItemSetting + " not found in DefaultItemSettings", "CYX_ENHANCE");
        }

        if (item.SuccessOutput && item.SuccessOutput.Count() > 0)
        {
            level.SuccessOutput = CloneResults(item.SuccessOutput);
        }

        if (item.FailureOutput && item.FailureOutput.Count() > 0)
        {
            level.FailureOutput = CloneResults(item.FailureOutput);
        }

        if (item.ProtectionCardOutput && item.ProtectionCardOutput.Count() > 0)
        {
            level.ProtectionCardOutput = CloneResults(item.ProtectionCardOutput);
        }

        // Ensure there is at least one output defined.
        if (level.SuccessOutput.Count() == 0 && item.SuccessOutput)
        {
            level.SuccessOutput = CloneResults(item.SuccessOutput);
        }

        item.LevelConfig = level;
    }

    static ItemSettingConfig GetSetting(string name)
    {
        if (!m_Config || !m_Config.DefaultItemSettings || name == "")
        {
            return null;
        }

        if (!m_Config.DefaultItemSettings.Contains(name))
        {
            return null;
        }

        return m_Config.DefaultItemSettings.Get(name);
    }

    static EnhanceDisplayInfo BuildDisplayInfo(string itemType)
    {
        EnhanceItem item = FindItem(itemType);
        if (!item || !item.LevelConfig)
        {
            return null;
        }

        ref EnhanceDisplayInfo info = new EnhanceDisplayInfo();
        info.ItemType = item.ItemType;
        if (item.DisplayName != "")
        {
            info.DisplayName = item.DisplayName;
        }
        else
        {
            info.DisplayName = item.ItemType;
        }

        info.SuccessRate = item.LevelConfig.SuccessRate;

        ref array<ref EnhanceMaterial> materialsSource = item.LevelConfig.RequiredMaterials;
        int sourceCount = 0;
        if (materialsSource)
        {
            sourceCount = materialsSource.Count();
        }
        Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: item.LevelConfig.RequiredMaterials count=" + sourceCount.ToString(), "CYX_ENHANCE");
        
        if (!materialsSource || materialsSource.Count() == 0)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: LevelConfig materials empty, trying fallback from ItemSetting=" + item.ItemSetting, "CYX_ENHANCE");
            ItemSettingConfig fallbackSetting = GetSetting(item.ItemSetting);
            if (fallbackSetting && fallbackSetting.RequiredMaterials)
            {
                int fallbackCount = fallbackSetting.RequiredMaterials.Count();
                Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: fallback setting found with " + fallbackCount.ToString() + " materials", "CYX_ENHANCE");
                materialsSource = fallbackSetting.RequiredMaterials;
            }
            else
            {
                Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: fallback setting not found or has no materials", "CYX_ENHANCE");
            }
        }
        
        info.RequiredMaterials = CloneMaterials(materialsSource);
        int finalCount = 0;
        if (info.RequiredMaterials)
        {
            finalCount = info.RequiredMaterials.Count();
        }
        Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: final RequiredMaterials count=" + finalCount.ToString(), "CYX_ENHANCE");
        
        // 打印每个材料的详细信息
        if (info.RequiredMaterials)
        {
            for (int i = 0; i < info.RequiredMaterials.Count(); i++)
            {
                EnhanceMaterial mat = info.RequiredMaterials.Get(i);
                if (mat)
                {
                    Debug.Log("[CYX_ENHANCE][SERVER] BuildDisplayInfo: Material[" + i.ToString() + "] type=" + mat.MaterialType + " qty=" + mat.Quantity.ToString() + " display=" + mat.DisplayName, "CYX_ENHANCE");
                }
            }
        }

        if (item.LevelConfig.ProtectionCardItem != "" && item.LevelConfig.ProtectionCardQuantity > 0)
        {
            info.HasProtectionOption = true;
            info.ProtectionCardItem = item.LevelConfig.ProtectionCardItem;
            info.ProtectionCardName = item.LevelConfig.ProtectionCardName;
            info.ProtectionCardQuantity = item.LevelConfig.ProtectionCardQuantity;
        }

        info.HasData = true;
        info.ErrorMessage = "";

        return info;
    }

    static EnhanceDisplayInfo BuildErrorInfo(string itemType, string message)
    {
        ref EnhanceDisplayInfo info = new EnhanceDisplayInfo();
        info.ItemType = itemType;
        info.DisplayName = itemType;
        info.HasData = false;
        info.ErrorMessage = message;
        return info;
    }

    static EnhanceConfig GetConfig()
    {
        if (!m_Config)
        {
            LoadConfig();
        }
        return m_Config;
    }

    static EnhanceItem FindItem(string itemType)
    {
        if (!m_Config)
        {
            LoadConfig();
        }

        if (!m_ItemIndex || !m_ItemIndex.Contains(itemType))
        {
            return null;
        }

        return m_ItemIndex.Get(itemType);
    }

    static ref array<ref EnhanceMaterial> CloneMaterials(array<ref EnhanceMaterial> source)
    {
        ref array<ref EnhanceMaterial> output = new array<ref EnhanceMaterial>();
        if (!source)
        {
            Debug.Log("[CYX_ENHANCE][SERVER] CloneMaterials: source is null", "CYX_ENHANCE");
            return output;
        }

        int sourceCount = source.Count();
        Debug.Log("[CYX_ENHANCE][SERVER] CloneMaterials: cloning " + sourceCount.ToString() + " materials", "CYX_ENHANCE");
        
        int clonedCount = 0;
        foreach (EnhanceMaterial material : source)
        {
            if (!material)
            {
                Debug.Log("[CYX_ENHANCE][SERVER] CloneMaterials: skipping null material", "CYX_ENHANCE");
                continue;
            }

            int qty = material.Quantity;
            if (qty <= 0)
            {
                qty = 1;
            }

            string displayName = material.DisplayName;
            if (displayName == "")
            {
                displayName = material.MaterialType;
            }

            Debug.Log("[CYX_ENHANCE][SERVER] CloneMaterials: cloning material type=" + material.MaterialType + " qty=" + qty.ToString() + " display=" + displayName, "CYX_ENHANCE");
            ref EnhanceMaterial copy = new EnhanceMaterial(material.MaterialType, qty, displayName);
            output.Insert(copy);
            clonedCount++;
        }

        Debug.Log("[CYX_ENHANCE][SERVER] CloneMaterials: cloned " + clonedCount.ToString() + " materials, output count=" + output.Count().ToString(), "CYX_ENHANCE");
        return output;
    }

    static ref array<ref EnhanceResultItem> CloneResults(array<ref EnhanceResultItem> source)
    {
        ref array<ref EnhanceResultItem> output = new array<ref EnhanceResultItem>();
        if (!source)
        {
            return output;
        }

        foreach (EnhanceResultItem item : source)
        {
            if (!item)
            {
                continue;
            }

            int qty = item.Quantity;
            if (qty <= 0)
            {
                qty = 1;
            }

            ref EnhanceResultItem copy = new EnhanceResultItem(item.ItemType, qty);
            output.Insert(copy);
        }

        return output;
    }
}

