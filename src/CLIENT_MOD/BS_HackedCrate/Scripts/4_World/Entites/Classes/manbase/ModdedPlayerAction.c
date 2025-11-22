modded class PlayerBase extends ManBase
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionOpenBSHC);
        AddAction(ActionAccessLootBSHC); // <--- Registrar nueva acción
    }
}