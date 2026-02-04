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
		phsyX->MoveKinematicPulleyJointBody(0, 1, -2.4f, 5.2f);
		phsyX->MoveKinematicPulleyJointBody(1, 1, -2.4f, 5.2f);
	}

	// Move Left Player
	if (_yeInput->keyDown(DIK_D))
	{
		phsyX->MoveKinematicPulleyJointBody(0, -1, -2.4f, 5.2f);
		phsyX->MoveKinematicPulleyJointBody(1, -1, -2.4f, 5.2f);
	}

	// Rotate Handle Players
	if (_yeInput->keyDown(DIK_W))
	{
		phsyX->RotatePulleyJointBody(0, 0.08f, 0.1f, 7.0f, 3.0f, 3.0f);
		phsyX->RotatePulleyJointBody(1, 0.08f, 0.1f, 7.0f, 3.0f, 3.0f);
	}

	// Reset Dynamic Sphere Position
	if (_yeInput->keyDown(DIK_R))
		phsyX->ResetDynamicSphere();
}