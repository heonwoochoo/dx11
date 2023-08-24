#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Types.h"
#include "Define.h"

// STL
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

// WIN
#include <windows.h>
#include <assert.h>
#include <optional>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#include <Effects11\d3dx11effect.h>
// Libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// Managers
#include "Game.h"
#include "Graphics.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"

#define CHECK(p)	assert(SUCCEEDED(p))
#define GAME		GET_SINGLE(Game)		
#define GRAPHICS	GET_SINGLE(Graphics)
#define DEVICE		GRAPHICS->GetDevice()
#define DC			GRAPHICS->GetDeviceContext()
#define INPUT		GET_SINGLE(InputManager)
#define TIME		GET_SINGLE(TimeManager)
#define DT			TIME->GetDeltaTime()
#define RESOURCES	GET_SINGLE(ResourceManager)

// Engine
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "IExecute.h"

//#include "GameObject.h"
//#include "Transform.h"
//#include "Texture.h"
//#include "Mesh.h"