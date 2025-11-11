#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_TRANSFORM_COMPONENT_H_
#define _YE_TRANSFORM_COMPONENT_H_

#include "DXAPI.h"
#include "YEBaseComponent.h"
#include "DXTypes.h"
#include "YEVector3.h"
#include "YEObserver.h"

class DX_API YETransformComponent : public YEBaseComponent, public IYESubject 
{
public:

	YETransformComponent();
	virtual ~YETransformComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void Attach(IYEObserver* observer) override;
	void Detach(IYEObserver* observer) override;
	void Notify() override;

	void setPosition(yeFloat x, yeFloat y, yeFloat z);
	void setPosition(YEVector3* position);
	void setRotation(yeFloat x, yeFloat y, yeFloat z);
	void setScale(yeFloat x, yeFloat y, yeFloat z);

	const XMFLOAT4X4& getWorldMatrix() const { return _mWorld; }

	YEVector3* getPosition();
	yeFloat* getRotation();
	yeFloat* getScale();

private:
	yeFloat x,y,z;
	YEVector3 _position;
	yeFloat pitch, roll, yaw, w;
	yeFloat sx,sy,sz;

	XMFLOAT4X4  _mWorld;
};

#endif