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
	FTHandle(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const char* meshName);
	virtual ~FTHandle();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	bool _isCPU;

protected:
	FTPlayer*			_player_right;
	FTPlayer*			_player_left;
	YEMeshComponent*	_mesh_component;
	const char*		_meshFilename;

};

#endif _FT_HANDLE_H_