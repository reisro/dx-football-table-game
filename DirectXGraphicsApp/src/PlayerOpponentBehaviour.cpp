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

		if (phsyX->MoveJointBody(1, -2.4f, 5.4f))

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
		//phsyX->MoveJointBody(0.05f);

		return YEBehaviourStatus::SUCCESS;
	}
	
	return YEBehaviourStatus::FAILURE;
}

YEBehaviourStatus PlayerOpponentBehaviour::MoveHandle()
{
	if (!_closeToShoot)
	{
		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		if (!_alignedWithBall && _goRight)
		{
			YELog("PlayerOpponentBehaviour: Move Handle Right executed.");

			if (phsyX->MoveJointBody(1, -2.4f, 5.4f))
				_canChangeDir = false;
		}
		
		if (!_alignedWithBall && _goLeft)
		{
			YELog("PlayerOpponentBehaviour: Move Handle Left executed.");

			if (phsyX->MoveJointBody(-1, -2.4f, 5.4f))
				_canChangeDir = false;
		}

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
