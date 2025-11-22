modded class ZombieBase extends DayZInfected
{
	ref autoptr CoCo_ZombieStoneManager m_CoCo_ZombieStoneManager;
	private bool firstInitDoneCoCo;
	
	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		if (firstInitDoneCoCo == false)
		{
			if (GetGame().IsDedicatedServer())
			{
				m_CoCo_ZombieStoneManager = new CoCo_ZombieStoneManager();
				m_CoCo_ZombieStoneManager.m_ZombieBase = this;
			}
			firstInitDoneCoCo = true;
		}
	}
	
	override void EOnPostFrame(IEntity other, int extra)
	{
		super.EOnPostFrame(other, extra);
		if (m_CoCo_ZombieStoneManager)
			m_CoCo_ZombieStoneManager.EOnPostFrame(other, extra);
	}
	
	void ~ZombieBase()
	{
		if (m_CoCo_ZombieStoneManager)
		{
			delete m_CoCo_ZombieStoneManager;
		}
	}
}

