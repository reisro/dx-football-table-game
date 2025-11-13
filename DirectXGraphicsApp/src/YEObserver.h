#pragma once

#ifndef _YE_OBSERVER_H_
#define _YE_OBSERVER_H_

class IYETransformComponentListener
{
public:
	virtual ~IYETransformComponentListener() {};
	virtual void Update(DirectX::CXMMATRIX M) = 0;
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