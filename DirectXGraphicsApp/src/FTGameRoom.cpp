#include "FTGameRoom.h"

FTGameRoom::FTGameRoom(const YEGameContext& _game_context, const char* _meshName):
	YEGameObject("Game Room", _game_context),
	_mesh_component(new YEMeshComponent(this, _meshName))
{
	addComponent(_mesh_component);
}

FTGameRoom::~FTGameRoom()
{
}

void FTGameRoom::start()
{
	YEGameObject::start();

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTGameRoom::shutdown()
{
}

void FTGameRoom::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
