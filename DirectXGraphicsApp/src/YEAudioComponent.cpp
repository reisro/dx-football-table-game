#include "YEAudioComponent.h"

YEAudioComponent::YEAudioComponent(bool looping):
	_audioEngine(new YEAudio),
	_loop(looping)
{
}

YEAudioComponent::~YEAudioComponent()
{
}

void YEAudioComponent::start()
{
	_audioEngine->initialize();
}

void YEAudioComponent::shutdown()
{
}

void YEAudioComponent::update(float _deltaTime)
{
}

void YEAudioComponent::LoadSound(const char* name, const char* file)
{
	if (_loop)
		_audioEngine->LoadLoopSound(name, file);
	else
		_audioEngine->LoadOneShotSound(name, file);
}

void YEAudioComponent::PlaySound(const char* name)
{
	_audioEngine->PlaySound(name, false, 0.5f, 1);
}

void YEAudioComponent::StopSound()
{
}
