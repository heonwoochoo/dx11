#include "pch.h"
#include "MaterialDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"

void MaterialDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"Lighting.fx");
	RENDER->Init(_shader);

	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto texture = RESOURCES->Load<Texture>(L"Texture", L"..\\Resources\\Textures\\masteryi.jpg");
			material->SetDiffuseMap(texture);
		}
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);

		RESOURCES->Add(L"MasterYi", material);
	}

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->GetTransform()->SetPosition(Vec3{ 0.f,0.f,-10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"MasterYi");
		_obj->GetMeshRenderer()->SetMaterial(material);
	}

	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f,0.f,2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"MasterYi")->Clone();
		
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Color(1.f, 0.f, 0.f, 1.f);
		desc.diffuse = Vec4(0.2f);

		_obj2->GetMeshRenderer()->SetMaterial(material);
	}
}

void MaterialDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		RENDER->PushLightData(lightDesc);
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.2f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		//desc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

		RENDER->PushMaterialData(desc);
		_obj->Update();
	}
	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Color(0.5f, 0.5f, 0.5f, 1.f);
		//desc.emissive = Color(1.f, 0.f, 0.f, 1.f);
		RENDER->PushMaterialData(desc);
		_obj2->Update();
	}
	
}

void MaterialDemo::Render()
{

}
