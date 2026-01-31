#include "GameEntry.h"
#include <FTBall.h>
#include <FTField.h>
#include <FTPlayer.h>
#include <FTPlayerWhite.h>
#include <FTHandleWhite.h>
#include <FTHandlePlayer.h>
#include <FTSingleHandle.h>
#include <FTSingleHandlePlayer.h>
#include <FTSingleHandleWhite.h>
#include <FTFieldWalls.h>
#include <AIPlayerOpponent.h>
#include <FTScore.h>
#include <FTGameRoom.h>
#include <FTScoreMarker.h>
#include <FTBackgroundSoundtrack.h>
#include <FTGameMainMenu.h>

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

		football_player_l = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx");
		football_player_l->hasParent = true;
		football_player_l->hasRigidBody = true;

		football_player2_l = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx");
		football_player2_l->hasParent = true;
		football_player2_l->hasRigidBody = true;

		football_keeper_ai = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_white.fbx");
		football_keeper_ai->hasRigidBody = true;

		football_keeper_player = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_red.fbx");
		football_keeper_player->hasRigidBody = true;

		// handle Player
		football_handle = new FTHandlePlayer(GetGameContext(), football_player, football_player2, L"C:\\Game Assets\\football_handle.fbx");

		// handle AI
		football_handle_player = new FTHandleWhite(GetGameContext(), football_player_l, football_player2_l, L"C:\\Game Assets\\football_handle.fbx");
		
		football_handle_keeper_ai = new FTSingleHandleWhite(GetGameContext(), football_keeper_ai, L"C:\\Game Assets\\football_handle.fbx");

		football_handle_keeper = new FTSingleHandlePlayer(GetGameContext(), football_keeper_player, L"C:\\Game Assets\\football_handle.fbx");

		ai_opponent = new AIPlayerOpponent(GetGameContext(), football_handle_player, football_handle_keeper_ai);

		football_score = new FTScore(GetGameContext());

		// Score markers 3D game objects
		score_marker_player = new FTScoreMarker(GetGameContext());
		score_marker_ai = new FTScoreMarker(GetGameContext());

		// Game Audio Soundtrack
		background_soundtrack = new FTBackgroundSoundtrack(GetGameContext(), "C:\\Game Assets\\footballtable_st.wav");

		// Game Main Menu Sprite Game Object
		main_menu = new FTGameMainMenu(GetGameContext());

		// Start Game Objects
		football_field->start();
		football_field->_transform->setPosition(new YEVector3(0.0f, 0.0f, 0.0f));

		football_walls->start();

		football_ball->start(); //0
		football_ball->_transform->setPosition(new YEVector3(0.0f, 3.0f, 0.0f));

		football_player->start(); //1
		football_player->_transform->setPosition(new YEVector3(0.0f, 0.85f, 3.85704f));

		football_player2->start(); //2
		football_player2->_transform->setPosition(new YEVector3(3.0f, 0.85f, 3.85704f));

		football_handle->_isCPU = true;
		football_handle->start();
		football_handle->_transform->setPosition(new YEVector3(0.0f, 1.15f, 3.62057f));

		football_player_l->start(); //3
		football_player_l->_transform->setPosition(new YEVector3(0.0f, 0.85f, -3.48704f));
		football_player_l->DistanceFromCenter();

		football_player2_l->start(); //4
		football_player2_l->_transform->setPosition(new YEVector3(3.0f, 0.85f, -3.48704f));
		football_player2_l->DistanceFromCenter();

		football_handle_player->_isCPU = false;
		football_handle_player->start();
		football_handle_player->_transform->setPosition(new YEVector3(0.0f, 1.15f, -3.02057f));

		football_keeper_ai->start(); //5
		football_keeper_ai->_transform->setPosition(new YEVector3(3.0f, 0.85f, -8.5f));

		football_handle_keeper_ai->_isCPU = false;
		football_handle_keeper_ai->start();
		football_handle_keeper_ai->_transform->setPosition(new YEVector3(0.0f, 0.85f, -8.5f));

		football_keeper_player->start(); //6
		football_keeper_player->_transform->setPosition(new YEVector3(3.0f, 0.85f, 8.85f));

		football_handle_keeper->_isCPU = true;
		football_handle_keeper->start();
		football_handle_keeper->_transform->setPosition(new YEVector3(0.0f, 0.85f, 8.5f));

		ai_opponent->start();

		score_marker_player->start();
		score_marker_player->_isPositiveOffset = false;
		score_marker_player->SetInitialPosition(1.7f);
		score_marker_player->SetMarkerOffset(0.34333f);
		score_marker_player->PlaceMarkerAt(6);

		score_marker_ai->start();
		score_marker_ai->_isPositiveOffset = true;
		score_marker_ai->SetInitialPosition(-1.6f);
		score_marker_ai->SetMarkerOffset(0.35333f);
		score_marker_ai->PlaceMarkerAt(4);

		background_soundtrack->start();

		main_menu->start();
	}

	bool update(dxDouble _deltaTime) override
	{				
		football_ball->update(static_cast<float>(_deltaTime));
		YELog("Football Ball Position: X:" + std::to_string(football_ball->_transform->getPosition()->_x) +
			" Y:" + std::to_string(football_ball->_transform->getPosition()->_y) +
			" Z:" + std::to_string(football_ball->_transform->getPosition()->_z));

		/*if (football_ball->_transform->getPosition()->_z < football_keeper_ai->_transform->getPosition()->_z ||
			football_ball->_transform->getPosition()->_z > football_keeper_player->_transform->getPosition()->_z)
			football_score->ResetScores();*/

		football_handle->update(static_cast<float>(_deltaTime));
		football_player->update(static_cast<float>(_deltaTime));
		football_player2->update(static_cast<float>(_deltaTime));

		football_handle_player->update(static_cast<float>(_deltaTime));
		football_player_l->DistanceFromTarget(football_ball);
		football_player_l->update(static_cast<float>(_deltaTime));
		football_player2_l->DistanceFromTarget(football_ball);
		football_player2_l->update(static_cast<float>(_deltaTime));
		football_keeper_ai->update(static_cast<float>(_deltaTime));
		football_keeper_ai->DistanceFromTarget(football_ball);
		football_handle_keeper_ai->update(static_cast<float>(_deltaTime));

		football_keeper_player->update(static_cast<float>(_deltaTime));
		football_handle_keeper->update(static_cast<float>(_deltaTime));

		ai_opponent->WatchBallDirection(football_ball);
		ai_opponent->update(static_cast<float>(_deltaTime));

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
	FTPlayerWhite* football_player_l;
	FTPlayerWhite* football_player2_l;
	FTPlayerWhite* football_keeper_ai;
	FTPlayer* football_keeper_player;
	FTPlayerWhite* football_player_white;
	FTHandlePlayer* football_handle;
	FTHandleWhite* football_handle_player;
	FTSingleHandlePlayer* football_handle_keeper;
	FTSingleHandleWhite* football_handle_keeper_ai;
	FTFieldWalls* football_walls;
	FTScore* football_score;
	FTScoreMarker* score_marker_player;
	FTScoreMarker* score_marker_ai;
	FTGameRoom* game_room;
	FTBackgroundSoundtrack* background_soundtrack;
	FTGameMainMenu* main_menu;

	AIPlayerOpponent* ai_opponent;

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