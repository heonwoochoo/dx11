#include "pch.h"
#include "InstancingBuffer.h"

InstancingBuffer::InstancingBuffer()
{
	CreateBuffer(MAX_MESH_INSTANCE);
}

InstancingBuffer::~InstancingBuffer()
{
}

// 데이터가 언제든지 바뀔 수 있기 때문에 매 프레임마다 실행
void InstancingBuffer::ClearData()
{
	_data.clear();
}

void InstancingBuffer::AddData(InstancingData& data)
{
	_data.push_back(data);
}

// GPU에게 데이터를 넘겨준다
void InstancingBuffer::PushData()
{
	const uint32 dataCount = GetCount();
	if (dataCount > _maxCount)
		CreateBuffer(dataCount);

	D3D11_MAPPED_SUBRESOURCE subResource;

	DC->Map(_instanceBuffer->GetComPtr().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		::memcpy(subResource.pData, _data.data(), sizeof(InstancingData) * dataCount);
	}
	DC->Unmap(_instanceBuffer->GetComPtr().Get(), 0);

	_instanceBuffer->PushData();
}

void InstancingBuffer::CreateBuffer(uint32 maxCount)
{
	_maxCount = maxCount;
	_instanceBuffer = make_shared<VertexBuffer>();

	vector<InstancingData> temp(maxCount);
	_instanceBuffer->Create(temp, /*slot*/1, /*cputWrite*/true);
}
