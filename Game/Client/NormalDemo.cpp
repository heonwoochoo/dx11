#include "pch.h"
#include "NormalDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"

void NormalDemo::Init()
{
	_shader = make_shared<Shader>(L"Normal.fx");

	// Texture
	_texture = RESOURCES->Load<Texture>(L"Texture", L"..\\Resources\\Textures\\masteryi.jpg");

	// Object
	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	//GeometryHelper::CreateCube(_geometry);
	GeometryHelper::CreateSphere(_geometry, 1, 20, 20);
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

	// Caching
	_fxWorld = _shader->GetMatrix("World");
	_fxView = _shader->GetMatrix("View");
	_fxProjection = _shader->GetMatrix("Projection");
	_fxTexture = _shader->GetSRV("Texture0");
	_fxLightDir = _shader->GetVector("LightDir");
}

void NormalDemo::Update()
{
	_camera->Update();

}

void NormalDemo::Render()
{
	_fxWorld->SetMatrix((float*)&_world);
	_fxView->SetMatrix((float*)&Camera::S_MatView);
	_fxProjection->SetMatrix((float*)&Camera::S_MatProjection);
	_fxTexture->SetResource(_texture->GetComPtr().Get());
	_fxLightDir->SetFloatVector((float*)&_lightDir);

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
