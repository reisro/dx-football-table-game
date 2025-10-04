#pragma once

#ifndef DX_RENDERINGDX11_H
#define DX_RENDERINGDX11_H

#include "DXRenderer.h"
#include "YEWinAppWindow.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <sstream>

using RGBA = float[4];

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

	~DXRenderingDirectX11();

	void CreateRenderTargetView();
	void SetViewport();
	
	void Render() override;
	void BeginFrame() override;
	void EndFrame() override;
	void Cleanup() override;

	ID3D11Device*				d3dDevice;
	ID3D11DeviceContext*		d3dDeviceContext;
	ID3D11RenderTargetView*		mainRenderTargetView;
	ID3D11RenderTargetView*		backBuffer;
	ID3D11Texture2D*			tBackBuffer;
	IDXGISwapChain*				swapChain;
	IDXGIDevice*				dxgiDevice;
	IDXGIAdapter*				dxgiAdapter;
	IDXGIFactory*				dxgiFactory;
	DXGI_SWAP_CHAIN_DESC		swapChainDesc;
	D3D_FEATURE_LEVEL			featureLevel;
	D3D11_VIEWPORT				viewport;
	YEWinAppWindow*				outputWindow;
	UINT						m4xMsaaQuality;

protected:

private:

};

#endif DX_RENDERINGDX11_H