#include "YEComposites.h"

YEBehaviourStatus YESequence::Execute()
{
    for (YEBehaviourNode* child : _children)
    {
        YEBehaviourStatus status = child->Execute();
        switch (status)
        {
        case YEBehaviourStatus::FAILURE:
            return status;
        case YEBehaviourStatus::RUNNING:
            return status;
        case YEBehaviourStatus::SUCCESS:
            continue;
		default:
			continue;
        }
    }

    return YEBehaviourStatus::SUCCESS;
}