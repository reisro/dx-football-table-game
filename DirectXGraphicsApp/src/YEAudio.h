#pragma once

#ifndef _YE_AUDIO_H_
#define _YE_AUDIO_H_

#include "DXAPI.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <unordered_map>

class DX_API YEAudio
{
public:
	YEAudio();
	virtual ~YEAudio();

	bool initialize();
	void Update();
	void Shutdown();

	bool CheckError(FMOD_RESULT result, const char* context);
	bool LoadSound(const char* filename, const char* soundName);
	void UnloadSound(const char* filename);

	FMOD::Channel* PlaySound(const char* soundName, bool paused = false);
	FMOD::System*  GetSystem() { return _mSystem; }

private:
	FMOD::System* _mSystem;
	std::unordered_map<const char*, FMOD::Sound*> _loadedSounds;
};

#endif