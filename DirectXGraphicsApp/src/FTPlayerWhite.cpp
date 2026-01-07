#include "FTPlayerWhite.h"
#include <YEPhysX.h>
#include <functional> 

FTPlayerWhite::FTPlayerWhite(const YEGameContext& _game_context, const wchar_t* _meshName)
	: FTPlayer(_game_context, _meshName)
	, _behaviour_tree(nullptr)
{
}

FTPlayerWhite::~FTPlayerWhite()
{
}

void FTPlayerWhite::start()
{
	_behaviour_tree = new PlayerOpponentBehaviour();

	YEBehaviourNode* rootNode = new YESelector();

	rootNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));

	_behaviour_tree->SetComposite(rootNode); // Set the root node appropriately
}

void FTPlayerWhite::shutdown()
{
}

void FTPlayerWhite::update(float _deltaTime)
{
	FTPlayer::update(_deltaTime);

	_behaviour_tree->Execute();
}
