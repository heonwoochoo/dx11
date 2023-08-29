#include "Global.fx"

float3 LightDir;
float4 LightSpecular;
float4 MaterialSpecular;

Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    
    // �̵� ��ȯ�� ������� �ʱ� ������ ������ 3x3 ����� �����ش�
    output.normal = mul(input.normal, (float3x3) W);
    
    return output;
}

// Specular (�ݻ籤)
// �� �������� ������ �ݻ�Ǵ� �� (Phong)

float4 PS(MeshOutput input) : SV_TARGET
{
    // ��� ���Ϳ� ���� �ݻ簢�� ����
    float3 R = reflect(LightDir, input.normal);
    R = normalize(R);
    
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - (float3)input.worldPosition);
    
    float value = saturate(dot(R, E));  // clamp(0~1)
    float specular = pow(value, 10);
    
    float4 color = LightSpecular * MaterialSpecular * specular;

    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};