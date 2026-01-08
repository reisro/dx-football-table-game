#pragma once

#ifndef _FT_HANDLE_WHITE_H_
#define _FT_HANDLE_WHITE_H_

#include "FTHandle.h"
#include "YEBehaviourAction.h"
#include "PlayerOpponentBehaviour.h"

class FTHandleWhite: public FTHandle
{
public:

	FTHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName);
	virtual ~FTHandleWhite();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	PlayerOpponentBehaviour* _behaviour_tree;

private:

};

#endif 
