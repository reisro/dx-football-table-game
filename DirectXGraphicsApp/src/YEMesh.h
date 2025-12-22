#pragma once

#ifndef _YE_MESH_H_
#define _YE_MESH_H_

#include <d3d11.h>
#include <vector>
#include "DXAPI.h"
#include "DXTypes.h"
#include <DirectXMath.h>
#include "YEVector3.h"

using namespace DirectX;

struct YEMeshVertex
{
	yeFloat x, y, z;
	XMFLOAT2 texcoord;
};

struct YETexture
{
	std::string type;
	std::string path;
	ID3D11ShaderResourceView* texture;
};

class DX_API YEMesh
{
	public:
		
		YEMesh();
		YEMesh(IUnknown* device, const std::vector<YEMeshVertex>& vertices, const std::vector<UINT>& indices,
			const std::vector<YETexture>& textures);
		virtual ~YEMesh();

		void PrepareMesh(IUnknown* device);
		void Draw(IUnknown* context);

		void SetIndices(ID3D11Device* device, const USHORT* indices, UINT count);

		bool DoTheImportThing(const std::string& pFile);

public:
	std::vector<YEMeshVertex> _vertices;
	std::vector<UINT>         _indices;
	std::vector<YETexture>    _textures;
	IUnknown*                 _device;
	UINT					  _idMWorld;
	XMFLOAT4X4				  _mWorld;
	XMFLOAT4X4				  _mView;
	XMFLOAT4X4				  _mProj;

private:
		ID3D11Buffer* mVB;
		ID3D11Buffer* mIB;

		DXGI_FORMAT mIndexBufferFormat; // Always 16-bit
		UINT mVertexStride;
};

#endif
