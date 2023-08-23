#pragma once

#ifndef DX_RENDERINGDX11_H
#define DX_RENDERINGDX11_H

#include "DXRendering.h"
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

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
	void Clean() override;

	virtual ~DXRenderingDirectX11();

	static ID3D11Device*           d3dDevice;
	static ID3D11DeviceContext*    d3dDeviceContext;
	static IDXGISwapChain*         swapChain;
	static ID3D11RenderTargetView* mainRenderTargetView;

protected:

private:

};

#endif DX_RENDERINGDX11_H