#include "FTPlayerWhite.h"
#include "YEVector3.h"
#include "DXTypes.h"
#include <YEPhysX.h>
#include <functional> 

FTPlayerWhite::FTPlayerWhite(const YEGameContext& _game_context, const wchar_t* _meshName, YEGameObject* target)
	: FTPlayer(_game_context, _meshName),
	_football_ball(target)
{}

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

	DistanceFromTarget();
}

void FTPlayerWhite::DistanceFromTarget()
{
	_distanceFromBall = YEVector3::Subtract(*new YEVector3(_football_ball->_transform->getPosition()->_x,0.0f, _football_ball->_transform->getPosition()->_z),
		*new YEVector3(_transform->getPosition()->_x,0.0f, _transform->getPosition()->_z))->Magnitude();

	_distanceX = _transform->getPosition()->_x;

	YELog("FTPlayerWhite: Distance X: " + std::to_string(_distanceX));
}

void FTPlayerWhite::DistanceFromCenter()
{
	_distanceFromCenter = YEVector3::Subtract(*new YEVector3(0.0f, _transform->getPosition()->_y,0.0f), *_transform->getPosition())->Magnitude();
}
