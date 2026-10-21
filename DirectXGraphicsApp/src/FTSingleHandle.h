#pragma once

#ifndef _FT_SINGLE_HANDLE_H_
#define _FT_SINGLE_HANDLE_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEPhysicsComponent.h"
#include "FTPlayer.h"
#include "YEFileSystem.h"

class FTSingleHandle : public YEGameObject
{
public:
	FTSingleHandle(const YEGameContext& _game_context, FTPlayer* p1, const char* meshName);
	virtual ~FTSingleHandle();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	bool _isCPU;

protected:
	FTPlayer* _player_left;
	YEMeshComponent* _mesh_component;
	const char* _meshFilename;
};

#endif _FT_SINGLE_HANDLE_H_