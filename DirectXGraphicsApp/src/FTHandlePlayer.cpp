#include "FTHandlePlayer.h"

FTHandlePlayer::FTHandlePlayer(const YEGameContext& _game_context) :
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_handle_right.fbx")),
	_physics_component(new YEPhysicsComponent())
{
	addComponent(_mesh_component);
	addComponent(_physics_component);
}

FTHandlePlayer::~FTHandlePlayer()
{
}

void FTHandlePlayer::start()
{
	//_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTHandlePlayer::shutdown()
{
}

void FTHandlePlayer::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}