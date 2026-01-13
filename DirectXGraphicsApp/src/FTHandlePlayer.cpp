#include "FTHandlePlayer.h"
#include "YEPhysX.h"

FTHandlePlayer::FTHandlePlayer(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName) :
	FTHandle(_game_context,p1,p2,meshName),
	_yeInput(YEInput::GetInstance())
{
}

FTHandlePlayer::~FTHandlePlayer()
{
}

void FTHandlePlayer::start()
{
	FTHandle::start();
}

void FTHandlePlayer::shutdown()
{
	FTHandle::shutdown();
}

void FTHandlePlayer::update(float _deltaTime)
{
	FTHandle::update(_deltaTime);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	// Move Right Player
	if (_yeInput->keyDown(DIK_A))
	{
		phsyX->MoveKinematicPulleyJointBody(0, 1, -2.4f, 5.0f);
		phsyX->MoveKinematicPulleyJointBody(1, 1, -2.4f, 5.0f);
	}

	// Move Left Player
	if (_yeInput->keyDown(DIK_D))
	{
		phsyX->MoveKinematicPulleyJointBody(0, -1, -2.4f, 5.0f);
		phsyX->MoveKinematicPulleyJointBody(1, -1, -2.4f, 5.0f);
	}
}