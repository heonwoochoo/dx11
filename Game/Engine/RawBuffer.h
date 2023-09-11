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
	// GPU���� �ǳ��ִ� ����
	ComPtr<ID3D11Buffer> _input;

	// input ���۸� �����ϴ� View�� �ʿ�
	ComPtr<ID3D11ShaderResourceView> _srv;

	// GPU�κ��� �޾ƿ��� ����
	ComPtr<ID3D11Buffer> _output;

	// output ���۸� �����ϴ� view�� ���� �޾ƿ�
	ComPtr<ID3D11UnorderedAccessView> _uav;

	// ���� ����� �����ϱ� ���� �뵵
	ComPtr<ID3D11Buffer> _result;

private:
	// � �����Ͱ� ������ ������ ���ϱ⿡ void* �� ����
	void* _inputData;

	// ������ ũ��
	uint32 _inputByte = 0;

	// ��� �������� ũ��
	uint32 _outputByte = 0;
};

