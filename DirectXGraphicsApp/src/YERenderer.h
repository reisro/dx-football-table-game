#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

//-----------------------------------------------------------------------------
// Base Header Includes
//-----------------------------------------------------------------------------
#include "pch.h"
#include "DXSubsystem.h"
#include "YESceneObject.h"
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

typedef struct YEColor
{
	YEColor(yeFloat r, yeFloat g, yeFloat b, yeFloat a):
		red(r), green(g), blue(b), alpha(a)
	{
		Value = { red, green, blue, alpha };
	}

	yeFloat red;
	yeFloat green;
	yeFloat blue;
	yeFloat alpha;

	XMVECTORF32 Value;

} YEColor;

//-----------------------------------------------------------------------------
// Constant Colors
//-----------------------------------------------------------------------------
namespace YEngineColors
{
	XMGLOBALCONST YEColor WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST YEColor BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST YEColor RED = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST YEColor GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST YEColor BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST YEColor YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST YEColor CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST YEColor MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
}

// Renderer subsystem for DirectX
class DX_API YERenderer: public DXSubsystem
{
public:

	//-----------------------------------------------------------------------------
	// Constructors and Destructors
	//-----------------------------------------------------------------------------
	YERenderer();
	YERenderer(const YERenderer& rhs);
	~YERenderer();

	//-----------------------------------------------------------------------------
	// Global Function Declarations and Definitions
	//-----------------------------------------------------------------------------
	static void CreateInstance();
	static YERenderer* GetInstance();

	static bool initialized;

	//-----------------------------------------------------------------------------
	// Override Function Declarations
	//-----------------------------------------------------------------------------
	void Setup() override;
	bool Init()  override;
	void PostInit() override;
	void Clean() override;

	//-----------------------------------------------------------------------------
	// Rendering Functions
	//-----------------------------------------------------------------------------
	virtual void Render();
	virtual void BeginFrame();
	virtual void EndFrame();
	virtual void Cleanup();
	virtual void CreateBasicGeometry();
	virtual void CreateDefaultCube();
	virtual void LoadMesh(const wchar_t* pFileName);
	virtual void InitPipeline();
	virtual void BuildFX();
	virtual void CreateVertexLayout();
	virtual void CreatePixelLayout();
	virtual void OnRenderUI(bool* open, const char* msg);
	virtual IUnknown* GetDevice();
	virtual IUnknown* GetDeviceContext();
	virtual YESceneObject* GetSceneObject();

	bool createGeometryCmd;

protected:

	static YERenderer* Singleton;
	YESceneObject*	   _sceneObject;

private:
	IUnknown* _device;
	IUnknown* _deviceContext;
};

#endif _DX_RENDERING_H