#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_GAME_OBJECT_H_
#define _YE_GAME_OBJECT_H_

#include "DXAPI.h"
#include "YEVectorWrapper.h"
#include "YETransformComponent.h"
#include "YEMeshComponent.h"

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

	void SetPosition(YEVector3* pos);

	YETransformComponent* GetTransform();

protected:
	YEVectorWrapper<YEBaseComponent*> _components;
	YEVectorWrapper<YEGameObject*>	  _children;

private:
	const char* _game_object_name;
	UINT _id;
	YEVector3* position;
};

#endif _YE_GAME_OBJECT_H_