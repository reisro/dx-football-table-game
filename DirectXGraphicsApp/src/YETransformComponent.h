#pragma once

#ifndef _YE_TRANSFORM_COMPONENT_H_
#define _YE_TRANSFORM_COMPONENT_H_

#include "DXAPI.h"
#include "YEBaseComponent.h"
#include "DXTypes.h"
#include "YEVector3.h"

class DX_API YETransformComponent : public YEBaseComponent
{
public:

	YETransformComponent();
	virtual ~YETransformComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void setPosition(yeFloat x, yeFloat y, yeFloat z);
	void setPosition(YEVector3* position);
	void setRotation(yeFloat x, yeFloat y, yeFloat z);
	void setScale(yeFloat x, yeFloat y, yeFloat z);

	yeFloat* getPosition();
	yeFloat* getRotation();
	yeFloat* getScale();

private:
	yeFloat x,y,z;
	YEVector3 _position;
	yeFloat pitch, roll, yaw, w;
	yeFloat sx,sy,sz;
};

#endif