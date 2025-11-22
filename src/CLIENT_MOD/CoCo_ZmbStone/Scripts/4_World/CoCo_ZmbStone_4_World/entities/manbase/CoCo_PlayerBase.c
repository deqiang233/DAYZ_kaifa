modded class PlayerBase extends DayZPlayer
{
	ref autoptr CoCo_PlayerStoneHandler m_CoCo_PlayerStoneHandler;
	
	CoCo_PlayerStoneHandler GetCoCo_PlayerStoneHandler()
	{
		if (!m_CoCo_PlayerStoneHandler)
		{
			m_CoCo_PlayerStoneHandler = new CoCo_PlayerStoneHandler();
			m_CoCo_PlayerStoneHandler.m_PlayerBase = this;
		}
		return m_CoCo_PlayerStoneHandler;
	}
	
	void SetCoCo_PlayerStoneHandler(CoCo_PlayerStoneHandler handler)
	{
		m_CoCo_PlayerStoneHandler = handler;
	}
	
	override void EOnContact(IEntity other, Contact extra)
	{
		super.EOnContact(other, extra);
		
		if (m_CoCo_PlayerStoneHandler && m_CoCo_PlayerStoneHandler.isTargetByStones > 0)
		{
			CoCo_ThrownStone theStone = CoCo_ThrownStone.Cast(other);
			if (theStone && theStone.coco_IsThrowStone == true)
			{
				m_CoCo_PlayerStoneHandler.OnStoneHit(theStone);
			}
		}
	}
	
	void ~PlayerBase()
	{
		if (m_CoCo_PlayerStoneHandler)
		{
			delete m_CoCo_PlayerStoneHandler;
		}
	}
}

