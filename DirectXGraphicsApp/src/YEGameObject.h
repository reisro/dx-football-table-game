#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_GAME_OBJECT_H_
#define _YE_GAME_OBJECT_H_

#include "DXAPI.h"
#include "YEVectorWrapper.h"
#include "YETransformComponent.h"
#include "YEMeshComponent.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "d3dx11effect.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

class YEBaseComponent;

class DX_API YEGameObject
{
public:

	YEGameObject();

	YEGameObject(const char* _game_name);

	virtual ~YEGameObject();

	virtual void start();

	virtual void shutdown();

	virtual void update(float _deltaTime);

	virtual void addComponent(YEBaseComponent* component);

	virtual void setName(const char* _name);

	void setWorldViewProj(CXMMATRIX M);

	void SetWorld(CXMMATRIX M);

	void SetWorldInverseTranspose(CXMMATRIX M);

	void SetEyePosW(const XMVECTOR& v);

	YETransformComponent* GetTransform();

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectVectorVariable* EyePosW;

protected:
	YEVectorWrapper<YEBaseComponent*> _components;
	YEVectorWrapper<YEGameObject*>	  _children;

private:
	const char* _game_object_name;
	UINT _id;
};

#endif _YE_GAME_OBJECT_H_