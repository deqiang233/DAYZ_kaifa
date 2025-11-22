class CoCo_ThrownStone extends Stone
{
	bool coco_IsThrowStone;
	
	// 独立伤害设置（如果未设置则使用默认配置）
	float coco_DamageHealth;
	float coco_DamageShock;
	float coco_KeepMinimumHealth;
	float coco_BleedChance;
	
	void CoCo_ThrownStone()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeleteThrownStone, 5000, false);
		// 初始化默认值（如果未设置则使用配置默认值）
		coco_DamageHealth = -1.0;
		coco_DamageShock = -1.0;
		coco_KeepMinimumHealth = -1.0;
		coco_BleedChance = -1.0;
	}
	
	void DeleteThrownStone()
	{
		GetGame().ObjectDelete(this);
	}
}

