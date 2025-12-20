#include "GameEntry.h"
#include <FTBall.h>
#include <FTField.h>
#include <FTPlayer.h>
#include <FTPlayerWhite.h>
#include <FTHandle.h>

using namespace gamentry;

class Cube: public YEGame
{
public:
	Cube() : YEGame("Default Cube")
	{
	}

	Cube(const char* _game_name) :
		YEGame(_game_name)
	{
	}

	void init() override
	{
		// Game Objects creation
		football_field = new FTField(GetGameContext());
		football_field->hasRigidBody = true;

		football_ball = new FTBall(GetGameContext());
		football_ball->hasRigidBody = true;
		
		football_player = new FTPlayer(GetGameContext());
		football_player->hasParent = true;
		football_player->hasRigidBody = true;

		football_player2 = new FTPlayer(GetGameContext());
		football_player2->hasParent = true;
		football_player2->hasRigidBody = true;

		football_handle = new FTHandle(GetGameContext(), football_player, football_player2);

		// Start Game Objects
		football_field->start();
		football_field->_transform->setPosition(new YEVector3(0.0f, 0.0f, 0.0f));

		football_ball->start();
		football_ball->_transform->setPosition(new YEVector3(0.0f, 3.0f, 0.0f));

		football_player->start();
		football_player->_transform->setPosition(new YEVector3(0.0f, 0.9f, 3.63704f));

		football_player2->start();
		football_player2->_transform->setPosition(new YEVector3(3.0f, 0.9f, 3.63704f));

		football_handle->start();
		//football_handle->_transform->setPosition(new YEVector3(-0.67763f, 1.85f, 3.62057f));
	}

	bool update(dxDouble _deltaTime) override
	{
		newPosition = new YEVector3(0.0f, 0.0f, forward_speed);
		
		//moveDirection = YEVector3::Sum(*football_ball->GetPosition(), *newPosition);
		
		//football_field->update(static_cast<float>(_deltaTime));
		football_ball->update(static_cast<float>(_deltaTime));
		football_handle->update(static_cast<float>(_deltaTime));
		football_player->update(static_cast<float>(_deltaTime));
		football_player2->update(static_cast<float>(_deltaTime));

		forward_speed += 0.00000000001f;

		return true;
	}

	virtual void shutdown() override
	{
		YELog("Shutdown Cube Game...");
	}

private:
	const char* game_name;

	FTBall* football_ball;
	FTField* football_field;
	FTPlayer* football_player;
	FTPlayer* football_player2;
	FTPlayerWhite* football_player_white;
	FTHandle* football_handle;

	YEVector3* position;
	YEVector3* newPosition;
	YEVector3* moveDirection;

	yeFloat    forward_speed = 0.1f;
	yeFloat    mTheta;
	yeFloat    mPhi;
	yeFloat    mRadius;

	XMFLOAT4X4 mView;
};

WINDOW_MAIN_ENTRY(Cube);