#pragma once

struct ModelBone
{
	wstring name;
	int32 index;
	int32 parentIndex;
	shared_ptr<ModelBone> parent;	// cache

	Matrix transform;
	vector<shared_ptr<ModelBone>> children;	// cache
};

struct ModelMesh
{
	void CreateBuffers();

	wstring name;

	// Mesh
	shared_ptr<Geometry<ModelVertexType>> geometry = make_shared<Geometry<ModelVertexType>>();
	shared_ptr<VertexBuffer> vertexBuffer;
	shared_ptr<IndexBuffer> indexBuffer;

	// Material
	wstring materialName = L"";
	shared_ptr<Material> material;	// cache

	// Bones
	int32 boneIndex;
	shared_ptr<ModelBone> bone;	// cache
};
