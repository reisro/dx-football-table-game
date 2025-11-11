#pragma once

#ifndef _YE_OBSERVER_H_
#define _YE_OBSERVER_H_

class IYEObserver
{
public:
	virtual ~IYEObserver() {};
	virtual void Update() = 0;
};

class IYESubject
{
	virtual ~IYESubject() {};
	virtual void Attach(IYEObserver* observer) = 0;
	virtual void Detach(IYEObserver* observer) = 0;
	virtual void Notify() = 0;
};

#endif