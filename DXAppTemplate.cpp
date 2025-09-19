
#include "GameEntry.h"

using namespace gamentry;

class Cube: public YEGame
{
public:
	Cube() : YEGame("Default Cube")
	{
		cube_game_object.setName("Cube Object");
	}

	Cube(const char* _game_name) :
		YEGame(_game_name)
	{
	}

	void init() override
	{
		DXLog("Initialized Cube Game...");

		cube_game_object.start();
	}

	bool update(float _deltaTime) override
	{
		DXLog("Game Loop...");

		cube_game_object.update(_deltaTime);

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
};

WINDOW_MAIN_ENTRY(Cube);