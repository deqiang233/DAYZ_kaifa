modded class ActionWorldCraft
{
	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);
		HandleFreezeCraftingSoundStart(action_data);
	}

	override void OnStartClient(ActionData action_data)
	{
		super.OnStartClient(action_data);
		HandleFreezeCraftingSoundStart(action_data);
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		HandleFreezeCraftingSoundStop(action_data);
	}

	override void OnEndClient(ActionData action_data)
	{
		super.OnEndClient(action_data);
		HandleFreezeCraftingSoundStop(action_data);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		HandleFreezeCraftingSoundStop(action_data);
	}

	override void OnFinishProgressClient(ActionData action_data)
	{
		super.OnFinishProgressClient(action_data);
		HandleFreezeCraftingSoundStop(action_data);
	}

	protected void HandleFreezeCraftingSoundStart(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target)
		{
			return;
		}

		Object targetObject = action_data.m_Target.GetObject();
		if (!targetObject)
		{
			return;
		}

		FreezeGrindingStone grindingStone = FreezeGrindingStone.Cast(targetObject);
		if (grindingStone)
		{
			grindingStone.SetGrinding(true);
			return;
		}

		FreezeGrindingStone_Static staticStone = FreezeGrindingStone_Static.Cast(targetObject);
		if (staticStone)
		{
			staticStone.SetGrinding(true);
			return;
		}

		FreezeAnvil anvil = FreezeAnvil.Cast(targetObject);
		if (anvil)
		{
			anvil.SetForging(true);
			return;
		}

		FreezeAnvil_Static staticAnvil = FreezeAnvil_Static.Cast(targetObject);
		if (staticAnvil)
		{
			staticAnvil.SetForging(true);
		}
	}

	protected void HandleFreezeCraftingSoundStop(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target)
		{
			return;
		}

		Object targetObject = action_data.m_Target.GetObject();
		if (!targetObject)
		{
			return;
		}

		FreezeGrindingStone grindingStone = FreezeGrindingStone.Cast(targetObject);
		if (grindingStone)
		{
			grindingStone.SetGrinding(false);
			return;
		}

		FreezeGrindingStone_Static staticStone = FreezeGrindingStone_Static.Cast(targetObject);
		if (staticStone)
		{
			staticStone.SetGrinding(false);
			return;
		}

		FreezeAnvil anvil = FreezeAnvil.Cast(targetObject);
		if (anvil)
		{
			anvil.SetForging(false);
			return;
		}

		FreezeAnvil_Static staticAnvil = FreezeAnvil_Static.Cast(targetObject);
		if (staticAnvil)
		{
			staticAnvil.SetForging(false);
		}
	}
}

