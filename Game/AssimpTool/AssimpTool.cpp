#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// fbx -> memory
		converter->ReadAssetFile(L"Dragon/Dragon 2.5_fbx.fbx");

		// memory -> custom data (file)
		converter->ExportMaterialData(L"Dragon/Dragon");
		converter->ExportModelData(L"Dragon/Dragon");

		// custom data (file) -> memory 
	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
