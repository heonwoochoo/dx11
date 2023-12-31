#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct asBone
{
	string name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct asMesh
{
	string name;
	aiMesh* mesh;
	vector<VertexType> vertices;
	vector<uint32> indices;

	int32 boneIndex;
	string materialName;
};

struct asMaterial
{
	string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	string diffuseFile;
	string specularFile;
	string normalFile;
};

// Animation
struct asBlendWeight
{
	void Set(uint32 index, uint32 boneIndex, float weight)
	{
		float i = (float)boneIndex;
		float w = weight;

		switch (index)
		{
		case 0:
			indices.x = i;
			weights.x = w;
			break;
		case 1:
			indices.y = i;
			weights.y = w;
			break;
		case 2:
			indices.z = i;
			weights.z = w;
			break;
		case 3:
			indices.w = i;
			weights.w = w;
			break;
		}
	}

	Vec4 indices = Vec4(0.f, 0.f, 0.f, 0.f);
	Vec4 weights = Vec4(0.f, 0.f, 0.f, 0.f);
};

// 정점마다 -> (관절번호, 가중치)
struct asBoneWeights
{
	void AddWeights(uint32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
			return;

		// 가중치가 높은 bone을 앞으로 우선 배치
		auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) { return weight > p.second; });

		boneWeights.insert(findIt, Pair(boneIndex, weight));
	}

	asBlendWeight GetBlendWeights()
	{
		asBlendWeight blendWeights;

		for (uint32 i = 0; i < boneWeights.size(); i++)
		{
			if (i >= 4) break;

			blendWeights.Set(i, boneWeights[i].first, boneWeights[i].second);
		}
		return blendWeights;
	}

	// 가중치의 합을 1로 변환
	void Normalize()
	{
		if (boneWeights.size() >= 4)
			boneWeights.resize(4);

		float totalWeight = 0.f;
		for (const auto& item : boneWeights)
			totalWeight += item.second;

		for (auto& item : boneWeights)
			item.second /= totalWeight;
	}

	using Pair = pair<uint32, float>;
	vector<Pair> boneWeights;
};

struct asKeyframeData
{
	float time;
	Vec3 scale;
	Quaternion rotation;
	Vec3 translation;
};

struct asKeyframe
{
	string boneName;
	vector<asKeyframeData> transforms;
};

struct asAnimation
{
	string name;
	uint32 frameCount;
	float frameRate;
	float duration;
	vector<shared_ptr<asKeyframe>> keyframes;
};

// cache
struct asAnimationNode
{
	aiString name;
	vector<asKeyframeData> keyframe;
};