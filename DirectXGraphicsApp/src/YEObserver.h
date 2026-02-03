#pragma once

#ifndef _YE_OBSERVER_H_
#define _YE_OBSERVER_H_

class IYETransformComponentListener
{
public:
	virtual ~IYETransformComponentListener() {};
	virtual void Update(UINT id, DirectX::CXMMATRIX M) = 0;
};

class YEPhysicsColliderListener
{
	public:
	virtual ~YEPhysicsColliderListener() {};
	virtual void OnNotify(const char* name) = 0;
};

class YEPhysicsColliderTransmitter
{
public:
	virtual ~YEPhysicsColliderTransmitter() {};
	virtual void Attach(YEPhysicsColliderListener* observer) = 0;
	virtual void NotifyCollision(const char* actorName) = 0;
};

class IYETransformComponentChange
{
public:
	virtual ~IYETransformComponentChange() {};
	virtual void Attach(IYETransformComponentListener* observer) = 0;
	virtual void Detach(IYETransformComponentListener* observer) = 0;
	virtual void Notify() = 0;
};

#endif