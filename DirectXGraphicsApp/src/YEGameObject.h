#pragma once

#ifndef _YE_GAME_OBJECT_H_
#define _YE_GAME_OBJECT_H_

#include "DXAPI.h"
#include "YEWindow.h"

class DX_API YEGameObject
{
public:

	YEGameObject();

	YEGameObject(const char* _game_name);

	virtual ~YEGameObject();

	virtual void start();

	virtual void shutdown();

	virtual void update(float _deltaTime);

	virtual void addComponent();

	virtual void setName(const char* _name);

private:
	const char* _game_object_name;
	UINT _id;
};

#endif _YE_GAME_OBJECT_H_