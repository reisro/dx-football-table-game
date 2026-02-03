#pragma once

#ifndef _FT_FIELD_WALLS_H_
#define _FT_FIELD_WALLS_H_

#include "YEGameObject.h"
#include "YEPhysicsComponent.h"
#include "YEObserver.h"
#include <FTScore.h>
#include <FTScoreMarker.h>

class FTFieldWalls : public YEGameObject, public YEPhysicsColliderListener
{
public:
	FTFieldWalls(const YEGameContext& _game_context);
	virtual ~FTFieldWalls();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	virtual void OnNotify(const char* name) override;

private:
	FTScore* football_score;
	FTScoreMarker* score_marker_player;
	FTScoreMarker* score_marker_ai;
};

#endif _FT_FIELD_WALLS_H_