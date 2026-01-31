#pragma once

#ifndef _YE_AUDIO_H_
#define _YE_AUDIO_H_

#include "DXAPI.h"
#include <fmod.hpp>
#include <fmod_errors.h>

class DX_API YEAudio
{
public:
	YEAudio();
	virtual ~YEAudio();

	bool initialize();
	void Update();
	void Shutdown();

	bool CheckError(FMOD_RESULT result, const char* context);

	FMOD::System* GetSystem() { return _mSystem; }

private:
	FMOD::System* _mSystem;
};

#endif