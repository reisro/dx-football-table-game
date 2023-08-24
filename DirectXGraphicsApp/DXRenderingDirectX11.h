#pragma once

#ifndef DX_RENDERINGDX11_H
#define DX_RENDERINGDX11_H

#include "DXRenderer.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <sstream>

//-----------------------------------------------------------------------------
// Enum (Vertex Processing)
// Types of vertex processing when using graphics card
//-----------------------------------------------------------------------------

enum class D3DVERTEXPROCESSING
{
	SOFTWARE = 1,
	HARDWARE = 2
};

class DXRenderingDirectX11: public DXRenderer
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

	ID3D11Device*           d3dDevice;
	ID3D11DeviceContext*    d3dDeviceContext;
	IDXGISwapChain*         swapChain;
	ID3D11RenderTargetView* mainRenderTargetView;
	DXGI_SWAP_CHAIN_DESC    swapChainDesc;
	ID3D11RenderTargetView* backBuffer;
	D3D_FEATURE_LEVEL		featureLevel;

protected:

private:

};

#endif DX_RENDERINGDX11_H