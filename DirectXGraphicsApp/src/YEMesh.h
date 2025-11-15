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

		struct Subset
		{
			Subset() :
				Id(-1),
				VertexStart(0), VertexCount(0),
				FaceStart(0), FaceCount(0) 
			{
			}

			UINT Id;
			UINT VertexStart;
			UINT VertexCount;
			UINT FaceStart;
			UINT FaceCount;
		};
		
		YEMesh();
		YEMesh(IUnknown* device, const std::vector<YEMeshVertex>& vertices, const std::vector<UINT>& indices,
			const std::vector<YETexture>& textures);
		virtual ~YEMesh();

		void PrepareMesh(IUnknown* device);
		void Draw(IUnknown* context);

		template <typename VertexType>
		void SetVertices(ID3D11Device* device, const VertexType* vertices, UINT count);

		void SetIndices(ID3D11Device* device, const USHORT* indices, UINT count);

		void SetSubsetTable(std::vector<Subset>& subsetTable);

		//void Draw(ID3D11DeviceContext* dc, UINT subsetId);

		bool DoTheImportThing(const std::string& pFile);

public:
	std::vector<YEMeshVertex> _vertices;
	std::vector<UINT>         _indices;
	std::vector<YETexture>    _textures;
	IUnknown*                 _device;
	XMFLOAT4X4				  _mWorld;
	XMFLOAT4X4				  _mView;
	XMFLOAT4X4				  _mProj;

private:
		ID3D11Buffer* mVB;
		ID3D11Buffer* mIB;

		DXGI_FORMAT mIndexBufferFormat; // Always 16-bit
		UINT mVertexStride;

		std::vector<Subset> mSubsetTable;
};

#endif

template<typename VertexType>
inline void YEMesh::SetVertices(ID3D11Device* device, const VertexType* vertices, UINT count)
{
	ReleaseCOM(mVB);

	mVertexStride = sizeof(VertexType);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(VertexType) * count;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;

	HR(device->CreateBuffer(&vbd, &vinitData, &mVB));
}