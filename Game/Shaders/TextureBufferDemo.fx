
Texture2DArray<float4> Input;
RWTexture2DArray<float4> Output;

// 스레드의 개수 10 * 8 * 3 = 240
[numthreads(32, 32, 1)]
void CS(uint3 id : SV_DispatchThreadID)
{
    float4 color = Input.Load(int4(id, 0));
    //Output[id] = color;
    Output[id] = 1.0f - color;
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