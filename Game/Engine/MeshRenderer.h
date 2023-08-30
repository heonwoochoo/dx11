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
	void SetMaterial(shared_ptr<Material> material) { _material = material; }

	// Legacy
	void SetTexture(shared_ptr<Texture> texture) { }
	void SetShader(shared_ptr<Shader> shader) {  }

private:
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

