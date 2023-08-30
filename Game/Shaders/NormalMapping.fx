#include "Light.fx"


MeshOutput VS(VertexTextureNormalTangent input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    
    // �̵� ��ȯ�� ������� �ʱ� ������ ������ 3x3 ����� �����ش�
    output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3)W);
    
    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, (float3)input.worldPosition);
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};