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
	bool CheckError(FMOD_RESULT result, const char* context);

private:
	FMOD::System* _mSystem;
};

#endif