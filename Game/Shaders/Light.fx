// pragma once 와 같은 기능
#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "Global.fx"

/////////////////
//   STRUCT    //
/////////////////

struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float padding;
};

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};

/////////////////
// ConstBuffer //
/////////////////

cbuffer LightBuffer
{
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};

/////////
// SRV //
/////////

Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

//////////////
// Function //
//////////////

float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    // Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    
    // Diffuse
    {
        float4 color = GlobalLight.diffuse * Material.diffuse;
        float value = dot(-GlobalLight.direction, normalize(normal));
        
        diffuseColor = DiffuseMap.Sample(LinearSampler, uv) * color * value;
    }
    
    // Specular
    {
        // 노멀 벡터에 대해 반사각을 적용
        float3 R = reflect(GlobalLight.direction, normal);
        R = normalize(R);
    
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(R, E)); // clamp(0~1)
        float specular = pow(value, 10);
    
        specularColor = GlobalLight.specular * Material.specular * specular;
    }
    
    // Emissive
    {
        float3 cameraPosition = CameraPosition();
        float3 E = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(E, normal));
        float emissive = 1.0f - value;
    
        emissive = smoothstep(0.0f, 1.0f, emissive);
        emissive = pow(emissive, 3);
    
        emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
    }
 
    return ambientColor + diffuseColor + specularColor + emissiveColor;
}

void ComputeNormalMapping(inout float3 normal, float3 tangent, float2 uv)
{
    // [0,255] 범위에서 [0,1]로 변환
    float4 map = NormalMap.Sample(LinearSampler, uv);
    if (any(map.rgb) == false)
        return;
    
    float3 N = normalize(normal);
    float3 T = normalize(tangent);
    float3 B = normalize(cross(N, T));
    
    // Tangent space에서 World space로 변환하는 행렬
    float3x3 TBN = float3x3(T, B, N);

    // [0,1] 범위에서 [-1,1] 범위로 변환
    float3 tangentSpaceNormal = (map.rgb * 2.0f - 1.0f);
    
    float3 worldNormal = mul(tangentSpaceNormal, TBN);
    normal = worldNormal;
}

#endif