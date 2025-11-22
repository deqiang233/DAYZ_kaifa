class EnhanceMenu extends UIScriptedMenu
{
    private static EnhanceMenu s_ActiveMenu;

    private Widget m_Root;
    private ItemPreviewWidget m_ItemPreview;
    private TextWidget m_ItemNameText;
    private TextWidget m_ItemDisplayHint;
    private TextWidget m_SuccessRateText;
    private TextWidget m_WarningText;
    private Widget m_MaterialsList;
    private CheckBoxWidget m_UseProtectionCheckbox;
    private CheckBoxWidget m_MaterialListProtectionCheckbox; // 材料列表中的保护石复选框
    private TextWidget m_ProtectionText;
    private ButtonWidget m_EnhanceButton;
    private ButtonWidget m_CloseButton;

    private ref EnhanceDisplayInfo m_CurrentInfo;
    private string m_LastItemType;
    private float m_UpdateTimer;
    private bool m_RequestInFlight;

    private const float UPDATE_INTERVAL = 0.25;

    void EnhanceMenu()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetMission().GetHud().Show(false);
        s_ActiveMenu = this;
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
        m_Root = GetGame().GetWorkspace().CreateWidgets("cyx_qianghua/gui/enhance.layout");
        if (!m_Root)
        {
            return null;
        }

        m_ItemPreview = ItemPreviewWidget.Cast(m_Root.FindAnyWidget("ItemPreview"));
        m_ItemNameText = TextWidget.Cast(m_Root.FindAnyWidget("ItemNameText"));
        m_ItemDisplayHint = TextWidget.Cast(m_Root.FindAnyWidget("ItemDisplayPositionLabel"));
        m_SuccessRateText = TextWidget.Cast(m_Root.FindAnyWidget("SuccessRateText"));
        m_WarningText = TextWidget.Cast(m_Root.FindAnyWidget("WarningText"));
        m_MaterialsList = m_Root.FindAnyWidget("MaterialsList");
        if (!m_MaterialsList)
        {
            Print("[CYX_ENHANCE] MaterialsList widget not found in enhance.layout");
        }
        else
        {
            Print("[CYX_ENHANCE] MaterialsList widget ready: " + m_MaterialsList.ToString());
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

        HideLegacyPlaceholders();
        UpdateState(true);
        return m_Root;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);

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
            "RefineMaterialsListContainer",
            "RefineMaterialStoneText",
            "RefineMaterialNailsText",
            "RefineMaterialAppleText",
            "RefineMaterialsTitleText",
            "RefineButton"
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
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
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

        ClearMaterialRows();

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

        UpdateMaterialRows(player);
        UpdateProtectionRow(player);

        if (m_WarningText)
        {
            m_WarningText.SetText("");
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

        if (w == m_CloseButton && button == MouseState.LEFT)
        {
            Close();
            return true;
        }

        return super.OnClick(w, x, y, button);
    }

    override bool OnKeyDown(Widget w, int x, int y, int key)
    {
        if (key == KeyCode.KC_ESCAPE)
        {
            Close();
            return true;
        }

        return super.OnKeyDown(w, x, y, key);
    }

    private bool HandleEscapeInput()
    {
        Input input = GetGame().GetInput();
        if (input && input.LocalPress("UAUIBack", false))
        {
            Close();
            return true;
        }

        return false;
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


