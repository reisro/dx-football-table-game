#pragma once

#ifndef _YE_SCENE_OBJECT_H_
#define _YE_SCENE_OBJECT_H_

#include "YEBaseComponent.h"
#include "YEMesh.h"

class DX_API YESceneObject
{
public:
	YESceneObject();
	virtual ~YESceneObject();

	//void addMesh(std::vector<YEMesh> meshes);
	void Draw(IUnknown* context);
	
private:
	std::vector<YEMesh> _meshes;
};

#endif

