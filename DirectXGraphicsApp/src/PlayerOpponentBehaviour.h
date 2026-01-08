#pragma once

#ifndef _GOALIE_OPPONENT_BEHAVIOUR_H_
#define _GOALIE_OPPONENT_BEHAVIOUR_H_

#include "YEBehaviourTree.h"
#include "YEBehaviourAction.h"

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
};

#endif // _GOALIE_OPPONENT_BEHAVIOUR_H_