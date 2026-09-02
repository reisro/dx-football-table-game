#include "FTSingleHandleWhite.h"
#include "YEPhysX.h"

FTSingleHandleWhite::FTSingleHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, const char* meshName):
	FTSingleHandle(_game_context, p1, meshName),
	_player_left(reinterpret_cast<FTPlayerWhite*>(p1))
{
}

FTSingleHandleWhite::~FTSingleHandleWhite()
{
}

void FTSingleHandleWhite::start()
{
	FTSingleHandle::start();
}

void FTSingleHandleWhite::shutdown()
{
	FTSingleHandle::shutdown();
}

void FTSingleHandleWhite::update(float _deltaTime)
{
	FTSingleHandle::update(_deltaTime);

	//YELog("FTSingleHandleWHite: Keeper from Ball : %f" + std::to_string(_player_left->_distanceFromBall));

	//YELog("FTSingleHandleWhite: Keeper from Ball : %f" + std::to_string(_keeper->_distanceFromBall));
	/*if (_keeper->_distanceFromBall < 0.35f)
		_behaviour_tree->_closeToShoot = true;
	else
	{
		_behaviour_tree->_closeToShoot = false;
	}*/

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	// Update Pulley Joint Bodies
	//phsyX->SetKinematicPulleyJointBody(4);
}
