#pragma once

#ifndef _GOALIE_OPPONENT_BEHAVIOUR_H_
#define _GOALIE_OPPONENT_BEHAVIOUR_H_

#include "YEBehaviourTree.h"
#include "YEBehaviourAction.h"

class GoalieOpponentBehaviour : public YEBehaviourTree
{
public:
	GoalieOpponentBehaviour();
	virtual ~GoalieOpponentBehaviour();

	YEBehaviourStatus Defend();

private:
	YEBehaviourNode* rootNode;
};

#endif // _GOALIE_OPPONENT_BEHAVIOUR_H_