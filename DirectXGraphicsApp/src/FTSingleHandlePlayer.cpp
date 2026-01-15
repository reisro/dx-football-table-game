#include "FTSingleHandlePlayer.h"
#include "YEPhysX.h"

FTSingleHandlePlayer::FTSingleHandlePlayer(const YEGameContext& _game_context, FTPlayer* p1, const wchar_t* meshName):
	FTSingleHandle(_game_context, p1, meshName), _yeInput(YEInput::GetInstance())
{
}

FTSingleHandlePlayer::~FTSingleHandlePlayer()
{
}

void FTSingleHandlePlayer::start()
{
	FTSingleHandle::start();
}

void FTSingleHandlePlayer::shutdown()
{
	FTSingleHandle::shutdown();
}

void FTSingleHandlePlayer::update(float _deltaTime)
{
	FTSingleHandle::update(_deltaTime);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	if (_yeInput->mouseButtonDown(1))
	{
		phsyX->MoveKinematicPulleyJointBody(5, 1, -5.0f, 5.3f);
	}

	if(_yeInput->keyDown(DIK_LEFT))
	{
		phsyX->MoveKinematicPulleyJointBody(5, 1, -5.0f, 5.3f);
	}
	
	if (_yeInput->keyDown(DIK_RIGHT))
	{
		phsyX->MoveKinematicPulleyJointBody(5, -1, -5.0f, 5.3f);
	}
}