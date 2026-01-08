#pragma once

#ifndef _FT_PLAYER_WHITE_H_
#define _FT_PLAYER_WHITE_H_

#include "FTPlayer.h"
#include "FTBall.h"
#include "YEBehaviourAction.h"
#include "PlayerOpponentBehaviour.h"

class FTPlayerWhite : public FTPlayer
{
public:
	FTPlayerWhite(const YEGameContext& _game_context, const wchar_t* _meshName);
	virtual ~FTPlayerWhite();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void DistanceFromTarget(YEGameObject* football_ball);

protected:
	PlayerOpponentBehaviour* _behaviour_tree;

private:
	FTBall* _football_ball;
	yeFloat _ballDistanceThreshold = 1.10f;
};

#endif _FT_PLAYER_WHITE_H_