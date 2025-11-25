#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_PHYSICS_COMPONENT_H_
#define _YE_PHYSICS_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEObserver.h"

class YEPhysics;

class DX_API YEPhysicsComponent: public YEBaseComponent, public IYETransformComponentChange
{
public:
	YEPhysicsComponent();
	YEPhysicsComponent(YEGameObject* owner);
	virtual ~YEPhysicsComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	YEPhysics* GetPhysicsEngine();

	void Attach(IYETransformComponentListener* observer) override;
	void Detach(IYETransformComponentListener* observer) override;
	void Notify() override;

private:

};

#endif