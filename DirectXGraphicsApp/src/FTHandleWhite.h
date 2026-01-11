#pragma once

#ifndef _FT_HANDLE_WHITE_H_
#define _FT_HANDLE_WHITE_H_

#include "FTHandle.h"
#include "FTPlayerWhite.h"
#include "YEBehaviourAction.h"
#include "YETimeBehaviourAction.h"
#include "PlayerOpponentBehaviour.h"

class FTHandleWhite: public FTHandle
{
public:

	FTHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName);
	virtual ~FTHandleWhite();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	PlayerOpponentBehaviour* GetBehaviourTree();

protected:
	PlayerOpponentBehaviour* _behaviour_tree;

private:
	FTPlayerWhite* _player_left;
	FTPlayerWhite* _player_right;
};

#endif 
