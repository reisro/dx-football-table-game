#pragma once

#ifndef _YE_MESH_COMPONENT_H_
#define _YE_MESH_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEMeshLoader.h"

class DX_API YEMeshComponent : public YEBaseComponent
{
public:

	YEMeshComponent();
	YEMeshComponent(YEGameObject* owner, const wchar_t* pFileName);

	virtual ~YEMeshComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	YEGameObject* GetGameObjectOwner();

	void LoadModel(const wchar_t* pFileName);
	void SendToSceneObject();

	void SetFilenamePath(const wchar_t* pFileName);
	const wchar_t* GetFilenamePath();

private:
	YEMeshLoader* ModelMesh;
	YEMesh* _mesh;
	const wchar_t* _meshFilename;
};

#endif