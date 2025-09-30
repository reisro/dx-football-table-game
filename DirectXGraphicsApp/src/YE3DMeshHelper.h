#pragma once

#ifndef _YE_MESH_HELPER_H_
#define _YE_MESH_HELPER_H_

#include <d3dx11.h>
#include <vector>
#include <string>

class YE3DMeshHelper
{
public:
	YE3DMeshHelper();
	virtual ~YE3DMeshHelper();

	static ID3D11ShaderResourceView* CreateTexture2DArraySRV(
		ID3D11Device* device, ID3D11DeviceContext* context,
		std::vector<std::wstring>& filenames,
		DXGI_FORMAT format = DXGI_FORMAT_FROM_FILE,
		UINT filter = D3DX11_FILTER_NONE,
		UINT mipFilter = D3DX11_FILTER_LINEAR);

	static ID3D11ShaderResourceView* CreateRandomTexture1DSRV(ID3D11Device* device);
};

#endif