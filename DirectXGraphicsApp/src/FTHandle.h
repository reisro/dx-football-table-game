#pragma once

#ifndef _FT_HANDLE_H_
#define _FT_HANDLE_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"
#include "FTPlayer.h"

class FTHandle : public YEGameObject
{
public:
	FTHandle(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2);
	virtual ~FTHandle();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	FTPlayer*			_player_right;
	FTPlayer*			_player_left;
	YEMeshComponent*	_mesh_component;
	YEPhysicsComponent* _physics_component;
};

#endif _FT_HANDLE_H_