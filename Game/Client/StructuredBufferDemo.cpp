#include "pch.h"
#include "StructuredBufferDemo.h"
#include "StructuredBuffer.h"

void StructredBufferDemo::Init()
{
	_shader = make_shared<Shader>(L"StructuredBufferDemo.fx");

	vector<Matrix> inputs(500, Matrix::Identity);

	auto buffer = make_shared<StructuredBuffer>(inputs.data(), sizeof(Matrix), 500, sizeof(Matrix), 500);
	
	_shader->GetSRV("Input")->SetResource(buffer->GetSRV().Get());
	_shader->GetUAV("Output")->SetUnorderedAccessView(buffer->GetUAV().Get());
	
	_shader->Dispatch(0, 0, 1, 1, 1);

	vector<Matrix> outputs(500);
	buffer->CopyFromOutput(outputs.data());
}

void StructredBufferDemo::Update()
{
	

}

void StructredBufferDemo::Render()
{
}
