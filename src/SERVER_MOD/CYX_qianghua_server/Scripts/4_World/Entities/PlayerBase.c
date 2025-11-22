modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (!GetGame().IsServer())
        {
            return;
        }

        Param2<string, bool> enhanceRequest;
        Param1<string> infoRequest;

        if (rpc_type == EnhanceRPC.RPC_ENHANCE_REQUEST)
        {
            if (ctx.Read(enhanceRequest))
            {
                string itemType = enhanceRequest.param1;
                bool useProtection = enhanceRequest.param2;
                EnhanceConfigManager.LoadConfig();
                EnhanceProcessor.ProcessEnhanceRequest(this, itemType, useProtection);
            }
            return;
        }

        if (rpc_type == EnhanceRPC.RPC_ITEM_INFO_REQUEST)
        {
            if (!ctx.Read(infoRequest))
            {
                Debug.Log("[CYX_ENHANCE][SERVER] Failed to read info request payload.", "CYX_ENHANCE");
                return;
            }

            string requestType = infoRequest.param1;
            EnhanceConfigManager.LoadConfig();
            EnhanceDisplayInfo info = EnhanceConfigManager.BuildDisplayInfo(requestType);
            if (!info)
            {
                string errorMessage = "❌ 未找到该物品的强化配置: " + requestType;
                info = EnhanceConfigManager.BuildErrorInfo(requestType, errorMessage);
            }

            Param1<ref EnhanceDisplayInfo> payload = new Param1<ref EnhanceDisplayInfo>(info);
            PlayerIdentity target = sender;
            if (!target)
            {
                target = GetIdentity();
            }

            string hasDataText;
            if (info.HasData)
            {
                hasDataText = "true";
            }
            else
            {
                hasDataText = "false";
            }
            Debug.Log("[CYX_ENHANCE][SERVER] Sending info response for " + requestType + " (hasData=" + hasDataText + ")", "CYX_ENHANCE");
            this.RPCSingleParam(EnhanceRPC.RPC_ITEM_INFO_RESPONSE, payload, true, target);
            return;
        }
    }
}

