#include "pch.h"
#include "SceneDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Shader.h"
#include "Model.h"
#include "ModelAnimator.h"
#include "ModelRenderer.h"
#include "Light.h"

void SceneDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"RenderDemo.fx");

	// Camera
	{
		auto camera = make_shared<GameObject>();
		camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
		camera->AddComponent(make_shared<Camera>());
		camera->AddComponent(make_shared<CameraScript>());
		CUR_SCENE->Add(camera);
	}

	// Light
	{
		auto light = make_shared<GameObject>();
		light->AddComponent(make_shared<Light>());
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.1f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		light->GetLight()->SetLightDesc(lightDesc);
		CUR_SCENE->Add(light);
	}

	//Animation
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Kachujin/Kachujin");
	m1->ReadMaterial(L"Kachujin/Kachujin");
	m1->ReadAnimation(L"Kachujin/Idle");
	m1->ReadAnimation(L"Kachujin/Run");
	m1->ReadAnimation(L"Kachujin/Slash");

	for (int32 i = 0; i < 500; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelAnimator>(_shader));
		obj->GetModelAnimator()->SetModel(m1);
		obj->GetModelAnimator()->SetPass(2);

		CUR_SCENE->Add(obj);
	}

	// Model
	shared_ptr<Model> m2 = make_shared<Model>();
	m2->ReadModel(L"House/House");
	m2->ReadMaterial(L"House/House");

	for (int32 i = 0; i < 100; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));

		obj->AddComponent(make_shared<ModelRenderer>(_shader));
		{
			obj->GetModelRenderer()->SetModel(m2);
			obj->GetModelRenderer()->SetPass(1);
		}
		CUR_SCENE->Add(obj);
	}

	//RENDER->Init(_shader);
}

void SceneDemo::Update()
{
	

}

void SceneDemo::Render()
{
}
