#pragma once

#ifndef DX_RENDERINGDX11_H
#define DX_RENDERINGDX11_H

#include "DXRendering.h"

//-----------------------------------------------------------------------------
// Enum (Vertex Processing)
// Types of vertex processing when using graphics card
//-----------------------------------------------------------------------------

enum class D3DVERTEXPROCESSING
{
	SOFTWARE = 1,
	HARDWARE = 2
};

class DXRenderingDirectX11: public DXRendering
{
public:
	DXRenderingDirectX11();
	DXRenderingDirectX11(const DXRenderingDirectX11& rhs);

	// interface methods override
	void Setup()    override;
	bool Init()     override;
	void PostInit() override;

	virtual ~DXRenderingDirectX11();

protected:

private:

};

#endif DX_RENDERINGDX11_H