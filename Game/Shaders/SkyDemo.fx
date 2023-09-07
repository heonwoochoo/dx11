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
    // Sky�� ī�޶��� ������ �����Ǿ��ٰ� �����ϸ� ���带 ������ �ʿ� ���� �ٷ� View�� ��ȯ
    // �ٸ� Rotation�� �����������Ѵ�.
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