#pragma once
#include "IExecute.h"

class StructredBufferDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Shader> _shader;
};

