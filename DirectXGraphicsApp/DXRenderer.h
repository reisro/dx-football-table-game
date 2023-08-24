#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

#include "pch.h"
#include "DXSubsystem.h"
#include "dear_imgui/backends/imgui_impl_dx11.h"
#include <d3d11.h>

class DX_API DXRenderer: public DXSubsystem
{
public:
	DXRenderer();
	DXRenderer(const DXRenderer& rhs);
	virtual ~DXRenderer();

	static bool initialized;

	static void CreateInstance();

	void Setup() override;
	bool Init()  override;
	void PostInit() override;
	void Clean() override;

	virtual DXRenderer* GetInstance();

	HWND renderWindow;

protected:

	static DXRenderer* Singleton;

private:

};


#endif _DX_RENDERING_H
