#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

#include "DXAPI.h"
#include "DXSubsystem.h"
#include "dear_imgui/backends/imgui_impl_dx11.h"
#include <d3d11.h>

class DX_API DXRendering: public DXSubsystem
{
public:
	DXRendering();
	DXRendering(const DXRendering& rhs);
	virtual ~DXRendering();

	void Setup() override;
	bool Init()  override;
	void PostInit() override;

protected:

	static DXRendering* instance;

private:

};

#endif _DX_RENDERING_H
