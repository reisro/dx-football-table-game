#include "FTFieldWalls.h"
#include <YEPhysX.h>

FTFieldWalls::FTFieldWalls(const YEGameContext& _game_context) :
	YEGameObject("Football Walls", _game_context),
	football_score(new FTScore(_game_context))
{
	// Score markers 3D game objects
	score_marker_player = new FTScoreMarker(_game_context);
	score_marker_ai = new FTScoreMarker(_game_context);
}

FTFieldWalls::~FTFieldWalls()
{
}

void FTFieldWalls::start()
{
	YEPhysics::GetInstance()->CreateStaticBox("Left Wall", new YEVector3(-6.7f, 0.0f, 0.0f), new YEVector3(1.0f, 2.5f, 10.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Left Player Net", new YEVector3(-4.0f, 0.0f, 10.5f), new YEVector3(2.4f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Left Player AI Net", new YEVector3(-4.0f, 0.0f, -10.5f), new YEVector3(2.4f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Right Player Net", new YEVector3(4.0f, 0.0f, 10.5f), new YEVector3(2.4f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Right Player AI Net", new YEVector3(4.0f, 0.0f, -10.5f), new YEVector3(2.4f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Right Wall", new YEVector3(6.7f, 0.0f, 0.0f), new YEVector3(1.0f, 2.5f, 10.0f));

	// nets
	YEPhysics::GetInstance()->CreateStaticBox("Net PlayerAI ", new YEVector3(0.0f, 0.0f, -12.5f), new YEVector3(1.6f, 2.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Net Player", new YEVector3(0.0f, 0.0f, 12.5f), new YEVector3(1.6f, 2.5f, 1.0f));

	score_marker_player->start();
	score_marker_player->_isPositiveOffset = false;
	score_marker_player->SetInitialPosition(1.7f);
	score_marker_player->SetMarkerOffset(0.34333f);
	score_marker_player->PlaceMarkerAt(0);

	score_marker_ai->start();
	score_marker_ai->_isPositiveOffset = true;
	score_marker_ai->SetInitialPosition(-1.6f);
	score_marker_ai->SetMarkerOffset(0.35333f);
	score_marker_ai->PlaceMarkerAt(0);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
	
	phsyX->Attach(this);
}

void FTFieldWalls::shutdown()
{
}

void FTFieldWalls::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}

void FTFieldWalls::OnNotify(const char* name)
{
	static bool once = false;

	if (!once)
	{
		once = true;
		
		if (name == "Net Player")
			YELog("Collision with net player detected!");
		else if (name == "Net PlayerAI")
			YELog("Collision with net player ai detected!");
	}
}
