#pragma once

#ifndef _YE_BASE_COMPONENT_H_
#define _YE_BASE_COMPONENT_H_

#include "DXAPI.h"
#include "YEVector3.h"

class YETransformComponent;
class YEGameObject;

class DX_API YEBaseComponent
{
	friend class YEGameObject;

public:
	
	YEBaseComponent(): _gameObject(nullptr) {}
	YEBaseComponent(YEGameObject* _owner) : _gameObject(_owner) {}
	virtual ~YEBaseComponent() {}

	virtual void start() = 0;
	virtual void shutdown() = 0;
	virtual void update(float _deltaTime) = 0;

	virtual YETransformComponent* getTransformComponent();
	virtual void SetGameObject(YEGameObject* go) { _gameObject = go; }
	
protected:
		
	YEGameObject* _gameObject;
};

#endif // _YE_BASE_COMPONENT_H_