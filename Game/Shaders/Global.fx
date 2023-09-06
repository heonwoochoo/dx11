// pragma once 와 같은 기능
#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

//////////////////
//  ConstBuffer //
//////////////////

cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP; // V,P를 곱해서 넘겨주면 연산 효율이 올라감
    matrix VInv;
};

cbuffer TransformBuffer
{
    matrix W;
};


//////////////////
//  VertexData  //
//////////////////

struct Vertex
{
    float4 position : POSITION;
};

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexColor
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentBlend
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLEND_INDICES;
    float4 blendWeights : BLEND_WEIGHTS;
};

///////////////////
//  VertexOutput //
///////////////////

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct MeshOutput
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

///////////////////
//  SamplerState //
///////////////////

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

//////////////////////
//  RasterizerState //
//////////////////////

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

////////////
//  Macro //
////////////

#define PASS_VP(name, vs, ps)                           \
pass name                                               \
{                                                       \
    SetVertexShader(CompileShader(vs_5_0, vs()));       \
    SetPixelShader(CompileShader(ps_5_0, ps()));        \
}

#define PASS_RS_VP(name, rs, vs, ps)                           \
pass name                                               \
{                                                       \
    SetRasterizerState(rs);                             \
    SetVertexShader(CompileShader(vs_5_0, vs()));       \
    SetPixelShader(CompileShader(ps_5_0, ps()));        \
}

///////////////
//  Function //
///////////////

float3 CameraPosition()
{
    return VInv._41_42_43;
}

#endif