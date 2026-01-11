#pragma once

#ifndef _AI_PLAYER_OPPONENT_H_
#define _AI_PLAYER_OPPONENT_H_

#include "YEGameObject.h"
#include "FTBall.h"
#include "YEVector3.h"
#include "YETimer.h"
#include "FTHandleWhite.h"

class AIPlayerOpponent: public YEGameObject
{
public:
	AIPlayerOpponent(const YEGameContext& _game_context, FTHandleWhite* handle);
	virtual ~AIPlayerOpponent();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void WatchBallDirection(FTBall* _football_ball);

private:
	YEVector3* _currentBallPos;
	YEVector3* _lastBallPos;
	YEVector3  footballPosAux;

	FTHandleWhite* _handleFront;
	FTHandleWhite* _handleKeeper;

	YETimer*   _timer;
	bool	   _isBallMovingRight;
	bool	   _captureTime;
};

#endif
