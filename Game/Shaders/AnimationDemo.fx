#include "Light.fx"

#define MAX_MODEL_TRANSFORMS 250

cbuffer BoneBuffer
{
    matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};

uint BoneIndex;

MeshOutput VS(VertexTextureNormalTangentBlend input)
{
    MeshOutput output;
    
    // TODO
    
    
    output.position = mul(input.position, BoneTransforms[BoneIndex]);
    output.position = mul(output.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    
    // 이동 변환은 고려하지 않기 때문에 월드의 3x3 행렬을 곱해준다
    output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3)W);
    
    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    //float4 color = ComputeLight(input.normal, input.uv, (float3)input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
    PASS_RS_VP(P1, FillModeWireFrame, VS, PS_RED)
};