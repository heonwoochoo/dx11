#pragma once
class RawBuffer
{
public:
	RawBuffer(void* inputData, uint32 inputByte, uint32 outputByte);
	~RawBuffer();

public:
	void CreateBuffer();
	void CopyToInput(void* data);
	void CopyFromOutput(void* data);

public:
	ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }
	ComPtr<ID3D11UnorderedAccessView> GetUAV() { return _uav; }

private:
	void CreateInput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV();
	void CreateResult();

private:
	// GPU에게 건네주는 버퍼
	ComPtr<ID3D11Buffer> _input;

	// input 버퍼를 묘사하는 View가 필요
	ComPtr<ID3D11ShaderResourceView> _srv;

	// GPU로부터 받아오는 버퍼
	ComPtr<ID3D11Buffer> _output;

	// output 버퍼를 묘사하는 view를 통해 받아옴
	ComPtr<ID3D11UnorderedAccessView> _uav;

	// 최종 결과를 취합하기 위한 용도
	ComPtr<ID3D11Buffer> _result;

private:
	// 어떤 데이터가 들어올지 예측을 못하기에 void* 로 정의
	void* _inputData;

	// 정보의 크기
	uint32 _inputByte = 0;

	// 출력 데이터의 크기
	uint32 _outputByte = 0;
};

