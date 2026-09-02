#pragma once

#ifndef _FT_SINGLE_HANDLE_PLAYER_H_
#define _FT_SINGLE_HANDLE_PLAYER_H_

#include "FTSingleHandle.h"
#include "YEInput.h"

class FTSingleHandlePlayer : public FTSingleHandle
{
public:

	FTSingleHandlePlayer(const YEGameContext& _game_context, FTPlayer* p1, const char* meshName);
	virtual ~FTSingleHandlePlayer();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

private:
	YEInput* _yeInput;
};

#endif 
