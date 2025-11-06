
#include "GameEntry.h"

using namespace gamentry;

class Cube: public YEGame
{
public:
	Cube() : YEGame("Default Cube")
	{
		cube_game_object.setName("Cube Object");
		football_table_ball_object.setName("Football ball");
	}

	Cube(const char* _game_name) :
		YEGame(_game_name)
	{
	}

	void init() override
	{
		cube_game_object.start();
		football_table_ball_object.start();

		YE::YEApplication::Import3DModel();
		
		// Set initial position of the cube
		position = YEVector3::Zero();

		//cube_game_object.GetTransform()->setPosition(position);

        LPCWSTR ball_model_path = L"C:\\Game Assets\\football_ball.fbx";

		football_table_ball_object._transform->setPosition(new YEVector3(.0f,.0f,-10.0f));
	}

	bool update(dxDouble _deltaTime) override
	{
		newPosition = new YEVector3(0.0f, 0.0f, forward_speed);
		moveDirection = YEVector3::Sum(*position, *newPosition);

		//cube_game_object.GetTransform()->setPosition(moveDirection);
		cube_game_object.update(_deltaTime);

		forward_speed += 0.1f;

		return true;
	}

	virtual void shutdown() override
	{
		DXLog("Shutdown Cube Game...");

		cube_game_object.shutdown();
	}

private:
	const char* game_name;

	YEGameObject cube_game_object;
	YEGameObject football_table_ball_object;

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