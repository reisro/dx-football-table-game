#include "PlayerOpponentBehaviour.h"

PlayerOpponentBehaviour::PlayerOpponentBehaviour()
{
}

PlayerOpponentBehaviour::~PlayerOpponentBehaviour()
{
}

YEBehaviourStatus PlayerOpponentBehaviour::Defend()
{
	return YEBehaviourStatus();
}

YEBehaviourStatus PlayerOpponentBehaviour::Attack()
{
	YELog("PlayerOpponentBehaviour: Attack executed.");

	return YEBehaviourStatus::SUCCESS;
}
