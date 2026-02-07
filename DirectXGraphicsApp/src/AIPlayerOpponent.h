#pragma once

#ifndef _AI_PLAYER_OPPONENT_H_
#define _AI_PLAYER_OPPONENT_H_

#include "YEGameObject.h"
#include "FTBall.h"
#include "YEVector3.h"
#include "YETimer.h"
#include "FTHandleWhite.h"
#include "FTSingleHandleWhite.h"
#include "PlayerOpponentBehaviour.h"

class AIPlayerOpponent: public YEGameObject
{
public:
	AIPlayerOpponent(const YEGameContext& _game_context, FTHandleWhite* handle, FTSingleHandleWhite* keeper, YEGameObject* _football_ball);
	virtual ~AIPlayerOpponent();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;
	void Play();
	void Stop();

	void WatchBallDirection();

private:
	PlayerOpponentBehaviour* _behaviour_tree;

	YEVector3* _currentBallPos;
	YEVector3* _lastBallPos;
	YEVector3  footballPosAux;

	yeFloat _pleftPosX;
	yeFloat _prightPosX;

	FTHandleWhite*		 _handleFront;
	FTSingleHandleWhite* _handleKeeper;

	YEGameObject* _target;

	YETimer*   _timer;
	
	bool		_active;
	bool	   _captureTime;
};

#endif
