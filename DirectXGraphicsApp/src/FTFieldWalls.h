#pragma once

#ifndef _FT_FIELD_WALLS_H_
#define _FT_FIELD_WALLS_H_

#include "YEGameObject.h"
#include "YEPhysicsComponent.h"
#include "YEObserver.h"
#include <FTScore.h>
#include <functional>

class FTFieldWalls : public YEGameObject, public YEPhysicsColliderListener
{
public:
	FTFieldWalls(const YEGameContext& _game_context);
	virtual ~FTFieldWalls();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;
	void OnGoalScored();
	void OnScoreGoalUIHide();
	void OnGoalsMaxReached();
	void ActiveScore();
	void DeactiveScore();
	void RestartScore();

	virtual void OnNotify(const char* name) override;

	std::function<void(void)> OnBallReachGoalTrigger;
	std::function<void(void)> OnCloseGoalWidget;
	std::function<void(const char*)> OnScoreMaxGoalsReached;

private:
	bool _updatedScore;
	FTScore* football_score;

	std::function<void (const char*)> action;
};

#endif _FT_FIELD_WALLS_H_