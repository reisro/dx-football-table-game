#include "FTReferee.h"
#include "YEPhysX.h"

FTReferee::FTReferee(const YEGameContext& _game_context):
	YEGameObject("FTReferee", _game_context),
	_audio_component(new YEAudioComponent(false)),
	_timerStarts(false),
	_timer(new YETimer)
{
	addComponent(_audio_component);
}

FTReferee::~FTReferee()
{
}

void FTReferee::start()
{
	_audio_component->start();
	_audio_component->LoadSound("Whistle", "C:\\Game Assets\\referee.wav");
	_audio_component->SetVolume(1.0f);
	_audio_component->SetPriority(1);
}

void FTReferee::shutdown()
{
}

void FTReferee::update(float _deltaTime)
{
}

void FTReferee::KickOff()
{
	_audio_component->PlaySound("Whistle");

	OnStartMatch();
}

void FTReferee::BallToTheCenter()
{
	_audio_component->PlaySound("Whistle");

	YEPhysX* physics = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
	physics->ResetDynamicSphere();
}

void FTReferee::PlayAfterGoal()
{
	static bool sendBallUp;

	_audio_component->PlaySound("Whistle");

	YEPhysX* physics = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
	
	sendBallUp = !sendBallUp;

	if (!sendBallUp)
		physics->AddForceToDynamicRigidBody(*new YEVector3(0.0, 0.0, -10.0));
	else
		physics->AddForceToDynamicRigidBody(*new YEVector3(0.0, 0.0, 10.0));

}
