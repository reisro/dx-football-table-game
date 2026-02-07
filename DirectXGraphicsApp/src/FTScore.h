#pragma once

#ifndef _H_FT_SCORE_H_
#define _H_FT_SCORE_H_

#include "YEGameObject.h"
#include "YEPhysX.h"
#include "YEAudioComponent.h"
#include <FTScoreMarker.h>
#include <FTGoalWidgetUI.h>
#include <functional>
#include <string.h>

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
	void Unregister() { _active = false; }
	void ResetScore() 
	{ 
		_playerScore = 0; 
		_aiScore = 0; 
		_score_marker_ai->PlaceMarkerAt(0);
		_score_marker_player->PlaceMarkerAt(0);
	}
	
	void IsGoalScoredMaxReached() 
	{ 
		if (_playerScore == 9)
		{
			std::string score = std::to_string(_aiScore);

			_matchResult = "n\t\t\t\t\t\t\t\t\t\t\You won! Scored 9 goals";

			OnGoalScoredMaxReached();
		}
		
		if (_aiScore == 9)
		{
			std::string score = std::to_string(_playerScore);

			_matchResult = "\n\t\t\t\t\t\t\t\t\t\tAI won! Scored 9 goals";

			OnGoalScoredMaxReached();
		}
	}

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
	std::function<void()> OnGoalScoredMaxReached;

	const char* _matchResult;

private:
	FTScoreMarker*    _score_marker_player;
	FTScoreMarker*    _score_marker_ai;
	FTGoalWidgetUI*	  _goal_widget_ui;
	YEAudioComponent* _goal_sound_component;
	const char*       _soundFilename;
	int               _playerScore=0;
	int               _aiScore=0;
	bool			  _active;
};

#endif _H_FT_SCORE_H_