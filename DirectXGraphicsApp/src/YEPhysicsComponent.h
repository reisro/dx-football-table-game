#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_PHYSICS_COMPONENT_H_
#define _YE_PHYSICS_COMPONENT_H_

#include "DXAPI.h"
#include "YEBaseComponent.h"
#include "DXTypes.h"
#include "YEVector3.h"
#include "YEObserver.h"
#include "PxPhysicsAPI.h"

class YEPhysicsComponent: public YEBaseComponent, public IYETransformComponentChange
{
public:
	YEPhysicsComponent();
	virtual ~YEPhysicsComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void Attach(IYETransformComponentListener* observer) override;
	void Detach(IYETransformComponentListener* observer) override;
	void Notify() override;

private:

};

#endif