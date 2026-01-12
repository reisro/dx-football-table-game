#include "FTSingleHandleWhite.h"
#include "YEPhysX.h"

FTSingleHandleWhite::FTSingleHandleWhite(const YEGameContext& _game_context, FTPlayer* p1, const wchar_t* meshName):
	FTSingleHandle(_game_context, p1, p1, meshName),
	_behaviour_tree(new PlayerOpponentBehaviour),
	_keeper(reinterpret_cast<FTPlayerWhite*>(p1))
{
}

FTSingleHandleWhite::~FTSingleHandleWhite()
{
}

void FTSingleHandleWhite::start()
{
	FTSingleHandle::start();
}

void FTSingleHandleWhite::shutdown()
{
	FTSingleHandle::shutdown();
}

void FTSingleHandleWhite::update(float _deltaTime)
{
	FTSingleHandle::update(_deltaTime);

	//YELog("FTSingleHandleWhite: Keeper from Ball : %f" + std::to_string(_keeper->_distanceFromBall));
	/*if (_keeper->_distanceFromBall < 0.35f)
		_behaviour_tree->_closeToShoot = true;
	else
	{
		_behaviour_tree->_closeToShoot = false;
	}*/
}

PlayerOpponentBehaviour* FTSingleHandleWhite::GetBehaviourTree()
{
	return _behaviour_tree;
}
