#include "YEMesh.h"

YEMesh::YEMesh()
{
}

YEMesh::~YEMesh()
{
}

void YEMesh::SetIndices(ID3D11Device* device, const USHORT* indices, UINT count)
{
}

void YEMesh::SetSubsetTable(std::vector<Subset>& subsetTable)
{
}

void YEMesh::Draw(ID3D11DeviceContext* dc, UINT subsetId)
{
}

bool YEMesh::DoTheImportThing(const std::string& pFile) 
{
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		DXLog(importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	//DoTheSceneProcessing(scene);

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

YEMesh& YEMesh::operator=(const YEMesh& rhs)
{
	// TODO: return ステートメントをここに挿入します
	return *this;
}
