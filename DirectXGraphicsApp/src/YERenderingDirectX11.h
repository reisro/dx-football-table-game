#pragma once

#ifndef YE_RENDERINGDX11_H
#define YE_RENDERINGDX11_H

#include "YERenderer.h"
#include "YEWinAppWindow.h"
#include "d3dx11Effect.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3dcompiler.h>
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

struct ConstantBuffer {
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

class YERenderingDirectX11: public YERenderer
{
public:

	YERenderingDirectX11();
	YERenderingDirectX11(const YERenderingDirectX11& rhs);

	// interface methods override
	void Setup()    override;
	bool Init()     override;
	void PostInit() override;
	void Clean() override;

	~YERenderingDirectX11();

	HRESULT CompileShaderFromFile(LPCWSTR pFileName, const D3D_SHADER_MACRO* pDefines, LPCSTR pEntryPoint, LPCSTR pShaderModel, ID3DBlob** ppBytecodeBlob);
	void CreateRenderTargetView();
	void SetViewport();
	
	void Render() override;
	void BeginFrame() override;
	void EndFrame() override;
	void Cleanup() override;
	void CreateDefaultCube() override;
	void LoadMesh() override;
	void InitPipeline() override;
	void BuildFX() override;
	void CreateVertexLayout() override;
	void CreatePixelLayout() override;
	IUnknown* GetDevice() override;
	IUnknown* GetDeviceContext() override;

protected:

	ID3D11Device*				 d3dDevice;
	ID3D11DeviceContext*		 d3dDeviceContext;
	ID3D11RenderTargetView*		 mainRenderTargetView;
	ID3D11RenderTargetView*		 backBuffer;
	D3D11_TEXTURE2D_DESC		 depthStencilDesc;
	ID3D11Texture2D*             depthStencilBuffer;
	ID3D11DepthStencilView*		 depthStencilView;
	ID3D11RasterizerState*		 rasterstate;
	ID3D11SamplerState*			 texSamplerState;
	ID3D11DepthStencilState*     depthStencilStateDesc;
	ID3D11Buffer*				 pConstantBuffer;
	ID3D11VertexShader*			 pVS;
	ID3D11PixelShader*			 pPS;
	ID3D11Texture2D*			 tBackBuffer;
	IDXGISwapChain*				 swapChain;
	IDXGIDevice*				 dxgiDevice;
	IDXGIAdapter*				 dxgiAdapter;
	IDXGIFactory*				 dxgiFactory;
	DXGI_SWAP_CHAIN_DESC		 swapChainDesc;
	D3D_FEATURE_LEVEL			 featureLevel;
	D3D11_VIEWPORT				 viewport;
	YEWinAppWindow*				 outputWindow;
	UINT						 m4xMsaaQuality;
	bool						 enable4xMsaa;

private:
	ID3D11Buffer*				 mCubeVB;
	ID3D11Buffer*				 mCubeIB;
	ID3D11InputLayout*           inputLayout;
	ID3DX11Effect*				 defaultColorFX;
	ID3DX11EffectTechnique*		 defaultEffectTechnique;
	ID3DX11EffectMatrixVariable* fxWorldViewProj;

	XMFLOAT4X4                  mWorld;
	XMFLOAT4X4                  mView;
	XMFLOAT4X4                  mProj;
};

#endif YE_RENDERINGDX11_H