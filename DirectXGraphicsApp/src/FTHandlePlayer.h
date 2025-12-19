#pragma once

#ifndef _FT_HANDLE_PLAYER_H_
#define _FT_HANDLE_PLAYER_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"

class FTHandlePlayer : public YEGameObject
{
public:
	FTHandlePlayer(const YEGameContext& _game_context);
	virtual ~FTHandlePlayer();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent* _mesh_component;
	YEPhysicsComponent* _physics_component;
};

#endif _FT_HANDLE_PLAYER_H_