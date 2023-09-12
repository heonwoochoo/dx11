#pragma once
#include "IExecute.h"

class TextureBufferDemo : public IExecute
{
	struct Input
	{
		float value;
	};

	struct Output
	{
		uint32 groupID[3];
		uint32 groupThreadID[3];
		uint32 dispatchThreadID[3];
		uint32 groupIndex;
		float value;
	};

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Shader> _shader;

private:
	ComPtr<ID3D11ShaderResourceView> MakeComputeShaderTexture();

};

