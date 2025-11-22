modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (!GetGame().IsClient())
        {
            return;
        }

        Param4<bool, string, int, string> enhanceResult;
        Param1<ref EnhanceDisplayInfo> infoResponse;
        Param3<bool, string, float> refineResult;

        if (rpc_type == EnhanceRPC.RPC_ENHANCE_RESULT)
        {
            if (ctx.Read(enhanceResult))
            {
                bool success = enhanceResult.param1;
                string resultType = enhanceResult.param2;
                int resultQuantity = enhanceResult.param3;
                string message = enhanceResult.param4;

                if (message != "")
                {
                    MessageImportant(message);
                }

                if (success)
                {
                    EnhanceEffects.PlaySuccessEffect(this);
                }
                else
                {
                    EnhanceEffects.PlayFailureEffect(this);
                }

                EnhanceMenuBridge.HandleEnhanceResult(success, message);
            }
            return;
        }

        if (rpc_type == EnhanceRPC.RPC_ITEM_INFO_RESPONSE)
        {
            if (!ctx.Read(infoResponse))
            {
                Print("[CYX_ENHANCE][CLIENT] Failed to read info response payload.");
                return;
            }

            EnhanceMenuBridge.HandleInfoResponse(infoResponse.param1);
            return;
        }

        if (rpc_type == EnhanceRPC.RPC_REFINE_RESULT)
        {
            if (ctx.Read(refineResult))
            {
                bool refineSuccess = refineResult.param1;
                string refineMessage = refineResult.param2;
                float multiplier = refineResult.param3;

                if (refineMessage != "")
                {
                    MessageImportant(refineMessage);
                }

                if (refineSuccess)
                {
                    EnhanceEffects.PlaySuccessEffect(this);
                }
                else
                {
                    EnhanceEffects.PlayFailureEffect(this);
                }
            }
            return;
        }
    }
}

