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
#include <FTGameRoom.h>
#include <FTReferee.h>
#include <FTBackgroundSoundtrack.h>
#include <FTGameMainMenu.h>
#include <FTPlayerInstructions.h>

using namespace gamentry;

class FootballTableGame: public YEGame
{
public:
	FootballTableGame() : YEGame("Football Table")
	{
	}

	FootballTableGame(const char* _game_name) :
		YEGame(_game_name)
	{
	}

	void init() override
	{
		SetGameStatus(GameStatus::MainMenu);

		// Game Objects creation
		football_field = new FTField(GetGameContext());
		football_field->hasRigidBody = true;

		// Game Main Menu Sprite Game Object
		main_menu = new FTGameMainMenu(GetGameContext());

		game_instructions = new FTPlayerInstructions(GetGameContext());

		football_walls = new FTFieldWalls(GetGameContext());

		football_ball = new FTBall(GetGameContext());
		football_ball->hasRigidBody = true;
		
		football_player = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player.fbx");
		football_player->hasParent = true;
		football_player->hasRigidBody = true;

		football_player2 = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player.fbx");
		football_player2->hasParent = true;
		football_player2->hasRigidBody = true;

		football_player_l = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx", football_ball);
		football_player_l->hasParent = true;
		football_player_l->hasRigidBody = true;

		football_player2_l = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_white.fbx", football_ball);
		football_player2_l->hasParent = true;
		football_player2_l->hasRigidBody = true;

		football_keeper_ai = new FTPlayerWhite(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_white.fbx", football_ball);
		football_keeper_ai->hasRigidBody = true;

		football_keeper_player = new FTPlayer(GetGameContext(), L"C:\\Game Assets\\football_player_keeper_red.fbx");
		football_keeper_player->hasRigidBody = true;

		// handle Player
		football_handle = new FTHandlePlayer(GetGameContext(), football_player, football_player2, L"C:\\Game Assets\\football_handle.fbx");

		// handle AI
		football_handle_player = new FTHandleWhite(GetGameContext(), football_player_l, football_player2_l, L"C:\\Game Assets\\football_handle.fbx");
		
		football_handle_keeper_ai = new FTSingleHandleWhite(GetGameContext(), football_keeper_ai, L"C:\\Game Assets\\football_handle.fbx");

		football_handle_keeper = new FTSingleHandlePlayer(GetGameContext(), football_keeper_player, L"C:\\Game Assets\\football_handle.fbx");

		ai_opponent = new AIPlayerOpponent(GetGameContext(), football_handle_player, football_handle_keeper_ai, football_ball);

		referee = new FTReferee(GetGameContext());

		// Game Audio Soundtrack
		background_soundtrack = new FTBackgroundSoundtrack(GetGameContext(), "C:\\Game Assets\\footballtable_st.wav");

		// Start Game Objects
		football_field->start();
		football_field->_transform->setPosition(new YEVector3(0.0f, 0.0f, 0.0f));

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

		referee->start();

		background_soundtrack->start();

		main_menu->start();
		game_instructions->start();

		football_walls->start();

		BindEventFunctions();
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

		football_keeper_ai->update(static_cast<float>(_deltaTime));
		football_handle_keeper_ai->update(static_cast<float>(_deltaTime));

		football_keeper_player->update(static_cast<float>(_deltaTime));
		football_handle_keeper->update(static_cast<float>(_deltaTime));

		ai_opponent->update(static_cast<float>(_deltaTime));

		main_menu->update(static_cast<float>(_deltaTime));
		game_instructions->update(static_cast<float>(_deltaTime));

		football_walls->update(static_cast<float>(_deltaTime));

		return true;
	}

	virtual void shutdown() override
	{
		YELog("Shutdown Cube Game...");
	}

	void BindEventFunctions()
	{
		main_menu->OnMainMenuKeyPressed = std::bind(&FTPlayerInstructions::SetGameMenuText, game_instructions);
		game_instructions->OnPKeyPressed = std::bind(&FTReferee::BoolWhistle, referee);
		football_walls->OnCloseGoalWidget = std::bind(&FTReferee::BoolWhistle, referee);
	}

	void SetGameStatus(GameStatus status)
	{
		GetGameContext().gameState.SetGameStatus(status);
	}

	static FootballTableGame* GetInstance()
	{
		static FootballTableGame instance;

		return &instance;
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
	FTGameRoom* game_room;
	FTReferee* referee;
	FTBackgroundSoundtrack* background_soundtrack;
	FTGameMainMenu* main_menu;
	FTPlayerInstructions* game_instructions;

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

WINDOW_MAIN_ENTRY(FootballTableGame);