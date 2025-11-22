class ActionSearchForLootCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{	
		int searchtime = m_ActionData.m_Player.GetSearchTime();
		searchtime = 1.5;
		m_ActionData.m_ActionComponent = new CAContinuousTime(searchtime);
	}
};

class ActionSearchForLoot: ActionContinuousBase
{
	void ActionSearchForLoot()
	{
		m_CallbackClass = ActionSearchForLootCB;
		m_FullBody = true;
		//m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		//m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_UNRESTRAINTARGET;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		//m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_TAKETEMPSELF;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINotPresent;
		//m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursorParent(UAMaxDistances.DEFAULT);
	}
	/*
	override bool IsUsingProxies()
	{
		return true;
	}
	*/
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}
	
	override bool HasTarget()
	{
		return true;
	}


	
	override bool CanBeUsedInVehicle()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#STR_search";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target )
			return false;
		Building building;
		if ( !Class.CastTo(building, target.GetParent()) ) 
			return false;
		// ukladat pozice clientside
		// v zavisloti jak douho je hrac na serveru zvysovat pravdepodobnost nalezeni predmetu
		// jako prevence proti relogovani
		// udelat mapu server time, vektor
		// mazat polozky starsi 20-30 minut
		// podle typu budovy spawnout item kategorii (vesnice, mesto, hunting, military)
		//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "Game time: " + GetGame().GetTime()/1000 + " plr created " + player.GetTimeCreated(), ""));

		array<string> selections = new array<string>;
		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			target.GetObject().GetActionComponentNameList(target.GetComponentIndex(), selections);
			//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "POS: " + target.GetObject().GetPosition() , ""));
			for (int s = 0; s < selections.Count(); s++)
			{	
				if ( selections[s] != "" && CanFindSomething(player, House.Cast(Object.Cast(target.GetParent())), target.GetObject().GetPosition(), Object.Cast(target.GetParent()).ModelToWorld(target.GetObject().GetPosition()) ) )
				{
					//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "Game time: " + GetGame().GetTime()/1000, ""));
					//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "Selection: " + selections[s], ""));
					
					//Print("OBJ " + target.GetObject() + " " + Object.Cast(target.GetParent()).ModelToWorld(target.GetObject().GetPosition()) + " parent " + Object.Cast(target.GetParent()).GetPosition() + " " + target.GetObject().GetModelName());
					return true;
				}
			}
			return false;
		} 
		return true;
	}
	override void OnStartClient(ActionData action_data )
	{
		string furniture;
		Object targetObject = action_data.m_Target.GetObject();
		House house = House.Cast(Object.Cast(action_data.m_Target.GetParent()));
		vector locpos = targetObject.GetPosition();
		
		//Print("CLIENT " + house + " locpos " + locpos);
		
		furniture = GetProxyName(house, locpos);
		//Print("furniture " + furniture);
		//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "House: " + house + " proxy: " + furniture, ""));
		
		ScriptInputUserData ctx = new ScriptInputUserData;
		ctx.Write(SFL_SEND_NAME);
		ctx.Write(furniture);
		ctx.Send();
		
	}
	
	override void OnStartServer(ActionData action_data )
	{	
		//start sound
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		if (config.SoundEnabled)
		{
			action_data.m_Player.StartSearchSound();
		}
		
	}
	
	override void OnFinishProgressClient( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		//string posit = targetObject.GetPosition()[0].ToString() + " " + targetObject.GetPosition()[1].ToString() + " " + targetObject.GetPosition()[2].ToString();
		string posit = Object.Cast(action_data.m_Target.GetParent()).ModelToWorld(action_data.m_Target.GetObject().GetPosition())[0].ToString() + " " + Object.Cast(action_data.m_Target.GetParent()).ModelToWorld(action_data.m_Target.GetObject().GetPosition())[1].ToString() + " " + Object.Cast(action_data.m_Target.GetParent()).ModelToWorld(action_data.m_Target.GetObject().GetPosition())[2].ToString(); 
		//Print ("POSIT " + posit);
		action_data.m_Player.GetSearchedLootMap().Insert(posit, GetGame().GetTime()/1000);
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		action_data.m_Player.ResetSearchSound();
		Object targetObject = action_data.m_Target.GetObject();
		string targetBuildingName = Object.Cast(action_data.m_Target.GetParent()).ClassName();
		vector pos = action_data.m_Player.ModelToWorld("0 0 0.2");
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		string buildingCategory;
		
		TStringArray Parentselections = new TStringArray;
		action_data.m_Target.GetParent().GetSelectionList( Parentselections );
		
		//SFLLogger.Debug("Player " + action_data.m_Player.GetIdentity().GetName() + " searched building " + targetBuildingName + " category " + GetDayZGame().GetBuildingCategory(targetBuildingName));
		//SFLLogger.Debug("OBJ " + targetBuildingName + " list " + Parentselections);
		int initialcooldown = config.InitialCooldown;
		int xpgain = Math.WrapInt(config.XPGain,1,10);
		if (initialcooldown == 0)
		{
			initialcooldown = 400;
		}
		
		if (GetRandomItem(GetDayZGame().GetBuildingCategory(targetBuildingName), action_data.m_Player.GetFurnitureName()) != "nothing")
		{
			// more random and also according to online time of player
			float rndnum = Math.RandomFloat(0,100);
			float rarita;
			//Print ("taget building name " + targetBuildingName);
			string advanced_category = GetDayZGame().GetBuildingCategory(targetBuildingName) + "_" + GetProxyCategory(action_data.m_Player.GetFurnitureName());
			//Print ("advanced category " + advanced_category);
			if (GetRarity(advanced_category) == 0)
			{
				rarita = config.Rarity;	
			}
			else
			{
				rarita = GetRarity(advanced_category);
			}
			//Print ("rarita " + rarita);
			action_data.m_Player.StatUpdate( "sfl_objects_searched", xpgain );
			action_data.m_Player.StatSyncToClient();
			// action_data.m_Player.StatGet("sfl_objects_searched") 
			if (rarita > rndnum &&  action_data.m_Player.GetTimeCreated()+initialcooldown < GetGame().GetTime()/1000)
			{
				if (!config.DisableNotifications && action_data.m_Player)
				{
					NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 2, config.NotificationHeading, config.NotificationText, "set:dayz_gui image:tutorials");
				}
				ItemBase item = ItemBase.Cast(GetGame().CreateObject(GetRandomItem(GetDayZGame().GetBuildingCategory(targetBuildingName), action_data.m_Player.GetFurnitureName() ), pos));
				//ItemBase item = ItemBase.Cast(CEApi.SpawnEntity(GetRandomItem(GetBuildingCategory(targetBuildingName)), pos, 1, 1));
				//Zedmag
				//added for organic foods.. 
				Edible_Base food;
				Class.CastTo(food,item);
				if ( food && food.HasFoodStage()) //possible NPE ?
				{
					int rand = Math.RandomInt(0,15);
					Edible_Base item_EB = Edible_Base.Cast(item);
					//33% chance its rotten
					if ( rand > 10 )
					{
						item_EB.ChangeFoodStage( FoodStageType.ROTTEN );
					}
					//33% chance its dried
					else if ( rand <=10 && rand >= 6 )
					{
						item_EB.ChangeFoodStage( FoodStageType.DRIED );
					}
					//if its less than 6 this its Raw
				}
				
				SetRandomQuantity(item);
				float maxcoef = Math.Clamp(config.MaxHealthCoef, 0.4, 1.0);
				
				Magazine_Base mag;	
        		if (item && !Class.CastTo(mag, item))
				{
					float rndhealth = Math.RandomFloat(item.GetMaxHealth("", "")*0.1, item.GetMaxHealth("", "")*maxcoef);
					item.SetHealth("", "", rndhealth);
				}
				//random damage of items
				if (item)
				{
					item.SetLifetime(900);
				}
			}
			//Zedmag
			//added 'else' for NOT meeting config.Rarity condition
			else 
			{
				//Zedmag
				//could add to config for custom msg.. 
				if (!config.DisableNotifications && action_data.m_Player)
				{
					NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 2, config.NotificationHeading, config.NotificationText2, "set:dayz_gui image:tutorials");
				}
				
			}
			
		}
	}
	
	string GetBuildingCategory(string building)
	{
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		int i, j;
		for (i = 0; i < config.SFLBuildings.Count(); i++)
		{
			for (j = 0; j < config.SFLBuildings.Get(i).buildings.Count(); j++)
			{
				if (config.SFLBuildings.Get(i).buildings.Get(j) == building)
				{
					return config.SFLBuildings.Get(i).name;
				}
			}
		}
		//fallback
		return "Civilian";
	}
	
	static void SetRandomQuantity(ItemBase item)
	{
		
		Magazine_Base mag;
		if (Class.CastTo(mag, item))
        {
            int ammocount = mag.GetAmmoCount();
			int qarnd = Math.RandomIntInclusive(1,ammocount);
			mag.ServerSetAmmoCount(qarnd);
		}
		else 
		{
		
			if (item && item.HasQuantity())
			{
				int qmax = item.GetQuantityMax();
				
				int qrnd = Math.RandomIntInclusive(1,qmax);
				qrnd = Math.RandomIntInclusive(1,qmax);
				if (qmax > 0)
				{
					
					item.SetQuantity(qrnd);
				}
			}		
			if( item && item.GetEconomyProfile() )
			{
	
				float q_min = item.GetEconomyProfile().GetQuantityMin();
				float q_max = item.GetEconomyProfile().GetQuantityMax();
				if( q_max > 0 )
				{
					float quantity_randomized = Math.RandomFloatInclusive(q_min, q_max);
					item.SetQuantityNormalized(quantity_randomized, false);
					
				}
			}
			
		}
		
	}
	
	string GetProxyName(House house, vector localpos)
	{
		string furniture;
		string localposstr = localpos.ToString(false);
		TStringArray strpos = new TStringArray;
		localposstr.Split(" ", strpos);
		//string locpos = strpos[0]+ " " + strpos[2];
		string locpos = locpos.SubstringInverted( strpos[0], -4 + strpos[0].Length(), strpos[0].Length())+ " " + locpos.SubstringInverted( strpos[2], -4 + strpos[2].Length(), strpos[2].Length() );
		house.SFLGetProxyObjectMap1().Find( locpos, furniture);
		return furniture;
	}
	
	string GetRandomItem (string category, string furniture)
	{
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		
		//string furniture;
		string furniture_category;
		string advanced_category;
		int i;
		//string localposstr = localpos.ToString(false);
		//TStringArray strpos = new TStringArray;
		//localposstr.Split(" ", strpos);
		//string locpos = strpos[0]+ " " + strpos[2];
		//house.GetProxyObjectMap1().Find( locpos, furniture);
		//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", furniture, ""));
		
		TStringArray proxies = new TStringArray;
		GetGame().ConfigGetTextArray("CfgSFLProxies proxies", proxies);
		
		if (proxies.Find(furniture) > -1) 
		{
			furniture_category = GetProxyCategory(furniture);
			//Print("Searched: " + furniture + " category " + furniture_category);
		}
		
		// First try to find building-specific category (e.g., "Civilian_Food")
		advanced_category = category + "_" + furniture_category;
		
		for (i = 0; i < config.SFLLootCategory.Count(); i++)
		{
			if (config.SFLLootCategory.Get(i).name == advanced_category)
			{
				return GetWeightedRandomItem(config.SFLLootCategory.Get(i));
			}
		}
		
		// Fallback to generic category (e.g., "Food", "Clothing", "Tools")
		for (i = 0; i < config.SFLLootCategory.Count(); i++)
		{
			if (config.SFLLootCategory.Get(i).name == furniture_category)
			{
				return GetWeightedRandomItem(config.SFLLootCategory.Get(i));
			}
		}
		
		return "nothing";
	}
	
	string GetWeightedRandomItem(SFLootCategory category)
	{
		int i;
		// 优先使用新的权重系统
		if (category.lootItems && category.lootItems.Count() > 0)
		{
			// 计算总权重
			float totalWeight = 0;
			for (i = 0; i < category.lootItems.Count(); i++)
			{
				if (category.lootItems.Get(i).weight > 0)
				{
					totalWeight += category.lootItems.Get(i).weight;
				}
			}
			
			if (totalWeight <= 0)
			{
				return "nothing";
			}
			
			// 随机选择
			float randomValue = Math.RandomFloat(0, totalWeight);
			float currentWeight = 0;
			
			for (i = 0; i < category.lootItems.Count(); i++)
			{
				SFLootItem lootItem = category.lootItems.Get(i);
				if (lootItem.weight > 0)
				{
					currentWeight += lootItem.weight;
					if (randomValue <= currentWeight)
					{
						return lootItem.item;
					}
				}
			}
			
			// 如果循环结束还没返回，返回最后一个有效物品
			for (i = category.lootItems.Count() - 1; i >= 0; i--)
			{
				if (category.lootItems.Get(i).weight > 0)
				{
					return category.lootItems.Get(i).item;
				}
			}
		}
		
		// 兼容旧格式：如果没有权重配置，使用旧的随机选择
		if (category.loot && category.loot.Count() > 0)
		{
			return category.loot.GetRandomElement();
		}
		
		return "nothing";
	}
	
	string GetProxyCategory(string furniture)
	{
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		int i;
		for (i = 0; i < config.SFLProxyCategory.Count(); i++)
		{
			if (config.SFLProxyCategory.Get(i).proxies.Find(furniture) > -1 )
			{
				return config.SFLProxyCategory.Get(i).name;
			}
		}
		return "Food";
	}
	
	float GetRarity (string category)
	{
		SFLConfig config = GetDayZGame().GetSearchForLootConfig();
		int i;
		for (i = 0; i < config.SFLLootCategory.Count(); i++)
		{
			if (config.SFLLootCategory.Get(i).name == category)
			{
				return config.SFLLootCategory.Get(i).rarity;
			}
		}
		// If category is in format "BuildingType_ProxyCategory", try to find generic "ProxyCategory"
		TStringArray categoryParts = new TStringArray;
		category.Split("_", categoryParts);
		if (categoryParts.Count() >= 2)
		{
			string genericCategory = categoryParts.Get(1);
			for (i = 0; i < config.SFLLootCategory.Count(); i++)
			{
				if (config.SFLLootCategory.Get(i).name == genericCategory)
				{
					return config.SFLLootCategory.Get(i).rarity;
				}
			}
		}
		return config.Rarity;
	}
	
	bool CanFindSomething(PlayerBase player, House house, vector localpos, vector pos)
	{
		int time = 1;
		string posi = pos[0].ToString() + " " + pos[1].ToString() + " " + pos[2].ToString();
		bool entry = player.GetSearchedLootMap().Find(posi, time);
		//SFLLogger.Log("MAP " + player.GetSearchedLootMap().Count());
		//Print("localpos " + localpos.ToString(false));
		/*
		string value;
		for ( int zzz = 0; zzz < house.GetProxyObjectMap1().Count(); zzz++ )
		{			
			house.GetProxyObjectMap1().Find(house.GetProxyObjectMap1().GetKey(zzz), value);
			Print("== " + house.GetProxyObjectMap1().GetKey(zzz) + ", " + value +  " =="); 
		}
		//Print("----Part 2-----");
		
		for ( int ddd = 0; ddd < house.GetProxyObjectMap2().Count(); ddd++ )
		{
			house.GetProxyObjectMap2().Find(house.GetProxyObjectMap2().GetKey(ddd), value);
			//Print("== " + house.GetProxyObjectMap2().GetKey(ddd) + ", " + value +  " =="); 
		}
		*/
		string furniture;
		string localposstr = localpos.ToString(false);
		TStringArray strpos = new TStringArray;
		localposstr.Split(" ", strpos);
		string locpos = locpos.SubstringInverted( strpos[0], -4 + strpos[0].Length(), strpos[0].Length())+ " " + locpos.SubstringInverted( strpos[2], -4 + strpos[2].Length(), strpos[2].Length() );
		house.SFLGetProxyObjectMap1().Find( locpos, furniture);
		
		//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", "CAN FIND: " + furniture, ""));
		
		//Print("FURNITURE " + furniture + " " + localpos.ToString(false));
		TStringArray proxies = new TStringArray;
		GetGame().ConfigGetTextArray("CfgSFLProxies proxies", proxies);
		//Print ("PROXY LIST " + proxies);
		if (proxies.Find(furniture) < 0) 
		{
			return false;
		}
		
		if (GetGame().GetTime()/1000 > time+1800 || !entry)
		{
			if (entry)
			{
				player.GetSearchedLootMap().Remove(posi);
			}
			return true;
		}
		return false;
	}

};