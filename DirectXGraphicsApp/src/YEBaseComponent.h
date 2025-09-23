#pragma once

#ifndef _YE_BASE_COMPONENT_H_
#define _YE_BASE_COMPONENT_H_

#include "DXAPI.h"

class DX_API YEBaseComponent
{
public:
	
	YEBaseComponent() {}
	virtual ~YEBaseComponent() {}

	virtual void start() = 0;
	virtual void shutdown() = 0;
	virtual void update(float _deltaTime) = 0;
};

#endif // _YE_BASE_COMPONENT_H_