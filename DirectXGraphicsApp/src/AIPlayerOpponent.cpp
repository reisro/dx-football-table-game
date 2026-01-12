#include "AIPlayerOpponent.h"

AIPlayerOpponent::AIPlayerOpponent(const YEGameContext& _game_context, FTHandleWhite* handle, FTSingleHandleWhite* keeper):
	YEGameObject(_game_context), _handleFront(handle), _captureTime(false), _handleKeeper(keeper), 
	_behaviour_tree(new PlayerOpponentBehaviour())
{
	_currentBallPos = YEVector3::Zero();
	_lastBallPos = YEVector3::Zero();
	_timer = YETimer::GetInstance();
}

AIPlayerOpponent::~AIPlayerOpponent()
{
	_currentBallPos = nullptr;
	_lastBallPos = nullptr;
	_timer = nullptr;
}

void AIPlayerOpponent::start()
{
	YEGameObject::start();

	YEBehaviourNode* rootNode = new YESelector();

	YESequence* sequenceNode = new YESequence();
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::WatchBall, _behaviour_tree)));
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Deffend, _behaviour_tree)));

	rootNode->AddChild(sequenceNode);

	YESequence* moveSequenceNode = new YESequence();
	moveSequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::MoveHandle, _behaviour_tree)));

	//rootNode->AddChild(sequenceNode);

	_behaviour_tree->SetComposite(rootNode);
}

void AIPlayerOpponent::shutdown()
{
	YEGameObject::shutdown();
}

void AIPlayerOpponent::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	_behaviour_tree->_P1Position = *_handleFront->GetPlayerLeft()->_transform->getPosition();
	_behaviour_tree->_P2Position = *_handleFront->GetPlayerRight()->_transform->getPosition();

	_behaviour_tree->Execute();
}

void AIPlayerOpponent::WatchBallDirection(FTBall* _football_ball)
{
	/*if (!_captureTime)
	{
		_lastBallPos = _football_ball->_transform->getPosition();

		footballPosAux = *_lastBallPos;
		_captureTime = true;
	}

	if (_timer->Countdown(1))
	{
		_captureTime = false;
	}*/

	_currentBallPos = _football_ball->_transform->getPosition();

	yeFloat distanceZ = _currentBallPos->_z;
	YELog("AI Player Opponent: Ball Direction Z: " + std::to_string(distanceZ));

	// Check if the ball is moving towards or away from the opponent's goal
	if (distanceZ > 0.0f)
		_behaviour_tree->_isDefending = true;
	else
	{
		_behaviour_tree->_isDefending = false;
	}

	// Check if any player is close to the ball to shoot
	/*if (_handleFront->GetPlayerLeft()->_distanceFromBall < 0.35f || _handleFront->GetPlayerRight()->_distanceFromBall < 0.35f)
		_behaviour_tree->_closeToShoot = true;
	else
		_behaviour_tree->_closeToShoot = false;*/

	yeFloat x_right = _handleFront->GetPlayerRight()->_distanceX;
	yeFloat x_left =  _handleFront->GetPlayerLeft()->_distanceX;

	// Check if players are aligned with the ball
	//if (x_right >= -1.0f && x_right <= 1.0f || x_left >= -1.0f && x_left <= 1.0f)
	//{
	//	//3.638f
	//	_behaviour_tree->_alignedWithBall = true;
	//	_behaviour_tree->_goLeft = false;
	//	_behaviour_tree->_goRight = false;

	//	YELog("AI Player Opponent: Aligned with Ball");
	//}
	//else
	//{
		if (_currentBallPos->_x >= _handleFront->GetPlayerLeft()->_transform->getPosition()->_x &&
			_currentBallPos->_x <= _handleFront->GetPlayerRight()->_transform->getPosition()->_x)
		{
			_behaviour_tree->_alignedWithBall = true;
			_behaviour_tree->_goLeft = false;
			_behaviour_tree->_goRight = false;

			YELog("AI Player Opponent: Aligned with Ball");
		} 
		else
		{
			if (_currentBallPos->_x < _handleFront->GetPlayerLeft()->_transform->getPosition()->_x)
			{
				if (_timer->Countdown(2))
				{
					YELog("AI Player Opponent: Ball is to the Left");
					_behaviour_tree->_goLeft = true;
					_behaviour_tree->_goRight = false;
					_behaviour_tree->_alignedWithBall = false;
				}
			}
			else
			{
				if (_timer->Countdown(2))
				{
					YELog("AI Player Opponent: Ball is to the Right");
					_behaviour_tree->_goRight = true;
					_behaviour_tree->_goLeft = false;
					_behaviour_tree->_alignedWithBall = false;
				}
			}
		}
	//}
}
