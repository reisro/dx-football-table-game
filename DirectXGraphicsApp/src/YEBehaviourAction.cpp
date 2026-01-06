#include "YEBehaviourAction.h"

YEBehaviourAction::YEBehaviourAction(std::function<YEBehaviourStatus(void)> action)
{
}

YEBehaviourAction::~YEBehaviourAction()
{
}

YEBehaviourStatus YEBehaviourAction::Execute()
{
	return YEBehaviourStatus();
}
