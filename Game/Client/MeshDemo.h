#pragma once
#include "IExecute.h"
#include "Geometry.h"

class GameObject;

class MeshDemo : public IExecute
{

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<Shader> _shader;

	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _camera;

};