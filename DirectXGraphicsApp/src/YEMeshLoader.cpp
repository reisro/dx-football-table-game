#include "YEMeshLoader.h"

YEMeshLoader::YEMeshLoader():
	_device(nullptr), _context(nullptr),
	_meshes(), _directory(),
	_textures()
{
}

YEMeshLoader::~YEMeshLoader()
{
}

bool YEMeshLoader::Load(IUnknown* device, IUnknown* context, std::string filename)
{
	_device = device;
	_context = context;

	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
		return false;

	this->_directory = filename.substr(0, filename.find_last_of("/\\"));
	
	processNode(pScene->mRootNode, pScene);

	return true;
}

void YEMeshLoader::Draw(IUnknown* context)
{
	for (size_t i = 0; i < _meshes.size(); ++i)
	{
		_meshes[i].Draw(_context);
	}
}

void YEMeshLoader::processNode(aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(this->processMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

YEMesh YEMeshLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<YEMeshVertex> vertices;
	std::vector<UINT> indices;
	std::vector<YETexture> textures;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		YEMeshVertex vertex;

		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<YETexture> diffuseMMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
		textures.insert(textures.end(), diffuseMMaps.begin(), diffuseMMaps.end());
	}

	return YEMesh(_device, vertices,indices, textures);
}

std::vector<YETexture> YEMeshLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene)
{
	std::vector<YETexture> textures;

	for (UINT i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// Check if texture was loaded before and if so, continue to next iteration
		bool skip = false;

		for (UINT j = 0; j < _textures.size(); j++)
		{
			if (std::strcmp(_textures[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(_textures[j]);
				skip = true;
				break;
			}
		}

		ID3D11Device* renderDevice = reinterpret_cast<ID3D11Device*>(_device);
		ID3D11DeviceContext* renderContext = reinterpret_cast<ID3D11DeviceContext*>(_context);

		if (!skip)
		{
			HRESULT hr;
			YETexture texture;

			const aiTexture* embeddedTexture = scene->GetEmbeddedTexture(str.C_Str());
			if (embeddedTexture != nullptr)
			{
				texture.texture = loadEmbeddedTexture(embeddedTexture);
			}
			else
			{
				std::string filename = std::string(str.C_Str());
				filename = _directory + "/" + filename;
				std::wstring filenamews = std::wstring(filename.begin(), filename.end());
				hr = CreateWICTextureFromFile(renderDevice, renderContext, filenamews.c_str(), nullptr, &texture.texture);

				if (FAILED(hr))
					DXLog("Texture could not be loaded...");
			}

			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->_textures.push_back(texture);
		}
	}

	return textures;
}

ID3D11ShaderResourceView* YEMeshLoader::loadEmbeddedTexture(const aiTexture* embeddedTexture)
{
	HRESULT hr;
	ID3D11ShaderResourceView* texture = nullptr;

	ID3D11Device* renderDevice = dynamic_cast<ID3D11Device*>(_device);

	if (embeddedTexture->mHeight != 0)
	{
		// Load an uncompressed ARGB8888 embedded texture
		D3D11_TEXTURE2D_DESC desc;
		desc.Width = embeddedTexture->mWidth;
		desc.Height = embeddedTexture->mHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subresourceData;
		subresourceData.pSysMem = embeddedTexture->pcData;
		subresourceData.SysMemPitch = embeddedTexture->mWidth * 4;
		subresourceData.SysMemSlicePitch = embeddedTexture->mWidth * embeddedTexture->mHeight * 4;

		ID3D11Texture2D* texture2D = nullptr;
		hr = renderDevice->CreateTexture2D(&desc, &subresourceData, &texture2D);

		if (FAILED(hr))
		{
			DXLog("Create Texture Failed");
		}

		hr = renderDevice->CreateShaderResourceView(texture2D, nullptr, &texture);
		if (FAILED(hr))
		{
			DXLog("Create Shader Resource View failed...");
		}

		return texture;
	}

	const size_t size = embeddedTexture->mWidth;

	ID3D11Device* renderDevice_ = dynamic_cast<ID3D11Device*>(_device);
	ID3D11DeviceContext* renderContext_ = dynamic_cast<ID3D11DeviceContext*>(_context);

	hr = CreateWICTextureFromMemory(renderDevice_, renderContext_, reinterpret_cast<const unsigned char*>(embeddedTexture->pcData), size, nullptr, &texture);
	if (FAILED(hr))
		DXLog("Texture couldn't be created from memory!");

	return texture;
}