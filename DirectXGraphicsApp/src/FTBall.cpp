#include "FTBall.h"

FTBall::FTBall():
	_mesh_component(nullptr)
{
}

FTBall::~FTBall()
{
}

void FTBall::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_ball.fbx");
}

void FTBall::shutdown()
{
}

void FTBall::update(float _deltaTime)
{
}
