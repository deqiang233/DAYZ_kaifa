class CfgPatches
{
    class CYX_qianghua_server
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
    class CYX_qianghua_server
    {
        dir = "CYX_qianghua_server";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "CYX_qianghua_server";
        credits = "CYX";
        author = "CYX";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"CYX_qianghua_server/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"CYX_qianghua_server/Scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"CYX_qianghua_server/Scripts/5_Mission"};
            };
        };
    };
};

