#include "pch.h"
#include "InstancingManager.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "GameObject.h"

// �ν��Ͻ��� �ʿ��� ������Ʈ���� �����
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

	// �з� �ܰ�
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

		// �ϳ��� �־ ������ �ν��Ͻ��� �����ϴ� �������� �ۼ���
		const InstanceID instanceId = pair.first;
		for (int32 i = 0; i < vec.size(); i++)
		{
			const shared_ptr<GameObject>& gameObject = vec[i];

			InstancingData data;
			data.world = gameObject->GetTransform()->GetWorldMatrix();

			AddData(instanceId, data);
		}

		// ���̵� �� �׷��ִ� �� �� �ѹ��� ȣ��Ǿ���� -> �迭�� ù ��° ������Ʈ MeshRenderer�� ȣ��
		shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
		vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
	}
}

void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	// �з� �ܰ�
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

		// �ϳ��� �־ ������ �ν��Ͻ��� �����ϴ� �������� �ۼ���
		const InstanceID instanceId = pair.first;
		for (int32 i = 0; i < vec.size(); i++)
		{
			const shared_ptr<GameObject>& gameObject = vec[i];

			InstancingData data;
			data.world = gameObject->GetTransform()->GetWorldMatrix();

			AddData(instanceId, data);
		}

		// ���̵� �� �׷��ִ� �� �� �ѹ��� ȣ��Ǿ���� -> �迭�� ù ��° ������Ʈ MeshRenderer�� ȣ��
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
