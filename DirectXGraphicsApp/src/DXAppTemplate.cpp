#include "GameEntry.h"
#include <FTBall.h>
#include <FTField.h>
#include <FTPlayer.h>
#include <FTPlayerWhite.h>
#include <FTHandle.h>
#include <FTSingleHandle.h>
#include <FTFieldWalls.h>

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

		football_walls = new FTFieldWalls(GetGameContext());

		football_ball = new FTBall(GetGameContext());
		football_ball->hasRigidBody = true;
		
		football_player = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player.fbx");
		football_player->hasParent = true;
		football_player->hasRigidBody = true;

		football_player2 = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player.fbx");
		football_player2->hasParent = true;
		football_player2->hasRigidBody = true;

		football_player_l = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx");
		football_player_l->hasParent = true;
		football_player_l->hasRigidBody = true;

		football_player2_l = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx");
		football_player2_l->hasParent = true;
		football_player2_l->hasRigidBody = true;

		football_keeper = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_white.fbx");
		football_keeper->hasRigidBody = true;
		football_keeper->hasParent = true;

		football_keeper_ai = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_red.fbx");
		football_keeper_ai->hasRigidBody = true;

		football_handle = new FTHandle(GetGameContext(), football_player, football_player2, L"C:\\Game Assets\\football_handle.fbx");

		football_handle_player = new FTHandle(GetGameContext(), football_player_l, football_player2_l, L"C:\\Game Assets\\football_handle.fbx");

		football_handle_keeper = new FTSingleHandle(GetGameContext(), football_keeper, football_keeper, L"C:\\Game Assets\\football_handle.fbx");
		football_handle_keeper1 = new FTSingleHandle(GetGameContext(), football_keeper_ai, nullptr, L"C:\\Game Assets\\football_handle.fbx");

		// Start Game Objects
		football_field->start();
		football_field->_transform->setPosition(new YEVector3(0.0f, 0.0f, 0.0f));

		football_walls->start();

		football_ball->start(); //0
		football_ball->_transform->setPosition(new YEVector3(0.0f, 3.0f, 0.0f));

		football_player->start(); //1
		football_player->_transform->setPosition(new YEVector3(0.0f, 0.85f, 3.85704f));

		football_player2->start(); //2
		football_player2->_transform->setPosition(new YEVector3(3.0f, 0.85f, 3.73704f));

		football_handle->_isCPU = true;
		football_handle->start();
		football_handle->_transform->setPosition(new YEVector3(0.0f, 1.15f, 3.62057f));

		football_player_l->start(); //3
		football_player_l->_transform->setPosition(new YEVector3(0.0f, 0.85f, -3.63704f));

		football_player2_l->start(); //4
		football_player2_l->_transform->setPosition(new YEVector3(6.0f, 0.85f, -3.63704f));

		football_handle_player->_isCPU = false;
		football_handle_player->start();
		football_handle_player->_transform->setPosition(new YEVector3(0.0f, 1.25f, -3.72057f));

		football_keeper->start(); //5
		football_keeper->_transform->setPosition(new YEVector3(3.0f, 0.85f, -9.25f));

		football_keeper_ai->start(); //6
		football_keeper_ai->_transform->setPosition(new YEVector3(3.0f, 0.85f, 8.85f));

		football_handle_keeper->_isCPU = false;
		football_handle_keeper->start();
		football_handle_keeper->_transform->setPosition(new YEVector3(0.0f, 0.85f, -8.5f));

		football_handle_keeper1->_isCPU = true;
		football_handle_keeper1->start();
		football_handle_keeper1->_transform->setPosition(new YEVector3(0.0f, 1.15f, 8.5f));
	}

	bool update(dxDouble _deltaTime) override
	{				
		football_ball->update(static_cast<float>(_deltaTime));
		football_handle->update(static_cast<float>(_deltaTime));
		football_player->update(static_cast<float>(_deltaTime));
		football_player2->update(static_cast<float>(_deltaTime));
		football_handle_player->update(static_cast<float>(_deltaTime));
		football_player_l->update(static_cast<float>(_deltaTime));
		football_player2_l->update(static_cast<float>(_deltaTime));
		football_keeper->update(static_cast<float>(_deltaTime));
		football_handle_keeper->update(static_cast<float>(_deltaTime));
		football_keeper_ai->update(static_cast<float>(_deltaTime));
		football_handle_keeper1->update(static_cast<float>(_deltaTime));

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
	FTPlayer* football_player_l;
	FTPlayer* football_player2_l;
	FTPlayer* football_keeper;
	FTPlayer* football_keeper_ai;
	FTPlayerWhite* football_player_white;
	FTHandle* football_handle;
	FTHandle* football_handle_player;
	FTSingleHandle* football_handle_keeper;
	FTSingleHandle* football_handle_keeper1;
	FTFieldWalls* football_walls;

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