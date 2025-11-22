class ActionTurnOnOffFurnace: ActionInteractBase
{	
	string TooltipText = "#switch_on";
	void ActionTurnOnOffFurnace()
	{
	}

	override string GetText()
	{
		return TooltipText;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if(!targetObject)
			return false;
		FreezeFurnace Freezefurnace = FreezeFurnace.Cast( targetObject );		
		
		if (Freezefurnace)
		{
			if(Freezefurnace.IsFurnaceOn())
			{
				TooltipText = "#switch_off";
				return true;
			}
			
			if(!Freezefurnace.HasPropaneSetup())
			{
				return false;
			}
			
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftBase())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftIron())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftCopper())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftGold())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftSilver())
			{
				TooltipText = "#switch_on"; 
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftTin())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftSulphur())
			{
				TooltipText = "#switch_on";
				return true;
			}
			if(!Freezefurnace.IsFurnaceOn() && Freezefurnace.CanCraftUranium())
			{
				TooltipText = "#switch_on";
				return true;
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		FreezeFurnace Freezefurnace = FreezeFurnace.Cast( targetObject );
		if (Freezefurnace)
		{
			if(Freezefurnace.IsFurnaceOn())
			{
				Freezefurnace.SwitchOffServer();
				return; // Exit early after turning off
			}
			
			// Only turn on if furnace is off and has ore
			if(!Freezefurnace.IsFurnaceOn() && (Freezefurnace.CanCraftBase() || Freezefurnace.CanCraftGold() || Freezefurnace.CanCraftSilver() || Freezefurnace.CanCraftTin() || Freezefurnace.CanCraftIron() || Freezefurnace.CanCraftCopper() || Freezefurnace.CanCraftSulphur() || Freezefurnace.CanCraftUranium()))
			{
				Freezefurnace.SwitchOnServer();
			}
		}
	}
};