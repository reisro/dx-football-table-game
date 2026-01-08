#include "FTHandleWhite.h"

FTHandleWhite::FTHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName)
	: FTHandle(_game_context, p1, p2, meshName),
	_behaviour_tree(nullptr) {}

FTHandleWhite::~FTHandleWhite()
{
	_behaviour_tree = nullptr;
}

void FTHandleWhite::start()
{
	FTHandle::start();

	_behaviour_tree = new PlayerOpponentBehaviour();

	YEBehaviourNode* rootNode = new YESelector();

	YESequence* sequenceNode = new YESequence();
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::WatchBall, _behaviour_tree)));
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));

	rootNode->AddChild(sequenceNode);

	_behaviour_tree->SetComposite(sequenceNode);
}

void FTHandleWhite::shutdown()
{
	FTHandle::shutdown();
}

void FTHandleWhite::update(float _deltaTime)
{
	FTHandle::update(_deltaTime);

	_behaviour_tree->Execute();
}