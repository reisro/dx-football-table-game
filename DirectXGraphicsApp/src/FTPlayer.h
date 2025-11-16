#pragma once

#ifndef _FT_PLAYER_H_
#define _FT_PLAYER_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"

class FTPlayer : public YEGameObject
{
public:
	FTPlayer(const YEGameContext& _game_context);
	virtual ~FTPlayer();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent* _mesh_component;
};

#endif _FT_BALL_H_