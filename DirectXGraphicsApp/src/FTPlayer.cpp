#include "FTPlayer.h"

FTPlayer::FTPlayer(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_player.fbx"))
{
}

FTPlayer::~FTPlayer()
{
}

void FTPlayer::start()
{
	addComponent(_mesh_component);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTPlayer::shutdown()
{
}

void FTPlayer::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
