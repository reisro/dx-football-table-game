#pragma once

#ifndef _FT_REFEREE_H_
#define _FT_REFEREE_H_

#include "YEGameObject.h"
#include "YEAudioComponent.h"
#include <functional>

class FTReferee : public YEGameObject
{
public:
	FTReferee(const YEGameContext& _game_context);
	virtual ~FTReferee();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void KickOff();
	void BallToTheCenter();
	void PlayAfterGoal();

	std::function<void(void)> OnStartMatch;

protected:
	YEAudioComponent* _audio_component;

private:

};

#endif _FT_REFEREE_H_