#include "YEComposites.h"

YEBehaviourStatus YESelector::Execute()
{
	for (YEBehaviourNode* child : _children)
	{
		YEBehaviourStatus status = child->Execute();
		if (status == YEBehaviourStatus::SUCCESS)
		{
			return YEBehaviourStatus::SUCCESS;
		}
		else if (status == YEBehaviourStatus::RUNNING)
		{
			return YEBehaviourStatus::RUNNING;
		}
	}
	return YEBehaviourStatus::FAILURE;
}
