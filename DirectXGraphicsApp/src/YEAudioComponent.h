#pragma once

#ifndef _YE_AUDIO_COMPONENT_H_
#define _YE_AUDIO_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEAudio.h"

class DX_API YEAudioComponent : public YEBaseComponent
{
public:
	YEAudioComponent();
	virtual ~YEAudioComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void LoadSound(const char* file);
	void PlaySound();
	void StopSound();

private:
	const char* _soundBankLocation;
	YEAudio* _audioEngine;
};

#endif