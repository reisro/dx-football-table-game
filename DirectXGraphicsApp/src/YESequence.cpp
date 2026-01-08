#include "YEComposites.h"

YEBehaviourStatus YESequence::Execute()
{
    for (YEBehaviourNode* child : _children)
    {
        YEBehaviourStatus status = child->Execute();
        if (status == YEBehaviourStatus::FAILURE)
        {
            return YEBehaviourStatus::FAILURE;
        }
        else if (status == YEBehaviourStatus::RUNNING)
        {
            return YEBehaviourStatus::RUNNING;
        }
    }

    return YEBehaviourStatus::SUCCESS;
}