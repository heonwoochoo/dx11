RWByteAddressBuffer Output; // UAV

struct ComputeInput
{
    uint3 groupID : SV_GroupID;
    uint3 groupThreadID : SV_GroupThreadID;
    uint3 dispatchThreadID : SV_DispatchThreadID;
    uint groupIndex : SV_GroupIndex;
};

// 스레드의 개수 10 * 8 * 3 = 240
[numthreads(10, 8, 3)]
void CS(ComputeInput input)
{
    uint index = input.groupIndex;
    // ComputeInpute은 10개의 4 bytes (uint)를 가지고 있다
    uint outAddress = index * 10 * 4;
    
    // outAddress + offset 으로 저장될 위치를 설정
    Output.Store3(outAddress + 0, input.groupID);
    Output.Store3(outAddress + 12, input.groupThreadID);
    Output.Store3(outAddress + 24, input.dispatchThreadID);
    Output.Store(outAddress + 36, input.groupIndex);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);
        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
}