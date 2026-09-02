#include "FTHandleWhite.h"
#include <FTPlayerWhite.h>
#include "FTSingleHandleWhite.h"
#include "YEPhysX.h"

FTHandleWhite::FTHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const char* meshName)
	: FTHandle(_game_context, p1, p2, meshName),
	_player_right(reinterpret_cast<FTPlayerWhite*>(p1)),
	_player_left(reinterpret_cast<FTPlayerWhite*>(p2))
{
}

FTHandleWhite::~FTHandleWhite()
{
}

void FTHandleWhite::start()
{
	FTHandle::start();
}

void FTHandleWhite::shutdown()
{
	FTHandle::shutdown();
}

void FTHandleWhite::update(float _deltaTime)
{
	FTHandle::update(_deltaTime);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	YELog("FTHandleWHite: Player Left from Ball : %f" + std::to_string(_player_left->_distanceFromBall));
	YELog("FTHandleWHite: Player Right from Ball : %f" + std::to_string(_player_right->_distanceFromBall));
	YELog("FTHandleWHite: Player Right from Center : %f" + std::to_string(_player_right->_distanceFromCenter));

	// Update Pulley Joint Bodies
	//phsyX->SetKinematicPulleyJointBody(2);
	//phsyX->SetKinematicPulleyJointBody(3);
}

void FTHandleWhite::MoveToCenter()
{
	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	phsyX->ResetMovePulleyJointBody(2);
	phsyX->ResetMovePulleyJointBody(3);
}