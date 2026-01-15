#pragma once

#ifndef _GOALIE_OPPONENT_BEHAVIOUR_H_
#define _GOALIE_OPPONENT_BEHAVIOUR_H_

#include "YEBehaviourTree.h"
#include "YEBehaviourAction.h"
#include "YETimer.h"
#include "YEVector3.h"

class PlayerOpponentBehaviour : public YEBehaviourTree
{
public:
	PlayerOpponentBehaviour();
	virtual ~PlayerOpponentBehaviour();

	YEBehaviourStatus Deffend();
	YEBehaviourStatus Attack();
	YEBehaviourStatus MoveHandle();
	YEBehaviourStatus WatchBall();

	YEBehaviourNode* rootNode;

	bool    _isDefending;
	bool    _isBehind;
	bool	_closeToShoot;
	bool	_frontCanShoot;
	bool	_keeperCanShoot;
	bool    _ballIsInMySide;
	bool	_goRight;
	bool	_goLeft;
	bool	_canChangeDir;
	bool 	_handleAlignedWithBall;
	bool 	_keeperAlignedWithBall;

	YEVector3	_BallPosition;
	YEVector3	_P1Position;
	YEVector3	_P2Position;
	YEVector3	_KeeperPosition;

private:
	YETimer* _timer;
};

#endif // _GOALIE_OPPONENT_BEHAVIOUR_H_