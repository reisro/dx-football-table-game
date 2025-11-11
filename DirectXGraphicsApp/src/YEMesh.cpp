#include "YEMesh.h"

YEMesh::YEMesh()
{
	
}

YEMesh::YEMesh(IUnknown* device, const std::vector<YEMeshVertex>& vertices, const std::vector<UINT>& indices, const std::vector<YETexture>& textures)
	:_vertices(vertices), _indices(indices), _textures(textures), _device(device), mVB(nullptr), mIB(nullptr)
{
	PrepareMesh(_device);
}

YEMesh::~YEMesh()
{
}

void YEMesh::PrepareMesh(IUnknown* device)
{
	D3D11_BUFFER_DESC vbufferDesc;
	vbufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vbufferDesc.ByteWidth = static_cast<UINT>(sizeof(YEMeshVertex) * _vertices.size());
	vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbufferDesc.CPUAccessFlags = 0;
	vbufferDesc.MiscFlags = 0;
	vbufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &_vertices[0];

	ID3D11Device* renderDevice = reinterpret_cast<ID3D11Device*>(device);

	HRESULT hr = renderDevice->CreateBuffer(&vbufferDesc, &initData, &mVB);

	if (FAILED(hr))
	{
		DXLog("Failed creating vertex buffer....");
	}

	D3D11_BUFFER_DESC ibufferDesc;
	ibufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	ibufferDesc.ByteWidth = static_cast<UINT>(sizeof(UINT) * _indices.size());
	ibufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	ibufferDesc.CPUAccessFlags = 0;
	ibufferDesc.MiscFlags = 0;
	ibufferDesc.StructureByteStride = 0;

	initData.pSysMem = &_indices[0];

	hr = renderDevice->CreateBuffer(&ibufferDesc, &initData, &mIB);

	if (FAILED(hr))
	{
		DXLog("Failed creating index buffer....");
	}
}

void YEMesh::Draw(IUnknown* context)
{
	UINT stride = sizeof(YEMeshVertex);
	UINT offset = 0;

	ID3D11DeviceContext* renderContext = reinterpret_cast<ID3D11DeviceContext*>(context);

	renderContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	renderContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	renderContext->PSSetShaderResources(0, 1, &_textures[0].texture);
	renderContext->DrawIndexed(static_cast<UINT>(_indices.size()), 0, 0);
}

void YEMesh::SetIndices(ID3D11Device* device, const USHORT* indices, UINT count)
{
}

void YEMesh::SetSubsetTable(std::vector<Subset>& subsetTable)
{
}

bool YEMesh::DoTheImportThing(const std::string& pFile) 
{
	//// Create an instance of the Importer class
	//Assimp::Importer importer;

	//// And have it read the given file with some example postprocessing
	//// Usually - if speed is not the most important aspect for you - you'll
	//// probably to request more postprocessing than we do in this example.
	//const aiScene* scene = importer.ReadFile(pFile,
	//	aiProcess_CalcTangentSpace |
	//	aiProcess_Triangulate |
	//	aiProcess_JoinIdenticalVertices |
	//	aiProcess_SortByPType);

	//// If the import failed, report it
	//if (nullptr == scene) {
	//	DXLog(importer.GetErrorString());
	//	return false;
	//}

	//// Now we can access the file's contents.
	////DoTheSceneProcessing(scene);

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}