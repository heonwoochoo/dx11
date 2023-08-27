#pragma once
#include "ResourceBase.h"
#include "Geometry.h"

class Mesh : public ResourceBase
{
	using Super = ResourceBase;

public:
	Mesh();
	virtual ~Mesh();

	void CreateQuad();
	void CreateCube();
	void CreateSphere(float radius, int slices, int stacks);
	void CreateGrid(int32 SizeX, int32 SizeZ);

	void CreateBuffers();

	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }

private:

	// Mesh
	shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
	shared_ptr<VertexBuffer>	_vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;
};

