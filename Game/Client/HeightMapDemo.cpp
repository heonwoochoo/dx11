#include "pch.h"
#include "HeightMapDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"Terrain.fx");

	// Texture
	_texture = RESOURCES->Load<Texture>(L"Texture", L"..\\Resources\\Textures\\Terrain\\RidgeTexture.png");
	_heightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Textures\\Terrain\\RidgeHeightMap.png");

	const int32 width = _heightMap->GetSize().x;
	const int32 height = _heightMap->GetSize().y;

	const DirectX::ScratchImage& info = _heightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();

	// Object
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, width, height);

	// CPU
	{
		// 캐스팅으로 const를 강제로 없앤다
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());
		
		for (int32 z = 0; z < height; z++)
		{
			for (int32 x = 0; x < width; x++)
			{
				int32 idx = width * z + x;
				uint8 pixelheight = pixelBuffer[idx] / 255.f * 25.f;
				v[idx].position.y = pixelheight;	// 높이보정
			}
		}
	}

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->GetTransform()->SetPosition(Vec3{ 0.f,0.f,-5.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	_camera->GetTransform()->SetPosition(Vec3(0.f, 5.f, 0.f));
	_camera->GetTransform()->SetRotation(Vec3(25.f, 0.f, 0.f));

	// Caching
	_fxWorld = _shader->GetMatrix("World");
	_fxView = _shader->GetMatrix("View");
	_fxProjection = _shader->GetMatrix("Projection");
	_fxTexture = _shader->GetSRV("Texture0");
}

void HeightMapDemo::Update()
{
	_camera->Update();

}

void HeightMapDemo::Render()
{
	_fxWorld->SetMatrix((float*)&_world);
	_fxView->SetMatrix((float*)&Camera::S_MatView);
	_fxProjection->SetMatrix((float*)&Camera::S_MatProjection);
	_fxTexture->SetResource(_texture->GetComPtr().Get());

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
