#pragma once
#include "IExecute.h"

class InstancingDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<GameObject> _camera;
	vector<shared_ptr<GameObject>> _objs;

private:
	// INSTANCING
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;

	vector<Matrix> _worlds;
	shared_ptr<VertexBuffer> _instanceBuffer;
};

