#pragma once
#include "Component.h"

class Texture;
class Mesh;
class Material;

class MeshRenderer : public Component
{
	using Super = Component;

public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }

private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Texture> _texture;
	shared_ptr<Shader> _shader;

private:
	// caching shader variable
	ComPtr<ID3DX11EffectMatrixVariable>			_fxWorld;
	ComPtr<ID3DX11EffectMatrixVariable>			_fxView;
	ComPtr<ID3DX11EffectMatrixVariable>			_fxProjection;
	ComPtr<ID3DX11EffectShaderResourceVariable> _fxTexture;
	ComPtr<ID3DX11EffectVectorVariable> 		_fxLightDir;
};

