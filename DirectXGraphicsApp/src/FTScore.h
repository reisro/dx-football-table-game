#pragma once

#ifndef _H_FT_SCORE_H_
#define _H_FT_SCORE_H_

#include "YEGameObject.h"
#include "YEPhysX.h"
#include "YEAudioComponent.h"
#include <FTScoreMarker.h>
#include <FTGoalWidgetUI.h>
#include <functional>

class FTScore : public YEGameObject
{
public:
	FTScore(const YEGameContext& _game_context);
	virtual ~FTScore();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	int GetPlayerScore() const { return _playerScore; }
	int GetAIScore() const { return _aiScore; }
	void IncrementScore(const char* player);
	void PlayGoalSound();
	void Register() { _active = true; }

	void ResetBall() 
	{ 
		_score_marker_ai->ResetMarkerUpdate();
		_score_marker_player->ResetMarkerUpdate();

		OnScoreGoal();
	}

	void ResetGameplay()
	{
		OnGoalUIHide();
	}

	std::function<void()> OnScoreGoal;
	std::function<void()> OnGoalUIHide;

private:
	FTScoreMarker*    _score_marker_player;
	FTScoreMarker*    _score_marker_ai;
	FTGoalWidgetUI*	  _goal_widget_ui;
	YEAudioComponent* _goal_sound_component;
	const char*       _soundFilename;
	int               _playerScore;
	int               _aiScore;
	bool			  _active;
};

#endif _H_FT_SCORE_H_