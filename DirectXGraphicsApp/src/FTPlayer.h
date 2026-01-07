#pragma once

#ifndef _FT_PLAYER_H_
#define _FT_PLAYER_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"

class FTPlayer : public YEGameObject
{
public:
	FTPlayer(const YEGameContext& _game_context, const wchar_t* _meshName);
	virtual ~FTPlayer();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	YEPhysicsComponent* getPhysicsComponent() { return _physics_component; }

protected:
	YEMeshComponent*	_mesh_component;
	YEPhysicsComponent* _physics_component;
	const wchar_t*		_meshFilename;
};

#endif _FT_BALL_H_