modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
		//actions.Insert(ActionMineBuilding);
		actions.Insert(ActionDeployObject);
		actions.Insert(ActionTurnOnOffFurnace);
    }
}