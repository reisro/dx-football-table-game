#pragma once

#ifndef _H_FT_SCORE_H_
#define _H_FT_SCORE_H_

#include "YEGameObject.h"
#include "YEPhysX.h"

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
	void IncrementPlayerScore() { _playerScore++; }
	void IncrementAIScore() { _aiScore++; }
	
	void ResetScores() 
	{ 
		_playerScore = 0; 
		_aiScore = 0; 

		YEPhysX* physics = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
		physics->ResetDynamicSphere();
	}

private:
	int _playerScore;
	int _aiScore;
};

#endif _H_FT_SCORE_H_