#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Game.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"

MeshRenderer::MeshRenderer()
	:Super(ComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_mesh == nullptr || _material == nullptr) return;

	auto shader = _material->GetShader();
	if (shader == nullptr) return;

	// GlobalData
	shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();
	if (lightObj)
		shader->PushLightData(lightObj->GetLight()->GetLightDesc());

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