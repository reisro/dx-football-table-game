#include "FTPlayerWhite.h"
#include "YEVector3.h"
#include "DXTypes.h"
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
	FTPlayer::start();

	_behaviour_tree = new PlayerOpponentBehaviour();

	YEBehaviourNode* rootNode = new YESelector();

	//rootNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));
	//rootNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Deffend, _behaviour_tree)));

	YESequence* sequenceNode = new YESequence();
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::WatchBall, _behaviour_tree)));
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));
	rootNode->AddChild(sequenceNode);

	_behaviour_tree->SetComposite(sequenceNode);
}

void FTPlayerWhite::shutdown()
{
}

void FTPlayerWhite::update(float _deltaTime)
{
	FTPlayer::update(_deltaTime);

	_behaviour_tree->Execute();
}

void FTPlayerWhite::DistanceFromTarget(YEGameObject* football_ball)
{
	YEVector3* diff = YEVector3::Subtract(*_transform->getPosition(), *football_ball->_transform->getPosition());

	yeFloat distance = diff->Magnitude();

	distance <= _ballDistanceThreshold ? _behaviour_tree->_closeToShoot = true : _behaviour_tree->_closeToShoot = false;

	YELog("Ball Distance: " + std::to_string(diff->Magnitude()));
}