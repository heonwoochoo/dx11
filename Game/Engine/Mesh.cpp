#include "pch.h"
#include "Mesh.h"
#include "Geometry.h"
#include "GeometryHelper.h"

Mesh::Mesh()
	: Super(ResourceType::Mesh)
{
}

Mesh::~Mesh()
{
}

void Mesh::CreateQuad()
{
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateQuad(_geometry);
	CreateBuffers();
}

void Mesh::CreateCube()
{
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateCube(_geometry);
	CreateBuffers();
}

void Mesh::CreateSphere(float radius, int slices, int stacks)
{
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateSphere(_geometry, radius, slices, stacks);
	CreateBuffers();
}

void Mesh::CreateGrid(int32 SizeX, int32 SizeZ)
{
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateGrid(_geometry, SizeX, SizeZ);
	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}
