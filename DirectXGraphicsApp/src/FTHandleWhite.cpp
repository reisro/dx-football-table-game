#include "FTHandleWhite.h"
#include <FTPlayerWhite.h>

FTHandleWhite::FTHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName)
	: FTHandle(_game_context, p1, p2, meshName),
	_player_right(reinterpret_cast<FTPlayerWhite*>(p1)),
	_player_left(reinterpret_cast<FTPlayerWhite*>(p2)),
	_behaviour_tree(new PlayerOpponentBehaviour) {}

FTHandleWhite::~FTHandleWhite()
{
	_behaviour_tree = nullptr;
}

void FTHandleWhite::start()
{
	FTHandle::start();

	YEBehaviourNode* rootNode = new YESelector();

	YESequence* sequenceNode = new YESequence();
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::WatchBall, _behaviour_tree)));
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));

	rootNode->AddChild(sequenceNode);

	YESequence* moveSequenceNode = new YESequence();
	moveSequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::MoveHandle, _behaviour_tree)));

	rootNode->AddChild(moveSequenceNode);

	_behaviour_tree->SetComposite(rootNode);
}

void FTHandleWhite::shutdown()
{
	FTHandle::shutdown();
}

void FTHandleWhite::update(float _deltaTime)
{
	FTHandle::update(_deltaTime);

	YELog("FTHandleWHite: Player Left from Ball : %f" + std::to_string(_player_left->_distanceFromBall));
	YELog("FTHandleWHite: Player Right from Ball : %f" + std::to_string(_player_right->_distanceFromBall));
	YELog("FTHandleWHite: Player Right from Center : %f" + std::to_string(_player_right->_distanceFromCenter));

	if (_player_left->_distanceFromBall < 0.35f || _player_right->_distanceFromBall < 0.35f)
		_behaviour_tree->_closeToShoot = true;
	else
	{
		_behaviour_tree->_closeToShoot = false;
	}

	//if (_player_right->_distanceFromBall < _player_left->_distanceFromBall)
	//{
		//_behaviour_tree->_goRight = true;
		//_behaviour_tree->_goLeft = false;

		if (_player_right->_distanceFromBall < 3.638f)
			_behaviour_tree->_alignedWithBall = true;
		else
			_behaviour_tree->_alignedWithBall = false;
	//}
	/*else
	{
		_behaviour_tree->_goLeft = true;
		_behaviour_tree->_goRight = false;*/

		if (_player_left->_distanceFromBall < 3.638f)
			_behaviour_tree->_alignedWithBall = true;
		else
			_behaviour_tree->_alignedWithBall = false;
	//}

	_behaviour_tree->Execute();
}

PlayerOpponentBehaviour* FTHandleWhite::GetBehaviourTree()
{
	return _behaviour_tree;
}
