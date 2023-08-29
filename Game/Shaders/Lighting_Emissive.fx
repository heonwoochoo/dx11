#include "Global.fx"

float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    
    // 이동 변환은 고려하지 않기 때문에 월드의 3x3 행렬을 곱해준다
    output.normal = mul(input.normal, (float3x3) W);
    
    return output;
}

// Emissive
// 외곽선 구할 때 사용 (림 라이트)

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - (float3)input.worldPosition);
    
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;
    
    emissive = smoothstep(0.0f, 1.0f, emissive);
    emissive = pow(emissive, 3);
    
    float4 color = MaterialEmissive * emissive;
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};