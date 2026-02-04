#pragma once

#ifndef _YE_SCENE_OBJECT_H_
#define _YE_SCENE_OBJECT_H_

#include "YEBaseComponent.h"
#include "YEMesh.h"
#include "YESprite.h"
#include <DirectXMath.h>
#include "YEObserver.h"

using namespace DirectX;

class DX_API YESceneObject: public IYETransformComponentListener
{
public:
	YESceneObject();
	virtual ~YESceneObject();

	void CreateObjectWorldList(UINT id, DirectX::CXMMATRIX M);
	
	XMFLOAT4X4 LoadWorldPosition(UINT id);
	void Draw(IUnknown* context, int id);
	virtual void Update(UINT id, DirectX::CXMMATRIX M) override;

	std::vector<YEMesh> _meshesToRender;
	std::vector<YESprite> _spritesToRender;
	std::map<UINT, XMFLOAT4X4> _meshesWorld;

	bool* _showSprite;
	bool _on_off;

	UINT _meshid;
	UINT _physicsid;
	UINT _internalid;
};

#endif

