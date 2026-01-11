#include "AIPlayerOpponent.h"

AIPlayerOpponent::AIPlayerOpponent(const YEGameContext& _game_context, FTHandleWhite* handle):
	YEGameObject(_game_context), _handleFront(handle), _isBallMovingRight(false), _captureTime(false)
{
	_currentBallPos = YEVector3::Zero();
	_lastBallPos = YEVector3::Zero();
	_timer = YETimer::GetInstance();
}

AIPlayerOpponent::~AIPlayerOpponent()
{
	_currentBallPos = nullptr;
	_lastBallPos = nullptr;
	_timer = nullptr;
}

void AIPlayerOpponent::start()
{
	YEGameObject::start();
}

void AIPlayerOpponent::shutdown()
{
	YEGameObject::shutdown();
}

void AIPlayerOpponent::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}

void AIPlayerOpponent::WatchBallDirection(FTBall* _football_ball)
{
	if (!_captureTime)
	{
		_lastBallPos = _football_ball->_transform->getPosition();

		footballPosAux = *_lastBallPos;
		_captureTime = true;
	}

	if (_timer->Countdown(1))
	{
		_currentBallPos = _football_ball->_transform->getPosition();
		_captureTime = false;
	}

	if (YEVector3::Subtract(*_currentBallPos, footballPosAux)->_x < 0)
	{
		_handleFront->GetBehaviourTree()->_goLeft = true;
		_handleFront->GetBehaviourTree()->_goRight = false;
	}
	
	if (YEVector3::Subtract(*_currentBallPos, footballPosAux)->_x > 0)
	{
		_handleFront->GetBehaviourTree()->_goLeft = false;
		_handleFront->GetBehaviourTree()->_goRight = true;
	}

	if (YEVector3::Subtract(*_currentBallPos, footballPosAux)->_x == 0)
	{
		_handleFront->GetBehaviourTree()->_goLeft = false;
		_handleFront->GetBehaviourTree()->_goRight = false;
	}
}
