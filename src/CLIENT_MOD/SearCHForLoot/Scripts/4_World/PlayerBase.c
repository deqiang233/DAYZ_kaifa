modded class PlayerBase
{
  	protected ref TStringIntMap m_SearchedLootLocations;
	protected int m_TimeCreated;
	protected bool m_SFSearchSound;
	protected string m_SFL_Furniture;

	void PlayerBase()
	{
		m_SearchedLootLocations = new TStringIntMap;
		m_TimeCreated = GetGame().GetTime()/1000;
		RegisterNetSyncVariableBool("m_SFSearchSound");
	}
	
	override void SetActions() 
	{
		super.SetActions();
		AddAction(ActionSearchForLoot);
	}
	
	TStringIntMap GetSearchedLootMap()
	{
		return m_SearchedLootLocations;
	}
	
	int GetTimeCreated()
	{
		return m_TimeCreated;
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();		
		if (m_SFSearchSound)
		{
			SearchingItemSoundPlay();
		}
				
    }
	
	void SearchingItemSoundPlay()
	{
        int searchtime = GetSearchTime();
		searchtime = 3;
		EffectSound m_SearchSound = SEffectManager.PlaySoundOnObject( "SearchingForLoot_SoundSet"+searchtime, this );
		//Print ("SOUND WHISTLE");
        //m_WhistleSound.SetMaxVolume(3.0);
		m_SearchSound.SetSoundAutodestroy( true );
		ResetSearchSound();
	}
	
	void StartSearchSound()
	{
		m_SFSearchSound = true;
		SetSynchDirty();	
	}
	
	void ResetSearchSound()
	{
		m_SFSearchSound = false;
		SetSynchDirty();
	}
	
	int GetSearchTime()
	{
		int searched = this.StatGet("sfl_objects_searched");
		if (searched < 100)
		{
			return 5;
		}
		else if (searched >= 100 && searched < 200)
		{
			return 4;
		}
		else if (searched >= 200 && searched < 300)
		{
			return 3;
		}
		else if(searched >= 300)
		{
			return 2;
		}
		return 5;
	}
	
	string GetFurnitureName()
	{
		return m_SFL_Furniture;
	}
	
	override bool OnInputUserDataProcess(int userDataType, ParamsReadContext ctx)
	{
		if( super.OnInputUserDataProcess(userDataType, ctx) )
			return true;

		if (userDataType == SFL_SEND_NAME)
		{
			ctx.Read(m_SFL_Furniture);
			return false;
		}
		return false; 
	}
	
}