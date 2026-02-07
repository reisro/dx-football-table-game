#pragma once

#ifndef _FT_REFEREE_H_
#define _FT_REFEREE_H_

#include "YEGameObject.h"
#include "YEAudioComponent.h"
#include "YETimer.h"
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
	std::function<void(void)> OnTimerRunsOut;

protected:
	YEAudioComponent* _audio_component;

private:
	bool _timerStarts;
	YETimer* _timer;
};

#endif _FT_REFEREE_H_