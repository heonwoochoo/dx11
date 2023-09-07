#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Game.h"
#include "Texture.h"
#include "Material.h"

MeshRenderer::MeshRenderer()
	:Super(ComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr) return;
//
//	if (_fxTexture == nullptr) _fxTexture = _shader->GetSRV("Texture0");
//	_fxTexture->SetResource(_texture->GetComPtr().Get());
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{ world });
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _material == nullptr) return;
//
//	auto shader = _material->GetShader();
//	if (shader == nullptr) return;
//
//	_material->Update();
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{ world });
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

void MeshRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_mesh == nullptr || _material == nullptr) return;

	auto shader = _material->GetShader();
	if (shader == nullptr) return;

	// Texture
	_material->Update();

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();
	buffer->PushData();	// 같은 ID값의 모든 인스턴스 대상의 정보를 GPU로 넘김

	shader->DrawIndexedInstanced(0, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}

// 포인터의 주소값을 이용하여 아이디를 발급
InstanceID MeshRenderer::GetInstanceID()
{
	return make_pair((uint64)_mesh.get(), (uint64)_material.get());
}