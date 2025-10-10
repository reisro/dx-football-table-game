#pragma once

#ifndef _YE_MESH_H_
#define _YE_MESH_H_

#include <d3d11.h>
#include <vector>
#include "DXAPI.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>              // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class YEMesh
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
		virtual ~YEMesh();

		template <typename VertexType>
		void SetVertices(ID3D11Device* device, const VertexType* vertices, UINT count);

		void SetIndices(ID3D11Device* device, const USHORT* indices, UINT count);

		void SetSubsetTable(std::vector<Subset>& subsetTable);

		void Draw(ID3D11DeviceContext* dc, UINT subsetId);

		bool DoTheImportThing(const std::string& pFile);

private:
		YEMesh(const YEMesh& rhs);
		YEMesh& operator=(const YEMesh& rhs);

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