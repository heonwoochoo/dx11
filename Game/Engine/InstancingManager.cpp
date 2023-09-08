#include "pch.h"
#include "InstancingManager.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "GameObject.h"

// 인스턴싱이 필요한 오브젝트들을 골라내자
void InstancingManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
	ClearData();

	RenderMeshRenderer(gameObjects);
	RenderModelRenderer(gameObjects);
}

void InstancingManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		shared_ptr<InstancingBuffer>& buffer = pair.second;
		buffer->ClearData();
	}
}

void InstancingManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// 분류 단계
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		// 하나만 있어도 무조건 인스턴싱을 적용하는 버전으로 작성됨
		const InstanceID instanceId = pair.first;
		for (int32 i = 0; i < vec.size(); i++)
		{
			const shared_ptr<GameObject>& gameObject = vec[i];

			InstancingData data;
			data.world = gameObject->GetTransform()->GetWorldMatrix();

			AddData(instanceId, data);
		}

		// 아이디 당 그려주는 건 딱 한번만 호출되어야함 -> 배열의 첫 번째 오브젝트 MeshRenderer만 호출
		shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
		vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
	}
}

void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// 분류 단계
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetModelRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		// 하나만 있어도 무조건 인스턴싱을 적용하는 버전으로 작성됨
		const InstanceID instanceId = pair.first;
		for (int32 i = 0; i < vec.size(); i++)
		{
			const shared_ptr<GameObject>& gameObject = vec[i];

			InstancingData data;
			data.world = gameObject->GetTransform()->GetWorldMatrix();

			AddData(instanceId, data);
		}

		// 아이디 당 그려주는 건 딱 한번만 호출되어야함 -> 배열의 첫 번째 오브젝트 MeshRenderer만 호출
		shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
		vec[0]->GetModelRenderer()->RenderInstancing(buffer);
	}
}

void InstancingManager::AddData(InstanceID instanceId, InstancingData& data)
{
	if (_buffers.find(instanceId) == _buffers.end())
		_buffers[instanceId] = make_shared<InstancingBuffer>();

	_buffers[instanceId]->AddData(data);
}
