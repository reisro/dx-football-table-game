#pragma once

#ifndef _H_OPONENT_PLAYER_H
#define _H_OPONENT_PLAYER_H

#include "YEBehaviourTree.h"
#include "YEGameObject.h"

class OpponentPlayer: public YEGameObject
{
public:

	OpponentPlayer();
	virtual ~OpponentPlayer();

private:
	YEBehaviourTree* _behaviourTree;
};

#endif 