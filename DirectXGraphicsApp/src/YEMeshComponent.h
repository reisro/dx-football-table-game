#pragma once

#ifndef _YE_MESH_COMPONENT_H_
#define _YE_MESH_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEMeshLoader.h"

class DX_API YEMeshComponent : public YEBaseComponent
{
public:

	YEMeshComponent();
	YEMeshComponent(YEGameObject* owner, const char* pFileName);

	virtual ~YEMeshComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	YEGameObject* GetGameObjectOwner();

	void LoadModel(const char* pFileName);
	void SendToSceneObject();

	void SetFilenamePath(const char* pFileName);
	const char* GetFilenamePath();

private:
	YEMeshLoader* ModelMesh;
	YEMesh* _mesh;
	const char* _meshFilename;
};

#endif