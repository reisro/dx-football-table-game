#pragma once

#ifndef _FT_BACKGROUND_SOUNDTRACK_H_
#define _FT_BACKGROUND_SOUNDTRACK_H_

#include "YEGameObject.h"
#include "YEAudioComponent.h"

class FTBackgroundSoundtrack : public YEGameObject
{
public:
	FTBackgroundSoundtrack(const YEGameContext& _game_context, const char* filename);
	virtual ~FTBackgroundSoundtrack();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	private:
	YEAudioComponent* _audio_component;
	const char*		  _soundFilename;
};

#endif _FT_BACKGROUND_SOUNDTRACK_H_