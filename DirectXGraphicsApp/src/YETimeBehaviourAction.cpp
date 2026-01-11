#include "YETimeBehaviourAction.h"	

YETimeBehaviourAction::YETimeBehaviourAction(std::function<YEBehaviourStatus(void)> actionf,
	std::function<YEBehaviourStatus(void)> actions) :
	_mfirstAction(actionf),
	_msecondAction(actions),
	_timer(YETimer::GetInstance())
{
}

YETimeBehaviourAction::~YETimeBehaviourAction()
{
}

YEBehaviourStatus YETimeBehaviourAction::Execute()
{
	YEBehaviourStatus status = _mfirstAction();

	if (_timer->Countdown(3))
		return _msecondAction();
}
