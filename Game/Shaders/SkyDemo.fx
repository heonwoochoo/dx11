#include "Light.fx"

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
    VS_OUT output;
    
    // Local -> World -> View -> Proj
    // Sky가 카메라의 원점에 고정되었다고 가정하면 월드를 곱해줄 필요 없이 바로 View로 변환
    // 다만 Rotation은 적용시켜줘야한다.
    float4 viewPos = mul(float4(input.position.xyz, 0), V);
    float4 clipPos = mul(viewPos, P);
    output.position = clipPos.xyzw;
    output.position.z = output.position.w * 0.999999f;
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(VS_OUT input) : SV_TARGET
{
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    //float4 color = ComputeLight(input.normal, input.uv, (float3)input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

technique11 T0
{
    pass P0
    {
        SetRasterizerState(FrontCounterClockwiseTrue);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}