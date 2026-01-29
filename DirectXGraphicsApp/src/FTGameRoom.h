#pragma once

#ifndef _FT_GAMEROOM_H_
#define _FT_GAMEROOM_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"

class FTGameRoom : public YEGameObject
{
public:

	FTGameRoom(const YEGameContext& _game_context, const wchar_t* _meshName);
	virtual ~FTGameRoom();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent* _mesh_component;

private:

};

#endif _FT_GAMEROOM_H_