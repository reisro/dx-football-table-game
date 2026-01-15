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

		phsyX->ResetRotatePulleyJointBody(4);

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

		if (_frontCanShoot)
		{
			phsyX->RotatePulleyJointBody(2);
			phsyX->RotatePulleyJointBody(3);
		}
		
		if (_keeperCanShoot)
			phsyX->RotatePulleyJointBody(4);

		return YEBehaviourStatus::SUCCESS;
	}
	
	return YEBehaviourStatus::FAILURE;
}

YEBehaviourStatus PlayerOpponentBehaviour::MoveHandle()
{
	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	if (_goRight && !_handleAlignedWithBall)
	{
		phsyX->MoveKinematicPulleyJointBody(2, 1, -2.4f, 5.2f);
		phsyX->MoveKinematicPulleyJointBody(3, 1, -2.4f, 5.2f);
		
		if (_isDefending)
			phsyX->MoveKinematicPulleyJointBody(4, 1, -1.7f, 1.5f);
		else
			phsyX->MoveKinematicPulleyJointBody(4, 1, -2.4f, 5.2f);
	}
	if (_goLeft && !_handleAlignedWithBall)
	{
		phsyX->MoveKinematicPulleyJointBody(2, -1, -2.4f, 5.2f);
		phsyX->MoveKinematicPulleyJointBody(3, -1, -2.4f, 5.2f);

		if (_isDefending)
			phsyX->MoveKinematicPulleyJointBody(4, -1, -1.7f, 1.5f);
		else
			phsyX->MoveKinematicPulleyJointBody(4, -1, -2.4f, 5.2f);
	}

	if (!_keeperAlignedWithBall)
	{
		if (_BallPosition._x > _KeeperPosition._x + 0.2f)
			phsyX->MoveKinematicPulleyJointBody(4, 1, -1.7f, 1.5f);
		if (_BallPosition._x < _KeeperPosition._x - 0.2f)
			phsyX->MoveKinematicPulleyJointBody(4, -1, -1.7f, 1.5f);
	}

	return YEBehaviourStatus::SUCCESS;
}

YEBehaviourStatus PlayerOpponentBehaviour::WatchBall()
{
	YELog("PlayerOpponentBehaviour: Watching Ball executed.");

	return YEBehaviourStatus::SUCCESS;
}
