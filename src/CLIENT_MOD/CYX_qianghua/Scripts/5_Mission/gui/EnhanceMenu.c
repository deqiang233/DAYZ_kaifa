class EnhanceMenu extends UIScriptedMenu
{
    private static EnhanceMenu s_ActiveMenu;

    private Widget m_Root;
    private ItemPreviewWidget m_ItemPreview;
    private TextWidget m_ItemNameText;
    private TextWidget m_ItemDisplayHint;
    private TextWidget m_SuccessRateText;
    private TextWidget m_WarningText;
    private TextWidget m_RefineInfoText;
    private Widget m_MaterialsList;
    private Widget m_RefineMaterialsList; // 洗练材料列表容器
    private TextWidget m_RefineMaterialsTitleText; // 洗练材料标题
    private CheckBoxWidget m_UseProtectionCheckbox;
    private CheckBoxWidget m_MaterialListProtectionCheckbox; // 材料列表中的保护石复选框
    private TextWidget m_ProtectionText;
    private ButtonWidget m_EnhanceButton;
    private ButtonWidget m_CloseButton;
    private ButtonWidget m_RefineButton;

    private ref EnhanceDisplayInfo m_CurrentInfo;
    private string m_LastItemType;
    private float m_UpdateTimer;
    private bool m_RequestInFlight;

    private const float UPDATE_INTERVAL = 0.25;

    void EnhanceMenu()
    {
        Print("[CYX_ENHANCE] EnhanceMenu constructor called");
        
        if (!GetGame() || !GetGame().GetMission())
        {
            Print("[CYX_ENHANCE] ERROR: Game or Mission is null in constructor");
            return;
        }
        
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetMission().GetHud().Show(false);
        s_ActiveMenu = this;
        
        Print("[CYX_ENHANCE] EnhanceMenu constructor completed");
    }

    void ~EnhanceMenu()
    {
        if (GetGame() && GetGame().GetMission())
        {
            GetGame().GetMission().PlayerControlEnable(true);
            GetGame().GetMission().GetHud().Show(true);
        }
        s_ActiveMenu = null;
    }

    override Widget Init()
    {
        Print("[CYX_ENHANCE] Init() called");
        
        m_Root = GetGame().GetWorkspace().CreateWidgets("cyx_qianghua/gui/enhance.layout");
        if (!m_Root)
        {
            Print("[CYX_ENHANCE] ERROR: Failed to create root widget from enhance.layout");
            return null;
        }
        
        Print("[CYX_ENHANCE] Root widget created successfully");
        
        // 确保根窗口始终显示
        m_Root.Show(true);
        Print("[CYX_ENHANCE] Root widget shown");
        
        // 确保主要容器都显示
        Widget enhanceBackground = m_Root.FindAnyWidget("EnhanceBackground");
        if (enhanceBackground)
        {
            enhanceBackground.Show(true);
            Print("[CYX_ENHANCE] EnhanceBackground shown");
        }
        
        Widget mainPanel = m_Root.FindAnyWidget("MainPanel");
        if (mainPanel)
        {
            mainPanel.Show(true);
            Print("[CYX_ENHANCE] MainPanel shown");
        }

        m_ItemPreview = ItemPreviewWidget.Cast(m_Root.FindAnyWidget("ItemPreview"));
        m_ItemNameText = TextWidget.Cast(m_Root.FindAnyWidget("ItemNameText"));
        m_ItemDisplayHint = TextWidget.Cast(m_Root.FindAnyWidget("ItemDisplayPositionLabel"));
        m_SuccessRateText = TextWidget.Cast(m_Root.FindAnyWidget("SuccessRateText"));
        m_WarningText = TextWidget.Cast(m_Root.FindAnyWidget("WarningText"));
        m_RefineInfoText = TextWidget.Cast(m_Root.FindAnyWidget("RefineInfoText"));
        m_MaterialsList = m_Root.FindAnyWidget("MaterialsList");
        if (!m_MaterialsList)
        {
            Print("[CYX_ENHANCE] MaterialsList widget not found in enhance.layout");
        }
        else
        {
            Print("[CYX_ENHANCE] MaterialsList widget ready: " + m_MaterialsList.ToString());
        }
        
        // 查找洗练材料列表容器
        m_RefineMaterialsList = m_Root.FindAnyWidget("RefineMaterialsListContainer");
        if (m_RefineMaterialsList)
        {
            Print("[CYX_ENHANCE] RefineMaterialsListContainer found");
            // 初始状态隐藏，等待数据加载后再显示
            m_RefineMaterialsList.Show(false);
            // 确保父容器显示（但不显示列表本身）
            Widget listParent = m_RefineMaterialsList.GetParent();
            while (listParent)
            {
                listParent.Show(true);
                listParent = listParent.GetParent();
            }
        }
        else
        {
            Print("[CYX_ENHANCE] RefineMaterialsListContainer NOT found!");
        }
        
        // 查找洗练材料标题
        m_RefineMaterialsTitleText = TextWidget.Cast(m_Root.FindAnyWidget("RefineMaterialsTitleText"));
        if (m_RefineMaterialsTitleText)
        {
            Print("[CYX_ENHANCE] RefineMaterialsTitleText found");
            // 初始状态隐藏，等待数据加载后再显示
            m_RefineMaterialsTitleText.Show(false);
            // 确保父容器显示（但不显示标题本身）
            Widget titleParent = m_RefineMaterialsTitleText.GetParent();
            while (titleParent)
            {
                titleParent.Show(true);
                titleParent = titleParent.GetParent();
            }
        }
        else
        {
            Print("[CYX_ENHANCE] RefineMaterialsTitleText NOT found!");
        }
        // 直接查找控件，FindAnyWidget 已经内置递归查找功能
        Widget protectionContainer = m_Root.FindAnyWidget("ProtectionContainer");
        if (protectionContainer)
        {
            Print("[CYX_ENHANCE] ProtectionContainer found, showing it");
            protectionContainer.Show(true);
        }
        else
        {
            Print("[CYX_ENHANCE] ProtectionContainer NOT found!");
        }
        
        m_UseProtectionCheckbox = CheckBoxWidget.Cast(m_Root.FindAnyWidget("UseProtectionCheckbox"));
        m_ProtectionText = TextWidget.Cast(m_Root.FindAnyWidget("ProtectionStoneText"));
        
        // 直接显示控件
        if (m_UseProtectionCheckbox)
        {
            Print("[CYX_ENHANCE] UseProtectionCheckbox found, showing it");
            m_UseProtectionCheckbox.Show(true);
            Widget checkboxParent = m_UseProtectionCheckbox.GetParent();
            if (checkboxParent)
            {
                checkboxParent.Show(true);
                Print("[CYX_ENHANCE] UseProtectionCheckbox parent shown");
            }
        }
        else
        {
            Print("[CYX_ENHANCE] UseProtectionCheckbox NOT found!");
        }
        
        if (m_ProtectionText)
        {
            Print("[CYX_ENHANCE] ProtectionStoneText found, showing it");
            m_ProtectionText.Show(true);
            Widget textParent = m_ProtectionText.GetParent();
            if (textParent)
            {
                textParent.Show(true);
            }
        }
        else
        {
            Print("[CYX_ENHANCE] ProtectionStoneText NOT found!");
        }
        m_EnhanceButton = ButtonWidget.Cast(m_Root.FindAnyWidget("EnhanceButton"));
        m_CloseButton = ButtonWidget.Cast(m_Root.FindAnyWidget("CloseButtonEnhance"));
        m_RefineButton = ButtonWidget.Cast(m_Root.FindAnyWidget("RefineButton"));
        
        // 确保洗练按钮被找到并显示
        if (m_RefineButton)
        {
            Print("[CYX_ENHANCE] RefineButton found");
            // 初始状态根据配置决定是否显示，但确保控件存在
            Widget buttonParent = m_RefineButton.GetParent();
            while (buttonParent)
            {
                buttonParent.Show(true);
                buttonParent = buttonParent.GetParent();
            }
        }
        else
        {
            Print("[CYX_ENHANCE] RefineButton NOT found!");
        }

        HideLegacyPlaceholders();
        
        Print("[CYX_ENHANCE] Init() completed, returning root widget");
        UpdateState(true);
        return m_Root;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);

        // 检查根窗口是否存在，如果不存在说明菜单已被关闭
        if (!m_Root)
        {
            Print("[CYX_ENHANCE] WARNING: m_Root is null in Update()");
            return;
        }

        // 确保根窗口和主要容器始终显示
        m_Root.Show(true);
        
        // 确保背景和主面板始终显示
        Widget enhanceBackground = m_Root.FindAnyWidget("EnhanceBackground");
        if (enhanceBackground)
        {
            enhanceBackground.Show(true);
        }
        else
        {
            Print("[CYX_ENHANCE] WARNING: EnhanceBackground not found in Update()");
        }
        
        Widget mainPanel = m_Root.FindAnyWidget("MainPanel");
        if (mainPanel)
        {
            mainPanel.Show(true);
        }
        else
        {
            Print("[CYX_ENHANCE] WARNING: MainPanel not found in Update()");
        }

        if (HandleEscapeInput())
        {
            return;
        }

        m_UpdateTimer += timeslice;
        if (m_UpdateTimer >= UPDATE_INTERVAL)
        {
            m_UpdateTimer = 0.0;
            UpdateState(false);
        }
    }

    private void HideLegacyPlaceholders()
    {
        array<string> placeholders = {
            "MaterialStoneText",
            "MaterialNailsText",
            "MaterialAppleText",
            "UseProtectionText",
            "RefineMaterialStoneText",
            "RefineMaterialNailsText",
            "RefineMaterialAppleText"
        };

        foreach (string name : placeholders)
        {
            Widget widget = m_Root.FindAnyWidget(name);
            if (widget)
            {
                widget.Show(false);
            }
        }
    }

    private void UpdateState(bool forceRequest)
    {
        if (!m_Root)
        {
            Print("[CYX_ENHANCE] WARNING: UpdateState called but m_Root is null");
            return;
        }
        
        // 确保根窗口和主容器始终显示
        m_Root.Show(true);
        Widget enhanceBackground = m_Root.FindAnyWidget("EnhanceBackground");
        if (enhanceBackground)
        {
            enhanceBackground.Show(true);
        }
        Widget mainPanel = m_Root.FindAnyWidget("MainPanel");
        if (mainPanel)
        {
            mainPanel.Show(true);
        }
        
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            Print("[CYX_ENHANCE] WARNING: UpdateState called but player is null");
            return;
        }

        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
        if (!itemInHands)
        {
            ShowNoItemState();
            return;
        }

        string itemType = itemInHands.GetType();
        if (m_ItemNameText)
        {
            m_ItemNameText.SetText(itemInHands.GetDisplayName());
        }

        if (m_ItemDisplayHint)
        {
            m_ItemDisplayHint.Show(false);
        }

        if (m_ItemPreview)
        {
            m_ItemPreview.SetItem(itemInHands);
            m_ItemPreview.Show(true);
        }

        bool requiresRequest = (itemType != m_LastItemType) || forceRequest;
        if (requiresRequest && !m_RequestInFlight)
        {
            RequestItemInfo(itemType);
        }

        if (m_CurrentInfo && m_CurrentInfo.ItemType == itemType)
        {
            RenderInfo(player);
        }
        else
        {
            ShowLoadingState();
        }
    }

    private void ShowNoItemState()
    {
        m_CurrentInfo = null;
        m_LastItemType = "";
        m_RequestInFlight = false;

        if (m_ItemPreview)
        {
            m_ItemPreview.SetItem(null);
        }

        if (m_ItemNameText)
        {
            m_ItemNameText.SetText("");
        }

        if (m_ItemDisplayHint)
        {
            m_ItemDisplayHint.SetText("请手持需要强化的物品");
            m_ItemDisplayHint.Show(true);
        }

        if (m_SuccessRateText)
        {
            m_SuccessRateText.SetText("强化成功概率: -");
        }

        if (m_RefineInfoText)
        {
            m_RefineInfoText.SetText("当前洗练: 未洗练");
            m_RefineInfoText.SetColor(ARGB(255, 255, 0, 0)); // 红色
        }

        ClearMaterialRows();
        ClearRefineMaterialRows();

        // 隐藏洗练相关控件
        if (m_RefineMaterialsTitleText)
        {
            m_RefineMaterialsTitleText.Show(false);
        }
        if (m_RefineMaterialsList)
        {
            m_RefineMaterialsList.Show(false);
        }
        if (m_RefineButton)
        {
            m_RefineButton.Show(false);
        }

        // 保持控件显示，只重置状态
        if (m_ProtectionText)
        {
            m_ProtectionText.SetText("保护石: 0/0");
            m_ProtectionText.SetColor(ARGB(255, 200, 200, 200));
            m_ProtectionText.Show(true);
        }
        if (m_UseProtectionCheckbox)
        {
            m_UseProtectionCheckbox.SetChecked(false);
            m_UseProtectionCheckbox.Show(true);
        }
    }

    private void ShowLoadingState()
    {
        if (m_SuccessRateText)
        {
            m_SuccessRateText.SetText("强化成功概率: 正在加载配置...");
        }

        if (m_WarningText)
        {
            m_WarningText.SetText("");
        }
    }

    private void RenderInfo(PlayerBase player)
    {
        if (!m_CurrentInfo)
        {
            return;
        }

        int percent = Math.Round(m_CurrentInfo.SuccessRate * 100);
        if (m_SuccessRateText)
        {
            m_SuccessRateText.SetText("强化成功概率: " + percent.ToString() + "%");
        }

        // 更新洗练信息显示
        if (m_RefineInfoText)
        {
            if (m_CurrentInfo.RefineMultiplier != 1.0)
            {
                int multiplierPercent = Math.Round(m_CurrentInfo.RefineMultiplier * 100);
                string refineText = "当前洗练: " + multiplierPercent.ToString() + "%";
                m_RefineInfoText.SetText(refineText);
                // 根据倍率设置颜色：小于100%为红色，大于100%为绿色，等于100%为黄色
                if (m_CurrentInfo.RefineMultiplier < 1.0)
                {
                    m_RefineInfoText.SetColor(ARGB(255, 255, 0, 0)); // 红色
                }
                else if (m_CurrentInfo.RefineMultiplier > 1.0)
                {
                    m_RefineInfoText.SetColor(ARGB(255, 0, 255, 0)); // 绿色
                }
                else
                {
                    m_RefineInfoText.SetColor(ARGB(255, 255, 255, 0)); // 黄色
                }
            }
            else
            {
                m_RefineInfoText.SetText("当前洗练: 未洗练");
                m_RefineInfoText.SetColor(ARGB(255, 255, 0, 0)); // 红色
            }
        }

        UpdateMaterialRows(player);
        UpdateProtectionRow(player);
        UpdateRefineMaterials(player);
        UpdateRefineButton();

        if (m_WarningText)
        {
            m_WarningText.SetText("");
        }
    }

    private void UpdateRefineMaterials(PlayerBase player)
    {
        // 清除旧的洗练材料列表
        ClearRefineMaterialRows();

        // 检查是否有洗练材料数据
        bool hasRefineMaterials = (m_CurrentInfo && m_CurrentInfo.RefineRequiredMaterials && m_CurrentInfo.RefineRequiredMaterials.Count() > 0);
        bool canRefine = (m_CurrentInfo && m_CurrentInfo.CanRefine);
        
        // 调试日志
        string debugInfo = "UpdateRefineMaterials: ";
        if (m_CurrentInfo)
        {
            debugInfo += "CanRefine=" + canRefine + " ";
            if (m_CurrentInfo.RefineRequiredMaterials)
            {
                debugInfo += "RefineMaterialsCount=" + m_CurrentInfo.RefineRequiredMaterials.Count() + " ";
            }
            else
            {
                debugInfo += "RefineMaterials=null ";
            }
        }
        else
        {
            debugInfo += "m_CurrentInfo=null ";
        }
        debugInfo += "hasRefineMaterials=" + hasRefineMaterials;
        Print("[CYX_ENHANCE] " + debugInfo);
        
        string parentName; // 声明变量，在函数内复用
        
        // 显示/隐藏洗练材料标题（只要有材料数据就显示）
        if (m_RefineMaterialsTitleText)
        {
            m_RefineMaterialsTitleText.Show(hasRefineMaterials);
            Print("[CYX_ENHANCE] RefineMaterialsTitleText.Show(" + hasRefineMaterials + ")");
            // 确保标题的父容器始终显示
            Widget titleParent = m_RefineMaterialsTitleText.GetParent();
            while (titleParent)
            {
                titleParent.Show(true);
                parentName = titleParent.GetName();
                if (parentName == "MainPanel" || parentName == "EnhanceBackground" || titleParent == m_Root)
                {
                    break; // 不要继续向上
                }
                titleParent = titleParent.GetParent();
            }
        }
        
        // 显示/隐藏洗练材料列表（只要有材料数据就显示，不管CanRefine）
        if (m_RefineMaterialsList)
        {
            m_RefineMaterialsList.Show(hasRefineMaterials);
            Print("[CYX_ENHANCE] RefineMaterialsList.Show(" + hasRefineMaterials + ")");
            // 确保所有父容器都显示（不要隐藏父容器，只隐藏列表本身）
            Widget refineListParent = m_RefineMaterialsList.GetParent();
            while (refineListParent)
            {
                // 检查是否是主面板或根窗口，如果是则始终显示
                parentName = refineListParent.GetName();
                if (parentName == "MainPanel" || parentName == "EnhanceBackground" || refineListParent == m_Root)
                {
                    refineListParent.Show(true);
                    break; // 不要继续向上隐藏
                }
                // 对于其他父容器，确保它们显示（但不根据hasRefineMaterials隐藏）
                refineListParent.Show(true);
                refineListParent = refineListParent.GetParent();
            }
        }

        // 如果没有材料数据或列表容器不存在，直接返回
        if (!hasRefineMaterials || !m_RefineMaterialsList)
        {
            Print("[CYX_ENHANCE] UpdateRefineMaterials: early return - hasRefineMaterials=" + hasRefineMaterials + " listExists=" + (m_RefineMaterialsList != null));
            return;
        }

        // 显示洗练材料
        int rowIndex = 0;
        foreach (EnhanceMaterial material : m_CurrentInfo.RefineRequiredMaterials)
        {
            if (!material)
            {
                continue;
            }

            string displayName = material.MaterialType;
            if (material.DisplayName != "")
            {
                displayName = material.DisplayName;
            }
            int have = CountPlayerItem(player, material.MaterialType);
            bool enough = have >= material.Quantity;
            string line = displayName + ": " + have.ToString() + "/" + material.Quantity.ToString();
            
            Print("[CYX_ENHANCE] Adding refine material row[" + rowIndex + "]: " + line);
            AddRefineMaterialRow(line, enough, rowIndex);
            rowIndex++;
        }
    }

    private void ClearRefineMaterialRows()
    {
        if (!m_RefineMaterialsList)
        {
            return;
        }

        Widget child = m_RefineMaterialsList.GetChildren();
        while (child)
        {
            // 跳过静态的占位符控件（RefineMaterialStoneText等）
            string name = child.GetName();
            if (name != "RefineMaterialStoneText" && name != "RefineMaterialNailsText" && name != "RefineMaterialAppleText")
            {
                Widget next = child.GetSibling();
                child.Unlink();
                delete child;
                child = next;
            }
            else
            {
                child = child.GetSibling();
            }
        }
    }

    private void AddRefineMaterialRow(string text, bool enough, int rowIndex)
    {
        if (!m_RefineMaterialsList)
        {
            Print("[CYX_ENHANCE] AddRefineMaterialRow: m_RefineMaterialsList is null");
            return;
        }

        TextWidget line = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets("cyx_qianghua/gui/material_entry.layout", m_RefineMaterialsList));
        if (!line)
        {
            Print("[CYX_ENHANCE] Failed to create refine material row widget layout for: " + text);
            return;
        }

        Print("[CYX_ENHANCE] Created refine material row widget: " + text);
        
        // 设置每个材料项的 Y 位置（每个材料项高度 32 像素）
        int yPos = rowIndex * 32;
        line.SetPos(0, yPos);
        
        line.SetText(text);
        int color = ARGB(255, 255, 130, 130);
        if (enough)
        {
            color = ARGB(255, 120, 255, 120);
        }
        line.SetColor(color);
        
        // 确保 widget 可见
        line.Show(true);
        
        // 确保父容器可见
        Widget lineParent = line.GetParent();
        while (lineParent)
        {
            lineParent.Show(true);
            lineParent = lineParent.GetParent();
        }
        
        Print("[CYX_ENHANCE] Refine material row added and shown: " + text + " at y=" + yPos);
    }

    private void UpdateRefineButton()
    {
        if (!m_RefineButton)
        {
            return;
        }

        // 显示洗练按钮（如果武器可以洗练）
        if (m_CurrentInfo && m_CurrentInfo.CanRefine)
        {
            m_RefineButton.Show(true);
            Print("[CYX_ENHANCE] RefineButton shown (CanRefine=true)");
        }
        else
        {
            m_RefineButton.Show(false);
            if (m_CurrentInfo)
            {
                Print("[CYX_ENHANCE] RefineButton hidden (CanRefine=false)");
            }
            else
            {
                Print("[CYX_ENHANCE] RefineButton hidden (m_CurrentInfo is null)");
            }
        }
    }

    private void RequestItemInfo(string itemType)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }

        Print("[CYX_ENHANCE] RequestItemInfo for type=" + itemType);
        m_LastItemType = itemType;
        m_CurrentInfo = null;
        m_RequestInFlight = true;

        Param1<string> payload = new Param1<string>(itemType);
        player.RPCSingleParam(EnhanceRPC.RPC_ITEM_INFO_REQUEST, payload, true, null);
    }

    private void UpdateMaterialRows(PlayerBase player)
    {
        ClearMaterialRows();

        if (!m_CurrentInfo || !m_CurrentInfo.RequiredMaterials || !m_MaterialsList)
        {
            string infoText = "false";
            if (m_CurrentInfo != null)
            {
                infoText = "true";
            }
            string materialsText = "false";
            if (m_CurrentInfo && m_CurrentInfo.RequiredMaterials != null)
            {
                materialsText = "true";
            }
            string listText = "false";
            if (m_MaterialsList != null)
            {
                listText = "true";
            }
            Print("[CYX_ENHANCE] UpdateMaterialRows: missing data - info=" + infoText + " materials=" + materialsText + " list=" + listText);
            return;
        }

        Print("[CYX_ENHANCE] UpdateMaterialRows: processing " + m_CurrentInfo.RequiredMaterials.Count() + " materials");

        bool hasRows = false;
        int processedCount = 0;
        int skippedCount = 0;
        int rowIndex = 0; // 用于设置每个材料项的 Y 位置
        
        // 先遍历普通材料（不包括保护石）
        int materialIndex = 0;
        foreach (EnhanceMaterial material : m_CurrentInfo.RequiredMaterials)
        {
            materialIndex++;
            if (!material)
            {
                Print("[CYX_ENHANCE] UpdateMaterialRows: null material encountered at index " + materialIndex);
                continue;
            }

            Print("[CYX_ENHANCE] UpdateMaterialRows: checking material[" + materialIndex + "] type=" + material.MaterialType + " displayName=" + material.DisplayName);

            // 跳过保护石（保护石会单独添加）
            if (m_CurrentInfo.HasProtectionOption && m_CurrentInfo.ProtectionCardItem != "" && material.MaterialType == m_CurrentInfo.ProtectionCardItem)
            {
                Print("[CYX_ENHANCE] UpdateMaterialRows: skipping protection stone in RequiredMaterials (will add separately)");
                skippedCount++;
                continue;
            }

            processedCount++;
            Print("[CYX_ENHANCE] UpdateMaterialRows: processing material[" + processedCount + "] type=" + material.MaterialType + " displayName=" + material.DisplayName);

            string displayName = material.MaterialType;
            if (material.DisplayName != "")
            {
                displayName = material.DisplayName;
            }
            int have = CountPlayerItem(player, material.MaterialType);
            bool enough = have >= material.Quantity;
            string line = displayName + ": " + have.ToString() + "/" + material.Quantity.ToString();
            
            Print("[CYX_ENHANCE] Adding material row[" + rowIndex + "]: " + line + " (enough=" + enough + ", have=" + have + ", required=" + material.Quantity + ")");
            AddMaterialRow(line, enough, rowIndex);
            rowIndex++;
            hasRows = true;
        }

        // 单独添加保护石（如果存在且不在 RequiredMaterials 中）
        if (m_CurrentInfo.HasProtectionOption && m_CurrentInfo.ProtectionCardItem != "" && m_CurrentInfo.ProtectionCardQuantity > 0)
        {
            int haveProtection = CountPlayerItem(player, m_CurrentInfo.ProtectionCardItem);
            bool enoughProtection = haveProtection >= m_CurrentInfo.ProtectionCardQuantity;
            string protectionDisplayName = m_CurrentInfo.ProtectionCardName;
            if (protectionDisplayName == "")
            {
                protectionDisplayName = m_CurrentInfo.ProtectionCardItem;
            }
            string protectionLine = protectionDisplayName + ": " + haveProtection.ToString() + "/" + m_CurrentInfo.ProtectionCardQuantity.ToString();
            
            Print("[CYX_ENHANCE] Adding protection stone material row[" + rowIndex + "] with checkbox: " + protectionLine);
            AddMaterialRowWithCheckbox(protectionLine, enoughProtection, rowIndex);
            rowIndex++;
            hasRows = true;
        }

        string displayedText = "no";
        if (hasRows)
        {
            displayedText = "yes";
        }
        Print("[CYX_ENHANCE] UpdateMaterialRows: processed=" + processedCount + " skipped=" + skippedCount + " displayed=" + displayedText);
        
        // 确保材料列表容器始终显示
        if (m_MaterialsList)
        {
            m_MaterialsList.Show(true);
            // 确保所有父容器都显示
            Widget parent = m_MaterialsList.GetParent();
            while (parent)
            {
                parent.Show(true);
                parent = parent.GetParent();
            }
            
            // 强制更新布局（确保所有子元素正确显示）
            m_MaterialsList.Update();
        }
        
        // 注意：洗练材料的显示由 UpdateRefineMaterials() 统一处理，这里不再重复处理
        
        // 统计实际显示的子元素数量，并打印每个子元素的详细信息
        if (m_MaterialsList)
        {
            int childCount = 0;
            Widget child = m_MaterialsList.GetChildren();
            while (child)
            {
                childCount++;
                float x, y, w, h;
                child.GetPos(x, y);
                child.GetSize(w, h);
                bool visible = child.IsVisible();
                Print("[CYX_ENHANCE] MaterialsList child[" + childCount + "]: pos=(" + x + "," + y + ") size=(" + w + "," + h + ") visible=" + visible);
                child = child.GetSibling();
            }
            Print("[CYX_ENHANCE] MaterialsList has " + childCount.ToString() + " children after update");
        }
    }

    private void UpdateProtectionRow(PlayerBase player)
    {
        // 检查保护石是否在材料列表中显示（通过检查是否有材料列表中的保护石复选框）
        bool protectionInMaterialsList = (m_MaterialListProtectionCheckbox != null);
        
        // 如果保护石在材料列表中显示，隐藏 ProtectionContainer
        Widget protectionContainer = m_Root.FindAnyWidget("ProtectionContainer");
        if (protectionContainer)
        {
            if (protectionInMaterialsList)
            {
                // 保护石在材料列表中显示，隐藏单独的 ProtectionContainer
                protectionContainer.Show(false);
            }
            else
            {
                // 保护石不在材料列表中，显示 ProtectionContainer
                protectionContainer.Show(true);
                // 确保所有父容器都显示
                Widget parent = protectionContainer.GetParent();
                while (parent)
                {
                    parent.Show(true);
                    parent = parent.GetParent();
                }
            }
        }
        
        // 如果保护石不在材料列表中，更新 ProtectionContainer 中的显示
        if (!protectionInMaterialsList)
        {
            if (!m_ProtectionText || !m_UseProtectionCheckbox)
            {
                Print("[CYX_ENHANCE] UpdateProtectionRow: widgets missing");
                return;
            }

            // 始终显示控件
            m_ProtectionText.Show(true);
            m_UseProtectionCheckbox.Show(true);
            
            Widget checkboxParent = m_UseProtectionCheckbox.GetParent();
            if (checkboxParent)
            {
                checkboxParent.Show(true);
            }
            
            Widget textParent = m_ProtectionText.GetParent();
            if (textParent)
            {
                textParent.Show(true);
            }

            // 如果有配置信息，更新文本和状态
            if (m_CurrentInfo && m_CurrentInfo.HasProtectionOption && m_CurrentInfo.ProtectionCardItem != "" && m_CurrentInfo.ProtectionCardQuantity > 0)
            {
                int have = CountPlayerItem(player, m_CurrentInfo.ProtectionCardItem);
                bool enough = have >= m_CurrentInfo.ProtectionCardQuantity;
                string displayName = m_CurrentInfo.ProtectionCardName;
                if (displayName == "")
                {
                    displayName = m_CurrentInfo.ProtectionCardItem;
                }

                string text = displayName + ": " + have.ToString() + "/" + m_CurrentInfo.ProtectionCardQuantity.ToString();
                m_ProtectionText.SetText(text);
                int color = ARGB(255, 255, 130, 130);
                if (enough)
                {
                    color = ARGB(255, 120, 255, 120);
                }
                m_ProtectionText.SetColor(color);
                m_UseProtectionCheckbox.Enable(enough);
            }
            else
            {
                // 没有配置时显示默认文本
                m_ProtectionText.SetText("保护石: 0/0");
                m_ProtectionText.SetColor(ARGB(255, 200, 200, 200));
                m_UseProtectionCheckbox.Enable(false);
            }
        }
    }

    private void ClearMaterialRows()
    {
        if (!m_MaterialsList)
        {
            return;
        }

        // 清除材料列表中的保护石复选框引用
        m_MaterialListProtectionCheckbox = null;

        Widget child = m_MaterialsList.GetChildren();
        while (child)
        {
            Widget next = child.GetSibling();
            child.Unlink();
            delete child;
            child = next;
        }
    }

    private void AddMaterialRow(string text, bool enough, int rowIndex)
    {
        if (!m_MaterialsList)
        {
            Print("[CYX_ENHANCE] AddMaterialRow: m_MaterialsList is null");
            return;
        }

        TextWidget line = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets("cyx_qianghua/gui/material_entry.layout", m_MaterialsList));
        if (!line)
        {
            Print("[CYX_ENHANCE] Failed to create material row widget layout for: " + text);
            return;
        }

        Print("[CYX_ENHANCE] Created material row widget: " + text + ", ptr=" + line.ToString());
        
        // 获取当前 widget 的位置和大小信息
        float currentX, currentY, currentW, currentH;
        line.GetPos(currentX, currentY);
        line.GetSize(currentW, currentH);
        Print("[CYX_ENHANCE] Material row initial position: (" + currentX + "," + currentY + ") size: (" + currentW + "," + currentH + ")");
        
        // 设置每个材料项的 Y 位置（每个材料项高度 32 像素）
        int yPos = rowIndex * 32;
        line.SetPos(0, yPos);
        
        // 验证位置是否设置成功
        line.GetPos(currentX, currentY);
        Print("[CYX_ENHANCE] Set material row position: y=" + yPos + ", verified position: (" + currentX + "," + currentY + ")");
        
        line.SetText(text);
        int color = ARGB(255, 255, 130, 130);
        if (enough)
        {
            color = ARGB(255, 120, 255, 120);
        }
        line.SetColor(color);
        
        // 确保 widget 可见
        line.Show(true);
        
        // 确保父容器可见
        Widget parent = line.GetParent();
        while (parent)
        {
            parent.Show(true);
            parent = parent.GetParent();
        }
        
        Print("[CYX_ENHANCE] Material row added and shown: " + text + " at y=" + yPos);
    }

    private void AddMaterialRowWithCheckbox(string text, bool enough, int rowIndex)
    {
        if (!m_MaterialsList)
        {
            return;
        }

        Widget rowWidget = GetGame().GetWorkspace().CreateWidgets("cyx_qianghua/gui/material_entry_with_checkbox.layout", m_MaterialsList);
        if (!rowWidget)
        {
            Print("[CYX_ENHANCE] Failed to create material row with checkbox widget layout for: " + text);
            return;
        }

        // 获取当前 widget 的位置和大小信息
        float currentX, currentY, currentW, currentH;
        rowWidget.GetPos(currentX, currentY);
        rowWidget.GetSize(currentW, currentH);
        Print("[CYX_ENHANCE] Material row with checkbox initial position: (" + currentX + "," + currentY + ") size: (" + currentW + "," + currentH + ")");
        
        // 设置每个材料项的 Y 位置（每个材料项高度 32 像素）
        int yPos = rowIndex * 32;
        rowWidget.SetPos(0, yPos);
        
        // 验证位置是否设置成功
        rowWidget.GetPos(currentX, currentY);
        Print("[CYX_ENHANCE] Set material row with checkbox position: y=" + yPos + ", verified position: (" + currentX + "," + currentY + ")");

        TextWidget line = TextWidget.Cast(rowWidget.FindAnyWidget("MaterialText"));
        CheckBoxWidget checkbox = CheckBoxWidget.Cast(rowWidget.FindAnyWidget("MaterialCheckbox"));
        
        if (line)
        {
            line.SetText(text);
            int color = ARGB(255, 255, 130, 130);
            if (enough)
            {
                color = ARGB(255, 120, 255, 120);
            }
            line.SetColor(color);
        }
        
        if (checkbox)
        {
            // 保存材料列表中的保护石复选框引用
            m_MaterialListProtectionCheckbox = checkbox;
            
            // 关联到保护石复选框，同步初始状态
            if (m_UseProtectionCheckbox)
            {
                checkbox.SetChecked(m_UseProtectionCheckbox.IsChecked());
            }
            else
            {
                checkbox.SetChecked(false);
            }
            checkbox.Enable(enough);
        }
        
        Print("[CYX_ENHANCE] Created material row with checkbox widget: " + text);
    }

    private int CountPlayerItem(PlayerBase player, string typeName)
    {
        if (!player || typeName == "")
        {
            return 0;
        }

        int total = 0;
        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (!item || !item.IsKindOf(typeName))
            {
                continue;
            }

            ItemBase baseItem = ItemBase.Cast(item);
            if (baseItem && baseItem.HasQuantity())
            {
                total += baseItem.GetQuantity();
            }
            else
            {
                total += 1;
            }
        }

        return total;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_EnhanceButton && button == MouseState.LEFT)
        {
            StartEnhance();
            return true;
        }

        if (w == m_RefineButton && button == MouseState.LEFT)
        {
            StartRefine();
            return true;
        }

        if (w == m_CloseButton && button == MouseState.LEFT)
        {
            CloseMenu();
            return true;
        }

        return super.OnClick(w, x, y, button);
    }

    override bool OnKeyDown(Widget w, int x, int y, int key)
    {
        if (key == KeyCode.KC_ESCAPE)
        {
            CloseMenu();
            return true;
        }

        return super.OnKeyDown(w, x, y, key);
    }

    private bool HandleEscapeInput()
    {
        Input input = GetGame().GetInput();
        if (input && input.LocalPress("UAUIBack", false))
        {
            CloseMenu();
            return true;
        }

        return false;
    }

    void CloseMenu()
    {
        Print("[CYX_ENHANCE] CloseMenu() called");
        
        // 恢复游戏状态
        if (GetGame() && GetGame().GetMission())
        {
            GetGame().GetMission().PlayerControlEnable(true);
            GetGame().GetMission().GetHud().Show(true);
        }
        
        // 关闭菜单 - 使用 UIManager 的 Back 方法
        UIManager ui = GetGame().GetUIManager();
        if (ui && ui.GetMenu() == this)
        {
            ui.Back();
        }
        
        // 清理静态引用
        s_ActiveMenu = null;
    }

    private void StartEnhance()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !m_CurrentInfo)
        {
            return;
        }

        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
        if (!itemInHands || itemInHands.GetType() != m_CurrentInfo.ItemType)
        {
            player.MessageImportant("❌ 请手持要强化的物品");
            return;
        }

        // 优先使用材料列表中的保护石复选框，如果没有则使用 ProtectionContainer 中的复选框
        bool useProtection = false;
        if (m_MaterialListProtectionCheckbox)
        {
            useProtection = m_MaterialListProtectionCheckbox.IsChecked();
        }
        else if (m_UseProtectionCheckbox)
        {
            useProtection = m_UseProtectionCheckbox.IsChecked();
        }
        Param2<string, bool> payload = new Param2<string, bool>(m_CurrentInfo.ItemType, useProtection);
        player.RPCSingleParam(EnhanceRPC.RPC_ENHANCE_REQUEST, payload, true, null);
        player.MessageImportant("正在强化中...");
    }

    private void StartRefine()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !m_CurrentInfo)
        {
            return;
        }

        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
        if (!itemInHands || itemInHands.GetType() != m_CurrentInfo.ItemType)
        {
            player.MessageImportant("❌ 请手持要洗练的武器");
            return;
        }

        Param1<string> payload = new Param1<string>(m_CurrentInfo.ItemType);
        player.RPCSingleParam(EnhanceRPC.RPC_REFINE_REQUEST, payload, true, null);
        player.MessageImportant("正在洗练中...");
    }

    static void HandleInfoResponse(EnhanceDisplayInfo info)
    {
        if (s_ActiveMenu)
        {
            s_ActiveMenu.OnInfoResponse(info);
        }
    }

    static void HandleEnhanceResult(bool success, string message)
    {
        if (s_ActiveMenu)
        {
            s_ActiveMenu.OnEnhanceResult(success, message);
        }
    }

    void OnInfoResponseRPC(Param1<ref EnhanceDisplayInfo> ctx)
    {
        if (!ctx || !ctx.param1)
        {
            return;
        }

        OnInfoResponse(ctx.param1);
    }

    void OnEnhanceResultRPC(Param2<bool, string> ctx)
    {
        if (!ctx)
        {
            return;
        }

        OnEnhanceResult(ctx.param1, ctx.param2);
    }

    private void OnInfoResponse(EnhanceDisplayInfo info)
    {
        m_RequestInFlight = false;
        string typeName = "<null>";
        string hasDataText = "false";
        if (info)
        {
            typeName = info.ItemType;
            if (info.HasData)
            {
                hasDataText = "true";
            }
        }
        Print("[CYX_ENHANCE] OnInfoResponse item=" + typeName + " hasData=" + hasDataText);
        if (!info || !info.HasData)
        {
            m_CurrentInfo = null;
            if (m_WarningText)
            {
                string warning = "❌ 未找到该物品的配置";
                if (info && info.ErrorMessage != "")
                {
                    warning = info.ErrorMessage;
                }
                m_WarningText.SetText(warning);
            }
            return;
        }

        // 调试：打印接收到的材料信息
        int materialsCount = 0;
        if (info.RequiredMaterials)
        {
            materialsCount = info.RequiredMaterials.Count();
        }
        Print("[CYX_ENHANCE] Received materials count: " + materialsCount.ToString());
        if (info.RequiredMaterials)
        {
            for (int i = 0; i < info.RequiredMaterials.Count(); i++)
            {
                EnhanceMaterial mat = info.RequiredMaterials.Get(i);
                if (mat)
                {
                    Print("[CYX_ENHANCE] Material[" + i.ToString() + "]: type=" + mat.MaterialType + " qty=" + mat.Quantity.ToString() + " display=" + mat.DisplayName);
                }
            }
        }
        string protectionOptionText = "false";
        if (info.HasProtectionOption)
        {
            protectionOptionText = "true";
        }
        Print("[CYX_ENHANCE] HasProtectionOption=" + protectionOptionText + " ProtectionCardItem=" + info.ProtectionCardItem);

        // 调试：打印接收到的洗练材料信息
        string canRefineText = "false";
        if (info.CanRefine)
        {
            canRefineText = "true";
        }
        Print("[CYX_ENHANCE] CanRefine=" + canRefineText);
        int refineMaterialsCount = 0;
        if (info.RefineRequiredMaterials)
        {
            refineMaterialsCount = info.RefineRequiredMaterials.Count();
        }
        Print("[CYX_ENHANCE] Received refine materials count: " + refineMaterialsCount.ToString());
        if (info.RefineRequiredMaterials)
        {
            for (int j = 0; j < info.RefineRequiredMaterials.Count(); j++)
            {
                EnhanceMaterial refineMat = info.RefineRequiredMaterials.Get(j);
                if (refineMat)
                {
                    Print("[CYX_ENHANCE] RefineMaterial[" + j.ToString() + "]: type=" + refineMat.MaterialType + " qty=" + refineMat.Quantity.ToString() + " display=" + refineMat.DisplayName);
                }
            }
        }
        else
        {
            Print("[CYX_ENHANCE] RefineRequiredMaterials is null");
        }

        m_CurrentInfo = info;
    }

    private void OnEnhanceResult(bool success, string message)
    {
        // Force refresh materials after result.
        m_CurrentInfo = null;
        m_RequestInFlight = false;
        UpdateState(true);
    }
}


