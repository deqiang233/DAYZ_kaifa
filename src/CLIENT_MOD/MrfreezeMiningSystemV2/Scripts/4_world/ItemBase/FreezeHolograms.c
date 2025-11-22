class FreezeAnvil_Holo extends ItemBase
{
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent)) { return false; }        
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutIntoHands(parent))
        {
            return false;
        }
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
}

class FreezeFurnace_Holo extends ItemBase
{
	override bool CanPutInCargo(EntityAI parent)
	{
		if (!super.CanPutInCargo(parent)) { return false; }
		if (GetNumberOfItems() == 0)
		{
			return false;
		}
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		if (!super.CanPutIntoHands(parent))
		{
			return false;
		}
		if (GetNumberOfItems() == 0)
		{
			return false;
		}
		return false;
	}
}

class FreezeGrindingStone_Holo extends ItemBase
{
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent)) { return false; }        
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutIntoHands(parent))
        {
            return false;
        }
        if (GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
}

