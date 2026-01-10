#include "PlayerOpponentBehaviour.h"
#include "YEPhysX.h"

PlayerOpponentBehaviour::PlayerOpponentBehaviour():
	_timer(YETimer::GetInstance())
{
}

PlayerOpponentBehaviour::~PlayerOpponentBehaviour()
{
}

YEBehaviourStatus PlayerOpponentBehaviour::Deffend()
{
	if (_isDefending)
	{
		YELog("PlayerOpponentBehaviour: Deffend executed.");

		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		return YEBehaviourStatus::SUCCESS;
	}
	
	return YEBehaviourStatus::FAILURE;
}

YEBehaviourStatus PlayerOpponentBehaviour::Attack()
{
	if (_closeToShoot)
	{
		YELog("PlayerOpponentBehaviour: Attack executed.");

		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		phsyX->RotateJointBody();
		phsyX->MoveJointBody(0.05f);

		return YEBehaviourStatus::SUCCESS;
	}
	
	return YEBehaviourStatus::FAILURE;
}

YEBehaviourStatus PlayerOpponentBehaviour::MoveHandle()
{
	if (!_closeToShoot)
	{
		YELog("PlayerOpponentBehaviour: Move Handle executed.");

		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
		
		if(_timer->Countdown(5))
			phsyX->MoveJointBody(1);

		return YEBehaviourStatus::SUCCESS;
	}

	return YEBehaviourStatus::FAILURE;
}

YEBehaviourStatus PlayerOpponentBehaviour::WatchBall()
{
	YELog("PlayerOpponentBehaviour: Watching Ball executed.");

	if (_closeToShoot)
		_isDefending = false;
	else
	{
		if (_isBehind)
			_isDefending = false;
		else
			_isDefending = true;

		_closeToShoot = false;
	}

	return YEBehaviourStatus::SUCCESS;
}
