#pragma once
#include "IExecute.h"
#include "Geometry.h"

class GameObject;

class CameraDemo : public IExecute
{

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<Shader> _shader;

	shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	Matrix _world = Matrix::Identity;

	// Camera
	shared_ptr<GameObject> _camera;

private:
	ComPtr<ID3DX11EffectMatrixVariable> _fxWorld;
	ComPtr<ID3DX11EffectMatrixVariable> _fxView;
	ComPtr<ID3DX11EffectMatrixVariable> _fxProjection;
};