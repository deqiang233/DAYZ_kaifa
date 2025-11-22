modded class PluginManager
{
    override void Init()
    {
        RegisterPlugin("FreezeMiningConfig", true, true);
        RegisterPlugin("FreezeVanillaRockConfig", true, true);
        RegisterPlugin("FreezeSpawnManager", true, true);
        RegisterPlugin("FreezeCraftingTimesConfig", true, true);
        RegisterPlugin("LoggingUtility", false, true);
        super.Init();
    }
};
