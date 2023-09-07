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

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetPass(uint8 pass) { _pass = pass; }
	
	void RenderInstancing(shared_ptr<class InstancingBuffer>& buffer);

	InstanceID GetInstanceID();

private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
	uint8 _pass = 0;
};

