#ifndef CYX_ENHANCE_DATA_DEFINED
#define CYX_ENHANCE_DATA_DEFINED

// Shared data structures used by the server-side enhance logic.

class EnhanceMaterial
{
    string MaterialType;
    int Quantity;
    string DisplayName;

    void EnhanceMaterial(string type = "", int qty = 0, string name = "")
    {
        MaterialType = type;
        Quantity = qty;
        DisplayName = name;
    }

    bool ReadFromContext(ParamsReadContext ctx, int version)
    {
        if (!ctx.Read(MaterialType)) return false;
        if (!ctx.Read(Quantity)) return false;
        if (!ctx.Read(DisplayName)) return false;
        return true;
    }

    bool WriteToContext(ParamsWriteContext ctx)
    {
        if (!ctx.Write(MaterialType)) return false;
        if (!ctx.Write(Quantity)) return false;
        if (!ctx.Write(DisplayName)) return false;
        return true;
    }
}

class EnhanceResultItem
{
    string ItemType;
    int Quantity;

    void EnhanceResultItem(string type = "", int qty = 1)
    {
        ItemType = type;
        Quantity = qty;
    }

    bool ReadFromContext(ParamsReadContext ctx, int version)
    {
        if (!ctx.Read(ItemType)) return false;
        if (!ctx.Read(Quantity)) return false;
        return true;
    }

    bool WriteToContext(ParamsWriteContext ctx)
    {
        if (!ctx.Write(ItemType)) return false;
        if (!ctx.Write(Quantity)) return false;
        return true;
    }
}

class EnhanceDisplayInfo
{
    string ItemType;
    string DisplayName;
    float SuccessRate;
    bool HasData;
    string ErrorMessage;
    bool HasProtectionOption;
    string ProtectionCardItem;
    string ProtectionCardName;
    int ProtectionCardQuantity;
    ref array<ref EnhanceMaterial> RequiredMaterials;

    void EnhanceDisplayInfo()
    {
        RequiredMaterials = new array<ref EnhanceMaterial>();
        HasProtectionOption = false;
        ProtectionCardQuantity = 0;
        HasData = false;
        ErrorMessage = "";
    }

    bool ReadFromContext(ParamsReadContext ctx, int version)
    {
        if (!ctx.Read(ItemType)) return false;
        if (!ctx.Read(DisplayName)) return false;
        if (!ctx.Read(SuccessRate)) return false;
        if (!ctx.Read(HasProtectionOption)) return false;
        if (!ctx.Read(ProtectionCardItem)) return false;
        if (!ctx.Read(ProtectionCardName)) return false;
        if (!ctx.Read(ProtectionCardQuantity)) return false;
        if (!ctx.Read(RequiredMaterials)) return false;
        if (!ctx.Read(HasData)) return false;
        if (!ctx.Read(ErrorMessage)) return false;
        return true;
    }

    bool WriteToContext(ParamsWriteContext ctx)
    {
        if (!ctx.Write(ItemType)) return false;
        if (!ctx.Write(DisplayName)) return false;
        if (!ctx.Write(SuccessRate)) return false;
        if (!ctx.Write(HasProtectionOption)) return false;
        if (!ctx.Write(ProtectionCardItem)) return false;
        if (!ctx.Write(ProtectionCardName)) return false;
        if (!ctx.Write(ProtectionCardQuantity)) return false;
        if (!ctx.Write(RequiredMaterials)) return false;
        if (!ctx.Write(HasData)) return false;
        if (!ctx.Write(ErrorMessage)) return false;
        return true;
    }
}

#endif // CYX_ENHANCE_DATA_DEFINED

