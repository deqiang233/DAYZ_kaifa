//TODO add Debug Prints to config for disablibng logs
modded class House
{
	bool DoLogs = false; //TODO move to config?
	
	// if(DoLogs)
  	protected ref TStringStringMap z_SFL_ProxyObjectLocationsMap1;
  	protected ref TStringStringMap z_SFL_ProxyObjectLocationsMap2;
	protected ref TStringStringMap z_SFL_SortdedMap2; 
	
	private const string GEOM_LOD_NAME 	= LOD.NAME_GEOMETRY;
	static ref array<Selection> geoselections = new array<Selection>();		
	
	static ref TStringArray Parentselections = new TStringArray;

	//void SetupActionMap(string target){}	

	void SFLGetBuildingMaps()
	{
		int count;
		if (GetGame().IsMultiplayer() || GetGame().IsServer() || GetGame().IsClient() || GetGame().IsDedicatedServer())
		{

			//---------------Get names from proxy selection in geo lod----------------------------
			string type = GetType();
			type.ToLower();
			//------------------- Start-----Map1--------------------------
			LOD geoLod;
			if(GetType().Contains("ContaminatedArea"))
			{
				return;
			}
			else
			{
				geoLod = GetLODByName(GEOM_LOD_NAME);
			}
			
			GetSelectionList( Parentselections );
			if (!geoLod)
			{
				return;
			}				
			geoLod.GetSelections(geoselections);
			for (int i = 0; i < geoselections.Count(); ++i)
			{	
			if(DoLogs)
				Print("[ShowMeInfo] ---BEGIN--Proxy Map1 Building<" + GetType() + ">------------------|"); 
			if(DoLogs)
				Print("[ShowMeInfo] ---BEGIN--Proxy Map1 Object<" + this + ">------------------|"); 	
				string selection = geoselections[i].GetName();
				string selectionlower = selection;
				selectionlower.ToLower();				
				if(selectionlower.Contains("proxy") && !selectionlower.Contains("proxies") && !selectionlower.Contains("shadow")) 
				{
					string getselPosOldstrg = GetSelectionPositionOld(selection).ToString(false);
					TStringArray strpos = new TStringArray;
					getselPosOldstrg.Split(" ", strpos);
					string localpos = localpos.SubstringInverted(strpos[0], -4 + strpos[0].Length(), strpos[0].Length() )+ " " + localpos.SubstringInverted(strpos[2], -4 + strpos[2].Length(), strpos[2].Length() );
					selection.ToLower();
					TStringArray strs = new TStringArray;
					selection.Split("\\", strs);
					for ( int ii = 0; ii < strs.Count(); ii++ )
					{
						string newstrg = strs[ii];
						string objName;
						string objP3dName;
						if(newstrg.Contains("."))
						{
							newstrg = "static_" + newstrg;			
							int strLgth = newstrg.Length();
							int newLgth = strLgth - 4;					
							objName = newstrg.Substring(0, newLgth);
							//build ProxyMap 1------------------------------------
							if(objName.Contains(".p3d"))
							{
								int strP3dLgth = objName.Length();
								int newP3dLgth = strP3dLgth - 4;
								objP3dName = objName.Substring(0, newP3dLgth);
								SFLGetProxyObjectMap1().Insert(localpos, objP3dName);
							}
							else
							{

								SFLGetProxyObjectMap1().Insert(localpos, objName);
							}
							count++;
						}
					}
					
				}
			}
			
			//Print BEGIN Map1----------------------- 
			for ( int iii = 0; iii < SFLGetProxyObjectMap1().Count(); iii++ )
			{
				string value;
				SFLGetProxyObjectMap1().Find(SFLGetProxyObjectMap1().GetKey(iii), value);
			if(DoLogs)
				Print("[ShowMeInfo] -----map(key, value)--<" + SFLGetProxyObjectMap1().GetKey(iii) + ", " + value +  ">------------------|"); 
			}
			if(DoLogs)
				Print("[ShowMeInfo] ---END--Proxy Map1 Object<" + this + ">------------------|"); 
			//------------------- END-----Map1--------------------------

			//------------------- Begin-----Map2--------------------------
			for (int z = 0; z < Parentselections.Count(); z++)
			{
			if(DoLogs)
				Print("[ShowMeInfo] ---BEGIN--Proxy Map2 Building<" + GetType() + ">------------------|"); 
			if(DoLogs)
				Print("[ShowMeInfo] ---BEGIN--Proxy Map2 Object<" + this + ">------------------|"); 	
				
				Parentselections[z].ToLower();
				if(selectionlower.Contains("proxy") && !selectionlower.Contains("proxies") && !selectionlower.Contains("shadow")) 
				{

					vector P_LsPos = GetSelectionPositionLS(Parentselections[z]);
					string P_LsPosstrg = P_LsPos.ToString(false);
					
					TStringArray strs2 = new TStringArray;
					Parentselections[z].Split("\\", strs2);
					for ( int iiii = 0; iiii < strs2.Count(); iiii++ )
					{
						string newstrg2 = strs2[iiii];
						string objName2;
						string objP3dName2;
						if(newstrg2.Contains("."))
						{
							newstrg2 = "static_" + newstrg2;			
							int strLgth2 = newstrg2.Length();
							int newLgth2 = strLgth2 - 4;					
							objName2 = newstrg2.Substring(0, newLgth2);
							//build ProxyMap 2------------------------------------
							if(objName2.Contains(".p3d"))
							{
								int strP3dLgth2 = objName2.Length();
								int newP3dLgth2 = strP3dLgth2 - 4;
								objP3dName2 = objName2.Substring(0, newP3dLgth2);
	
								SFLGetProxyObjectMap2().Insert(P_LsPosstrg, objP3dName2);
							}
							else
							{
								SFLGetProxyObjectMap2().Insert(P_LsPosstrg, objName2);
							}
							count++;
						}
					}
					
				}
			}
			//Print BEGIN Map2----------------------- 
			for ( int zzz = 0; zzz < SFLGetProxyObjectMap2().Count(); zzz++ )
			{
				string value2;
				SFLGetProxyObjectMap2().Find(SFLGetProxyObjectMap2().GetKey(zzz), value2);
			if(DoLogs)
				Print("[ShowMeInfo] -----map(key, value)--<" + SFLGetProxyObjectMap2().GetKey(zzz) + ", " + value +  ">------------------|"); 
			}
			if(DoLogs)
				Print("[ShowMeInfo] ---END--Proxy Map2 Object<" + this + ">------------------|"); 
			//------------------- END-----Map2--------------------------
		}
	}	
	TStringStringMap SFLGetProxyObjectMap1()
	{
		return z_SFL_ProxyObjectLocationsMap1;
	}
	TStringStringMap SFLGetProxyObjectMap2()
	{
		return z_SFL_ProxyObjectLocationsMap2;
	}
	TStringStringMap SFLGetSortedMap()
	{
		return z_SFL_SortdedMap2;
	}
	void SFLPrintMap()
	{
		string value2;
		string value;
		SFLGetProxyObjectMap1().Find(SFLGetProxyObjectMap1().GetKey(0), value);
		SFLGetProxyObjectMap2().Find(SFLGetProxyObjectMap2().GetKey(0), value2);
		Print(" " + this + " - " + SFLGetProxyObjectMap1().GetKey(0) + " - " + value + " x " + SFLGetProxyObjectMap2().GetKey(0) + " - " + value2);
	}
	
	void House()
	{
		z_SFL_ProxyObjectLocationsMap1 = new TStringStringMap;
		z_SFL_ProxyObjectLocationsMap2 = new TStringStringMap;
		z_SFL_SortdedMap2 = new TStringStringMap;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SFLGetBuildingMaps, 1000, false);
		//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SFLPrintMap, 2000, false);		
	}		
}
		/* 
		TODO find better way to exclude buidlings that dont have proxies
		
		EXCLUDE the following
		"misc"
		"lamp"
		"staticobj"
		"wreck"
		"wall"
		"gate"
		"feed"
		"dead"
		"lunapark"
		
		INCLUDE
		"land_"
		"house"
		"station"
		
		
		*/
