#pragma once

#ifndef _FT_HANDLE_H_
#define _FT_HANDLE_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"

class FTHandle : public YEGameObject
{
public:
	FTHandle(const YEGameContext& _game_context);
	virtual ~FTHandle();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent*    _mesh_component;
	YEMeshComponent*	_mesh_component1;
	YEMeshComponent*	_mesh_component2;
	YEPhysicsComponent* _physics_component;
};

#endif _FT_HANDLE_H_