#include "PlayerOpponentBehaviour.h"
#include "YEPhysX.h"

PlayerOpponentBehaviour::PlayerOpponentBehaviour()
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
	}

	return YEBehaviourStatus::SUCCESS;
}
