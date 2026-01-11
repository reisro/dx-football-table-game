#include "FTPlayerWhite.h"
#include "YEVector3.h"
#include "DXTypes.h"
#include <YEPhysX.h>
#include <functional> 

FTPlayerWhite::FTPlayerWhite(const YEGameContext& _game_context, const wchar_t* _meshName)
	: FTPlayer(_game_context, _meshName) {}

FTPlayerWhite::~FTPlayerWhite()
{
}

void FTPlayerWhite::start()
{
	FTPlayer::start();
}

void FTPlayerWhite::shutdown()
{
}

void FTPlayerWhite::update(float _deltaTime)
{
	FTPlayer::update(_deltaTime);
}

void FTPlayerWhite::DistanceFromTarget(YEGameObject* football_ball)
{
	_distanceFromBall = YEVector3::Subtract(*new YEVector3(football_ball->_transform->getPosition()->_x,0.0f, football_ball->_transform->getPosition()->_z),
		*new YEVector3(_transform->getPosition()->_x,0.0f, _transform->getPosition()->_z))->Magnitude();
}

void FTPlayerWhite::DistanceFromCenter()
{
	_distanceFromCenter = YEVector3::Subtract(*new YEVector3(0.0f, _transform->getPosition()->_y,0.0f), *_transform->getPosition())->Magnitude();
}
