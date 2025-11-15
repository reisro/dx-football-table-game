#pragma once

#ifndef _YE_SCENE_OBJECT_H_
#define _YE_SCENE_OBJECT_H_

#include "YEBaseComponent.h"
#include "YEMesh.h"
#include "YEObserver.h"

class DX_API YESceneObject: public IYETransformComponentListener
{
public:
	YESceneObject();
	virtual ~YESceneObject();

	void Draw(IUnknown* context, int id);
	virtual void Update(UINT id, DirectX::CXMMATRIX M) override;

	std::vector<YEMesh> _meshesToRender;

	UINT _meshid;
};

#endif

