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
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(-6.7f, 0.0f, 0.0f), new YEVector3(1.0f, 5.5f, 10.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(-4.0f, 0.0f, 10.5f), new YEVector3(1.8f, 5.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(-4.0f, 0.0f, -10.5f), new YEVector3(1.8f, 5.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(4.0f, 0.0f, 10.5f), new YEVector3(1.8f, 5.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(4.0f, 0.0f, -10.5f), new YEVector3(1.8f, 5.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(6.7f, 0.0f, 0.0f), new YEVector3(1.0f, 5.5f, 10.0f));

	// nets
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(0.0f, 0.0f, -12.5f), new YEVector3(1.6f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox(new YEVector3(0.0f, 0.0f, 12.5f), new YEVector3(1.6f, 2.5f, 2.0f));
}

void FTFieldWalls::shutdown()
{
}

void FTFieldWalls::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}