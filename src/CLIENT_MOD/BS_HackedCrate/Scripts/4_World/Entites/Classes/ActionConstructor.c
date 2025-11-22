modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(ActionOpenBSHC);
        actions.Insert(ActionAccessLootBSHC); // <--- Registrar nueva acción
    }
}