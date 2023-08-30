#include "Light.fx"


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



float4 PS(MeshOutput input) : SV_TARGET
{
    float4 color = ComputeLight(input.normal, input.uv, (float3)input.worldPosition);
    
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
};