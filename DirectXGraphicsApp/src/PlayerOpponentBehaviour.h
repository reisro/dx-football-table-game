#pragma once

#ifndef _GOALIE_OPPONENT_BEHAVIOUR_H_
#define _GOALIE_OPPONENT_BEHAVIOUR_H_

#include "YEBehaviourTree.h"
#include "YEBehaviourAction.h"
#include "YETimer.h"

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
	bool    _ballIsInMySide;
	bool	_goRight;
	bool	_goLeft;
	bool	_canChangeDir;
	bool 	_alignedWithBall;

private:
	YETimer* _timer;
};

#endif // _GOALIE_OPPONENT_BEHAVIOUR_H_