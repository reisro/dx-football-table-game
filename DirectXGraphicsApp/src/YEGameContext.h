#pragma once

#ifndef _YE_GAMECONTEXT_H_
#define _YE_GAMECONTEXT_H_

#include "YESceneObject.h"

class YEGameContext
{
public:
	YEGameContext() {}
	virtual ~YEGameContext() {}

private:
	YESceneObject* _scene;
};

#endif