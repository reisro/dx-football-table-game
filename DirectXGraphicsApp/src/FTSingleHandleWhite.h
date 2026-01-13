#pragma once

#ifndef _FT_SINGLE_HANDLE_WHITE_H_
#define _FT_SINGLE_HANDLE_WHITE_H_

#include "FTSingleHandle.h"
#include "FTPlayerWhite.h"
#include "YEBehaviourAction.h"

class FTSingleHandleWhite : public FTSingleHandle
{
public:

	FTSingleHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, const wchar_t* meshName);
	virtual ~FTSingleHandleWhite();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	FTPlayerWhite* GetKeeper() const { return _keeper; }

private:
	FTPlayerWhite* _keeper;
};

#endif 
