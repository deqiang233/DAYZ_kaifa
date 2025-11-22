class CfgPatches
{
    class CYX_qianghua
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
    class CYX_qianghua
    {
        dir = "CYX_qianghua";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "CYX_qianghua";
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
                files[] = {"CYX_qianghua/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"CYX_qianghua/Scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"CYX_qianghua/Scripts/5_Mission"};
            };
        };
    };
};
