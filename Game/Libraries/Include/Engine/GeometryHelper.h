#pragma once
#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry, float radius, int slices, int stacks);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 SizeX, int32 SizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry, float radius, int slices, int stacks);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 SizeX, int32 SizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, float radius, int slices, int stacks);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, int32 SizeX, int32 SizeZ);
};

