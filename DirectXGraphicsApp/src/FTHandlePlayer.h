#pragma once

#ifndef _FT_HANDLE_PLAYER_H_
#define _FT_HANDLE_PLAYER_H_

#include "FTHandle.h"
#include "YEInput.h"

class FTHandlePlayer : public FTHandle
{
public:
	FTHandlePlayer(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const char* meshName);	
	virtual ~FTHandlePlayer();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

private:
	YEInput* _yeInput;
};

#endif _FT_HANDLE_PLAYER_H_