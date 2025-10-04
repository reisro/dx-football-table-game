#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

//-----------------------------------------------------------------------------
// Base Header Includes
//-----------------------------------------------------------------------------
#include "pch.h"
#include "DXSubsystem.h"
#include <d3d11.h>

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

protected:

	static YERenderer* Singleton;

private:

};

#endif _DX_RENDERING_H
