#pragma once

#ifndef YE_COMPOSITES_H
#define YE_COMPOSITES_H

#include "DXAPI.h"
#include <vector>

enum class YEBehaviourStatus
{
	SUCCESS,
	FAILURE,
	RUNNING
};

class DX_API YEBehaviourNode
{
	public:
	YEBehaviourNode() {}
	virtual ~YEBehaviourNode() {}

	virtual YEBehaviourStatus Execute() = 0;

	void AddChild(YEBehaviourNode* child)
	{
		_children.push_back(child);
	}

protected:
	std::vector<YEBehaviourNode*> _children;
};

class YESequence : public YEBehaviourNode
{
	public:
		YESequence() {}
		virtual ~YESequence() {}

		YEBehaviourStatus Execute() override;
};

class DX_API YESelector : public YEBehaviourNode
{
	public:
		YESelector() {}
		virtual ~YESelector() {}

		YEBehaviourStatus Execute() override;
};

class YEPartialSequence : public YEBehaviourNode
{
	public:
		YEPartialSequence() {}
		virtual ~YEPartialSequence() {}

		YEBehaviourStatus Execute() override;
};

#endif // YE_COMPOSITES_H