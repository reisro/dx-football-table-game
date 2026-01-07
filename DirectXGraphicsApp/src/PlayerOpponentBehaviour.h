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

	YEBehaviourStatus Defend();
	YEBehaviourStatus Attack();

	YEBehaviourNode* rootNode;

private:
};

#endif // _GOALIE_OPPONENT_BEHAVIOUR_H_