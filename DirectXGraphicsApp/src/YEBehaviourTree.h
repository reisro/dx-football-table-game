#pragma once

#ifndef _YE_BEHAVIOUR_TREE_H_
#define _YE_BEHAVIOUR_TREE_H_

#include "DXAPI.h"
#include "YEComposites.h"

class DX_API YEBehaviourTree
{
public:
	YEBehaviourTree();
	virtual ~YEBehaviourTree();

	YEBehaviourStatus Execute()
	{
		if (_compositeNode)
		{
			return _compositeNode->Execute();
		}
		return YEBehaviourStatus::FAILURE;
	}

	void SetComposite(YEBehaviourNode* composite) { _compositeNode = composite; }

private:
	YEBehaviourNode* _compositeNode;
};

#endif // _YE_BEHAVIOUR_TREE_H_