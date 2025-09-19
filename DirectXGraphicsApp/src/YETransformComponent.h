#pragma once

#ifndef _YE_TRANSFORM_COMPONENT_H_
#define _YE_TRANSFORM_COMPONENT_H_

#include "DXAPI.h"
#include "YEBaseComponent.h"
#include "DXTypes.h"

class DX_API YETransformComponent : public YEBaseComponent
{
public:

	YETransformComponent();
	virtual ~YETransformComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void setPosition(yeFloat x, yeFloat y, yeFloat z);
	void setRotation(yeFloat x, yeFloat y, yeFloat z);
	void setScale(yeFloat x, yeFloat y, yeFloat z);

	yeFloat* getPosition();
	yeFloat* getRotation();
	yeFloat* getScale();

private:
	yeFloat position[3];
	yeFloat rotation[3];
	yeFloat scale[3];
};

#endif