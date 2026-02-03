#pragma once

#ifndef _FT_FIELD_WALLS_H_
#define _FT_FIELD_WALLS_H_

#include "YEGameObject.h"
#include "YEPhysicsComponent.h"
#include "YEObserver.h"

class FTFieldWalls : public YEGameObject, public YEPhysicsColliderListener
{
public:
	FTFieldWalls(const YEGameContext& _game_context);
	virtual ~FTFieldWalls();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	virtual void OnNotify(const char* name) override;

};

#endif _FT_FIELD_WALLS_H_