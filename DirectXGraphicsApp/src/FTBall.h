#pragma once

#ifndef _FT_BALL_H_
#define _FT_BALL_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"
#include "YEFileSystem.h"

class FTBall : public YEGameObject
{
	public:
		FTBall(const YEGameContext& _game_context);
		virtual ~FTBall();

		void start() override;
		void shutdown() override;
		void update(float _deltaTime) override;

protected:
	YEMeshComponent*    _mesh_component;
	YEPhysicsComponent* _physics_component;
};

#endif _FT_BALL_H_