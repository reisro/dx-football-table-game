#pragma once

#ifndef _YE_TIME_BEHAVIOUR_ACTION_H_
#define _YE_TIME_BEHAVIOUR_ACTION_H_

#include "YEComposites.h"
#include "DXAPI.h"
#include "YETimer.h"
#include <functional>

class DX_API YETimeBehaviourAction : public YEBehaviourNode
{
public:
	YETimeBehaviourAction(std::function<YEBehaviourStatus(void)> actionf,
		std::function<YEBehaviourStatus(void)> actions);
	virtual ~YETimeBehaviourAction();

	YEBehaviourStatus Execute() override;

private:
	std::function<YEBehaviourStatus(void)> _mfirstAction;
	std::function<YEBehaviourStatus(void)> _msecondAction;

	YETimer* _timer;
};

#endif // _YE_BEHAVIOUR_ACTION_H_