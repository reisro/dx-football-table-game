#include "GameEntry.h"
#include <FTBall.h>
#include <FTField.h>

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
		football_ball = new FTBall(GetGameContext());
		football_field = new FTField(GetGameContext());

		football_ball->start();
		football_ball->_transform->setPosition(new YEVector3(0.0f, 1.0f, 0.0f));

		football_field->start();
		football_field->_transform->setPosition(new YEVector3(0.0f, 1.0f, 0.0f));

		// Set initial position of the cube
		position = YEVector3::Zero();
	}

	bool update(dxDouble _deltaTime) override
	{
		newPosition = new YEVector3(0.0f, 0.0f, forward_speed);
		moveDirection = YEVector3::Sum(*position, *newPosition);

		//football_ball->update(_deltaTime);

		//cube_game_object.GetTransform()->setPosition(moveDirection);

		forward_speed += 0.1f;

		return true;
	}

	virtual void shutdown() override
	{
		DXLog("Shutdown Cube Game...");
	}

private:
	const char* game_name;

	FTBall* football_ball;
	FTField* football_field;

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