modded class AnalyticsManagerServer
{
	
	override void OnPlayerConnect( Man player )
	{
		player.StatRegister( "sfl_objects_searched" );
		super.OnPlayerConnect(player);
	}
}