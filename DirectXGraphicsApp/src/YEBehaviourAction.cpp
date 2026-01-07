#include "YEBehaviourAction.h"

YEBehaviourAction::YEBehaviourAction(std::function<YEBehaviourStatus(void)> action):
	_mAction(action)
{
}

YEBehaviourAction::~YEBehaviourAction()
{
}

YEBehaviourStatus YEBehaviourAction::Execute()
{
	return _mAction();
}
