#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Game.h"
#include "Texture.h"

MeshRenderer::MeshRenderer()
	:Super(ComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr) return;

	// Caching
	if (_fxWorld == nullptr) _fxWorld = _shader->GetMatrix("World");
	if(_fxView == nullptr) _fxView = _shader->GetMatrix("View");
	if (_fxProjection == nullptr) _fxProjection = _shader->GetMatrix("Projection");
	if (_fxTexture == nullptr) _fxTexture = _shader->GetSRV("Texture0");
	if (_fxLightDir == nullptr) _fxLightDir = _shader->GetVector("LightDir");

	auto world = GetTransform()->GetWorldMatrix();
	_fxWorld->SetMatrix((float*)&world);
	_fxView->SetMatrix((float*)&Camera::S_MatView);
	_fxProjection->SetMatrix((float*)&Camera::S_MatProjection);
	_fxTexture->SetResource(_texture->GetComPtr().Get());
	
	// TEMP
	Vec3 _lightDir = Vec3(0.f, 0.f, 1.f);
	_fxLightDir->SetFloatVector((float*)&_lightDir);

	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();

	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}