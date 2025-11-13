#include "FTBall.h"
#include "YEGameContext.h"

FTBall::FTBall(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(nullptr)
{
}

FTBall::~FTBall()
{
}

void FTBall::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_ball.fbx");
	
	addComponent(_mesh_component);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTBall::shutdown()
{
}

void FTBall::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}