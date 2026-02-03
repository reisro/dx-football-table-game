#pragma once

#ifndef _YE_AUDIO_COMPONENT_H_
#define _YE_AUDIO_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEAudio.h"

class DX_API YEAudioComponent : public YEBaseComponent
{
public:
	YEAudioComponent(bool looping);
	virtual ~YEAudioComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void LoadSound(const char* name, const char* file);
	void PlaySound(const char* name);
	void StopSound();
	void SetVolume(float volume) { _volume = volume;}
	void SetPriority(int priority) { _priority = priority; }

private:
	const char* _soundBankLocation;
	float		_volume;
	int			_priority;
	bool		_loop;

	YEAudio* _audioEngine;
};

#endif