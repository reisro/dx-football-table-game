#pragma once

#ifndef YE_COMPOSITES_H
#define YE_COMPOSITES_H

enum class YEBehaviourStatus
{
	SUCCESS,
	FAILURE,
	RUNNING
};

class YEBehaviourNode
{
	public:
	YEBehaviourNode() {}
	virtual ~YEBehaviourNode() {}

	virtual YEBehaviourStatus Execute() = 0;
};

class YESequence : public YEBehaviourNode
{
	public:
		YESequence() {}
		virtual ~YESequence() {}

		YEBehaviourStatus Execute() override {}
};

class YESelector : public YEBehaviourNode
{
	public:
		YESelector() {}
		virtual ~YESelector() {}

		YEBehaviourStatus Execute() override {}
};

class YEPartialSequence : public YEBehaviourNode
{
	public:
		YEPartialSequence() {}
		virtual ~YEPartialSequence() {}

		YEBehaviourStatus Execute() override {}
};

#endif // YE_COMPOSITES_H