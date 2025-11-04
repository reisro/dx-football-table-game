#pragma once

#ifndef _YE_MESH_LOADER_H_
#define _YE_MESH_LOADER_H_

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "YEMesh.h"
#include "YETextureLoader.h"

class YEMeshLoader
{
public:
	YEMeshLoader();
	virtual ~YEMeshLoader();

	bool Load(IUnknown* device, IUnknown* context, const wchar_t* pFileName);
	std::vector<YEMesh> getLoadedMeshes();

private:
	IUnknown*		_device;
	IUnknown*		_context;

	std::vector<YEMesh>    _meshes;
	std::string			   _directory;
	std::vector<YETexture> _textures;

	void processNode(aiNode* node, const aiScene* scene);
	YEMesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<YETexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
	ID3D11ShaderResourceView* loadEmbeddedTexture(const aiTexture* embeddedTexture);
};

#endif _YE_MESH_LOADER_H_
