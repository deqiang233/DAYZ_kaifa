class EnhanceEffects
{
    static void PlaySuccessEffect(PlayerBase player)
    {
        if (!player)
        {
            return;
        }

        NotificationSystem.SendNotificationToPlayerExtended(player, 5, "强化结果", "强化成功!", "set:dayz_gui image:notification_friend");
    }

    static void PlayFailureEffect(PlayerBase player)
    {
        if (!player)
        {
            return;
        }

        NotificationSystem.SendNotificationToPlayerExtended(player, 5, "强化结果", "强化失败", "set:dayz_gui image:notification_badtaste");
    }
}

