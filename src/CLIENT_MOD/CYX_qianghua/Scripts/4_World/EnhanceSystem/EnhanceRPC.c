#ifndef CYX_ENHANCE_RPC_DEFINED
#define CYX_ENHANCE_RPC_DEFINED

class EnhanceRPC
{
    // Client -> Server
    const int RPC_ENHANCE_REQUEST = 19991;
    const int RPC_ITEM_INFO_REQUEST = 19997;

    // Server -> Client
    const int RPC_ENHANCE_RESULT = 19992;
    const int RPC_ITEM_INFO_RESPONSE = 19998;
}

#endif