#include "FTReferee.h"

FTReferee::FTReferee(const YEGameContext& _game_context):
	YEGameObject("FTReferee", _game_context),
	_audio_component(new YEAudioComponent(false))
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

void FTReferee::BoolWhistle()
{
	_audio_component->PlaySound("Whistle");
}
