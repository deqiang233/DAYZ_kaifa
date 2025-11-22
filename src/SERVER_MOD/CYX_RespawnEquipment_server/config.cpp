class CfgPatches
{
    class CYX_RespawnEquipment_Server
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = 
        {
            "DZ_Data",
            "DZ_Scripts"
        };
    };
};

class CfgMods
{
    class CYX_RespawnEquipment_Server
    {
        dir = "CYX_RespawnEquipment_Server";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "CYX_RespawnEquipment_Server";
        credits = "CYX";
        author = "CYX";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"World"};
        
        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"CYX_RespawnEquipment_Server/Scripts/4_world"};
            };
        };
    };
};

