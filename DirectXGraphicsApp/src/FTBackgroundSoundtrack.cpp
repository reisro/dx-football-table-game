#include "FTBackgroundSoundtrack.h"

FTBackgroundSoundtrack::FTBackgroundSoundtrack(const YEGameContext& _game_context, const char* filename):
	YEGameObject("Background Soundtrack", _game_context),
	_soundFilename(filename),
	_audio_component(new YEAudioComponent(true))
{
	addComponent(_audio_component);
}

FTBackgroundSoundtrack::~FTBackgroundSoundtrack()
{
}

void FTBackgroundSoundtrack::start()
{
	_audio_component->start();

	_audio_component->LoadSound("Background Soundtrack",_soundFilename);

	_audio_component->SetVolume(0.5f);

	_audio_component->SetPriority(2);

	_audio_component->PlaySound("Background Soundtrack");
}

void FTBackgroundSoundtrack::shutdown()
{
}

void FTBackgroundSoundtrack::update(float _deltaTime)
{
}
