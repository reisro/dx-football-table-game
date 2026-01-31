#include "YEAudioComponent.h"

YEAudioComponent::YEAudioComponent():
	_audioEngine(new YEAudio)
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

void YEAudioComponent::LoadSound(const char* file)
{
	_audioEngine->LoadSound("Background", file);
}

void YEAudioComponent::PlaySound()
{
	_audioEngine->PlaySound("Background");
}

void YEAudioComponent::StopSound()
{
}
