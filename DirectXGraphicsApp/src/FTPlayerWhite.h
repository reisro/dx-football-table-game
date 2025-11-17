#pragma once

#ifndef _FT_PLAYER_WHITE_H_
#define _FT_PLAYER_WHITE_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"

class FTPlayerWhite : public YEGameObject
{
public:
	FTPlayerWhite(const YEGameContext& _game_context);
	virtual ~FTPlayerWhite();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent* _mesh_component;
};

#endif _FT_PLAYER_WHITE_H_