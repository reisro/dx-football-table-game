#include "FTFieldWalls.h"
#include <YEPhysX.h>

FTFieldWalls::FTFieldWalls(const YEGameContext& _game_context) :
	YEGameObject(_game_context)
{
}

FTFieldWalls::~FTFieldWalls()
{
}

void FTFieldWalls::start()
{
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(-10.0f, 0.0f, 0.0f), new YEVector3(1.0f, 1.0f, 10.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(0.0f, 0.0f, 11.5f), new YEVector3(10.0f, 1.0f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(0.0f, 0.0f, -11.5f), new YEVector3(10.0f, 1.0f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(10.0f, 0.0f, 0.0f), new YEVector3(1.0f, 1.0f, 10.0f));
}

void FTFieldWalls::shutdown()
{
}

void FTFieldWalls::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}