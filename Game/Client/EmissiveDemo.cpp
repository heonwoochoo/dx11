#include "pch.h"
#include "EmissiveDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"

void EmissiveDemo::Init()
{
	_shader = make_shared<Shader>(L"Lighting_Emissive.fx");
	RENDER->Init(_shader);

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
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Texture", L"..\\Resources\\Textures\\masteryi.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f,0.f,2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Texture", L"..\\Resources\\Textures\\masteryi.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}
}

void EmissiveDemo::Update()
{
	_camera->Update();

	RENDER->Update();

	{
		Vec4 materialEmissive(1.f, 0.f, 0.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj->Update();
	}
	{
		Vec4 materialEmissive(0.f, 1.f, 0.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj2->Update();
	}
	
}

void EmissiveDemo::Render()
{


}