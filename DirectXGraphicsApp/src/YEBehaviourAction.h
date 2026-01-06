#pragma once

#ifndef _YE_BEHAVIOUR_ACTION_H_
#define _YE_BEHAVIOUR_ACTION_H_

#include "YEComposites.h"
#include "DXAPI.h"
#include <functional>

class DX_API YEBehaviourAction : public YEBehaviourNode
{
public:
	YEBehaviourAction(std::function<YEBehaviourStatus(void)> action);
	virtual ~YEBehaviourAction();

	YEBehaviourStatus Execute() override;

private:
	std::function<YEBehaviourStatus(void)> _mAction;
};

#endif // _YE_BEHAVIOUR_ACTION_H_