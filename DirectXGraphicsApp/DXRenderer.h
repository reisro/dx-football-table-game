#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

#include "pch.h"
#include "DXSubsystem.h"
#include <d3d11.h>

class DX_API DXRenderer: public DXSubsystem
{
public:
	DXRenderer();
	DXRenderer(const DXRenderer& rhs);
	virtual ~DXRenderer();

	static bool initialized;

	static void CreateInstance();
	static DXRenderer* GetInstance();

	void Setup() override;
	bool Init()  override;
	void PostInit() override;
	void Clean() override;

	virtual void Render();
	virtual void BeginFrame();
	virtual void EndFrame();

	HWND renderWindow;

protected:

	static DXRenderer* Singleton;

private:

};


#endif _DX_RENDERING_H
