#include "FTFieldWalls.h"
#include <YEPhysX.h>

FTFieldWalls::FTFieldWalls(const YEGameContext& _game_context) :
	YEGameObject("Football Walls", _game_context),
	football_score(new FTScore(_game_context))
{
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
	YEPhysics::GetInstance()->CreateStaticBox("Net PlayerAI", new YEVector3(0.0f, 0.0f, -12.5f), new YEVector3(1.6f, 1.5f, 1.0f));
	YEPhysics::GetInstance()->CreateStaticBox("Net Player", new YEVector3(0.0f, 0.0f, 12.5f), new YEVector3(1.6f, 1.5f, 1.0f));

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	football_score->start();
	football_score->OnScoreGoal = std::bind(&FTFieldWalls::OnGoalScored, this);
	football_score->OnGoalUIHide = std::bind(&FTFieldWalls::OnScoreGoalUIHide, this);
	
	phsyX->Attach(this);
}

void FTFieldWalls::shutdown()
{
}

void FTFieldWalls::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	football_score->update(_deltaTime);
}

void FTFieldWalls::OnGoalScored()
{
	OnBallReachGoalTrigger();
}

void FTFieldWalls::OnScoreGoalUIHide()
{
	OnCloseGoalWidget();
}

void FTFieldWalls::ActiveScore()
{
	football_score->Register();
}

void FTFieldWalls::OnNotify(const char* name)
{
	action = std::bind(&FTScore::IncrementScore, football_score, name);

	action(name);
}