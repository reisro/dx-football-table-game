#include "AIPlayerOpponent.h"

AIPlayerOpponent::AIPlayerOpponent(const YEGameContext& _game_context, FTHandleWhite* handle, FTSingleHandleWhite* keeper, YEGameObject* _football_ball):
	YEGameObject("AI Player Opponent", _game_context), _handleFront(handle), _captureTime(false), _handleKeeper(keeper),
	_behaviour_tree(new PlayerOpponentBehaviour()), _target(_football_ball)
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
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::MoveHandle, _behaviour_tree)));
	sequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Deffend, _behaviour_tree)));
	rootNode->AddChild(sequenceNode);

	YESequence* attackSequenceNode = new YESequence();
	attackSequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::MoveHandle, _behaviour_tree)));
	attackSequenceNode->AddChild(new YEBehaviourAction(std::bind(&PlayerOpponentBehaviour::Attack, _behaviour_tree)));
	rootNode->AddChild(attackSequenceNode);

	_behaviour_tree->SetComposite(rootNode);
}

void AIPlayerOpponent::shutdown()
{
	YEGameObject::shutdown();
}

void AIPlayerOpponent::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	if (_active)
	{
		_behaviour_tree->Execute();

		WatchBallDirection();
	}
}

void AIPlayerOpponent::Play()
{
	_active = true;
}

void AIPlayerOpponent::Stop()
{
	_active = false;
}

void AIPlayerOpponent::WatchBallDirection()
{
	_currentBallPos = _target->_transform->getPosition();

	yeFloat distanceZ = _currentBallPos->_z;
	YELog("AI Player Opponent: Ball Direction Z: " + std::to_string(distanceZ));

	yeFloat x_right =  _handleFront->GetPlayerRight()->_distanceX;
	yeFloat x_left =   _handleFront->GetPlayerLeft()->_distanceX;
	yeFloat x_keeper = _handleKeeper->GetKeeper()->_distanceX;

	// Check if the ball is moving towards or away from the opponent's goal
	if (distanceZ > 0.0f)
		_behaviour_tree->_isDefending = true;
	else
		_behaviour_tree->_isDefending = false;

	_behaviour_tree->_BallPosition = *_currentBallPos;
	_behaviour_tree->_KeeperPosition = *(_handleKeeper->GetKeeper()->GetPosition());

	if (_currentBallPos->_x > x_keeper || _currentBallPos->_x < x_keeper)
		_behaviour_tree->_keeperAlignedWithBall = false;
	else
		_behaviour_tree->_keeperAlignedWithBall = true;

	if (_currentBallPos->_x >= x_left && _currentBallPos->_x <= x_right)
	{
		_behaviour_tree->_handleAlignedWithBall = true;
		_behaviour_tree->_goLeft = false;
		_behaviour_tree->_goRight = false;

		YELog("AI Player Opponent: Aligned with Ball");
	}
	else
	{
		if (_currentBallPos->_x < x_left)
		{
			if (_timer->Countdown(1))
			{
				YELog("AI Player Opponent: Ball is to the Left");
				_behaviour_tree->_goLeft = true;
				_behaviour_tree->_goRight = false;
				_behaviour_tree->_handleAlignedWithBall = false;
			}
		}
		else if (_currentBallPos->_x > x_right)
		{
			if (_timer->Countdown(1))
			{
				YELog("AI Player Opponent: Ball is to the Right");
				_behaviour_tree->_goRight = true;
				_behaviour_tree->_goLeft = false;
				_behaviour_tree->_handleAlignedWithBall = false;
			}
		}
	}

	// Check if any player is close to the ball to shoot
	if (_handleFront->GetPlayerLeft()->_distanceFromBall < 0.7f || _handleFront->GetPlayerRight()->_distanceFromBall < 0.7f)
	{
		_behaviour_tree->_closeToShoot = true;
		_behaviour_tree->_frontCanShoot = true;
	}
	else
	{
		if (!_behaviour_tree->_keeperCanShoot)
			_behaviour_tree->_closeToShoot = false;
	}

	if (_handleKeeper->GetKeeper()->_distanceFromBall < 0.7f)
	{
		_behaviour_tree->_closeToShoot = true;
		_behaviour_tree->_keeperCanShoot = true;
	}
	else
	{
		if (!_behaviour_tree->_frontCanShoot)
			_behaviour_tree->_closeToShoot = false;

		_behaviour_tree->_keeperCanShoot = false;
	}
}