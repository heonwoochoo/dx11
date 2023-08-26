#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector<VertexColorData> vtx;
	vtx.resize(4);
	vtx[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vtx[0].color = color;
	vtx[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vtx[1].color = color;
	vtx[2].position = Vec3(0.5f, 0.5f, 0.f);
	vtx[2].color = color;
	vtx[3].position = Vec3(0.5f, -0.5f, 0.f);
	vtx[3].color = color;
	geometry->SetVertices(vtx);

	vector<uint32> indices = { 0, 1, 2, 0, 2, 3 };
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vtx;
	vtx.resize(4);
	vtx[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vtx[0].uv = Vec2(0.f,1.f);
	vtx[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vtx[1].uv = Vec2(0.f,0.f);
	vtx[2].position = Vec3(0.5f, 0.5f, 0.f);
	vtx[2].uv = Vec2(1.f,0.f);
	vtx[3].position = Vec3(0.5f, -0.5f, 0.f);
	vtx[3].uv = Vec2(1.f,1.f);
	geometry->SetVertices(vtx);

	vector<uint32> indices = { 0, 1, 2, 0, 2, 3 };
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	vector<VertexTextureData> vtx(24);

	// 앞면
	vtx[0] = VertexTextureData{ Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f) };
	vtx[1] = VertexTextureData{ Vec3(-w2, h2, -d2), Vec2(0.0f, 0.0f) };
	vtx[2] = VertexTextureData{ Vec3(w2, h2, -d2), Vec2(1.0f, 0.0f) };
	vtx[3] = VertexTextureData{ Vec3(w2, -h2, -d2), Vec2(1.0f, 1.0f) };
	// 뒷면
	vtx[4] = VertexTextureData{ Vec3(-w2, -h2, d2), Vec2(1.0f, 1.0f) };
	vtx[5] = VertexTextureData{ Vec3(w2, -h2, d2), Vec2(0.0f, 1.0f) };
	vtx[6] = VertexTextureData{ Vec3(w2, h2, d2), Vec2(0.0f, 0.0f) };
	vtx[7] = VertexTextureData{ Vec3(-w2, h2, d2), Vec2(1.0f, 1.0f) };
	// 윗면
	vtx[8] = VertexTextureData{ Vec3(-w2, h2, -d2), Vec2(0.0f, 1.0f) };
	vtx[9] = VertexTextureData{ Vec3(-w2, h2, d2), Vec2(0.0f, 0.0f) };
	vtx[10] = VertexTextureData{ Vec3(w2, h2, d2), Vec2(1.0f, 0.0f) };
	vtx[11] = VertexTextureData{ Vec3(w2, h2, -d2), Vec2(1.0f, 1.0f) };
	// 아랫면
	vtx[12] = VertexTextureData{ Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f) };
	vtx[13] = VertexTextureData{ Vec3(w2, -h2, -d2), Vec2(0.0f, 1.0f) };
	vtx[14] = VertexTextureData{ Vec3(w2, -h2, d2), Vec2(0.0f, 0.0f) };
	vtx[15] = VertexTextureData{ Vec3(-w2, -h2, d2), Vec2(1.0f, 0.0f) };
	// 왼쪽
	vtx[16] = VertexTextureData{ Vec3(-w2, -h2, d2), Vec2(0.0f, 1.0f) };
	vtx[17] = VertexTextureData{ Vec3(-w2, h2, d2), Vec2(0.0f, 0.0f) };
	vtx[18] = VertexTextureData{ Vec3(-w2, h2, -d2), Vec2(1.0f, 0.0f) };
	vtx[19] = VertexTextureData{ Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f) };
	// 오른쪽
	vtx[20] = VertexTextureData{ Vec3(w2, -h2, -d2), Vec2(0.0f, 1.0f) };
	vtx[21] = VertexTextureData{ Vec3(w2, h2, -d2), Vec2(0.0f, 0.0f) };
	vtx[22] = VertexTextureData{ Vec3(w2, h2, d2), Vec2(1.0f, 0.0f) };
	vtx[23] = VertexTextureData{ Vec3(w2, -h2, d2), Vec2(1.0f, 1.0f) };

	geometry->SetVertices(vtx);

	vector<uint32> idx(36);
	// 앞면
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	// 뒷면
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	// 윗면
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// 아랫면
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// 왼쪽
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// 오른쪽
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry, float radius, int slices, int stacks)
{

	// 정점 버퍼 생성
	std::vector<VertexTextureData> vertices;
	for (int stack = 0; stack <= stacks; ++stack)
	{
		float phi = XM_PI * static_cast<float>(stack) / static_cast<float>(stacks);
		for (int slice = 0; slice <= slices; ++slice)
		{
			float theta = XM_2PI * static_cast<float>(slice) / static_cast<float>(slices);
			float x = radius * sinf(phi) * cosf(theta);
			float y = radius * cosf(phi);
			float z = radius * sinf(phi) * sinf(theta);

			VertexTextureData vertex;
			vertex.position = Vec3(x, y, z);
			vertex.uv = Vec2(static_cast<float>(slice) / static_cast<float>(slices),
				static_cast<float>(stack) / static_cast<float>(stacks));
			vertices.push_back(vertex);
		}
	}
	geometry->SetVertices(vertices);

	// 인덱스 버퍼 생성
	std::vector<uint32> indices;
	for (int stack = 0; stack < stacks; ++stack)
	{
		for (int slice = 0; slice < slices; ++slice)
		{
			int v0 = stack * (slices + 1) + slice;
			int v1 = v0 + 1;
			int v2 = (stack + 1) * (slices + 1) + slice;
			int v3 = v2 + 1;

			indices.push_back(v0);
			indices.push_back(v2);
			indices.push_back(v1);

			indices.push_back(v1);
			indices.push_back(v2);
			indices.push_back(v3);
		}
	}
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ)
{

	// 정점 버퍼 생성
	vector<VertexTextureData> vertices;
	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureData v;
			v.position = Vec3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = Vec2(static_cast<float>(x), static_cast<float>(z));
			vertices.push_back(v);
		}
	}
	geometry->SetVertices(vertices);

	// 인덱스 버퍼 생성
	vector<uint32> indices;
	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			indices.push_back((sizeX + 1) * (z + 1) + (x));
			indices.push_back((sizeX + 1) * (z) + (x + 1));
			indices.push_back((sizeX + 1) * (z) + (x));

			indices.push_back((sizeX + 1) * (z) + (x + 1));
			indices.push_back((sizeX + 1) * (z + 1)+(x));
			indices.push_back((sizeX + 1) * (z + 1)+(x + 1));
		}
	}
	geometry->SetIndices(indices);
}
