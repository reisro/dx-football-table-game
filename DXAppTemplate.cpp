
#include "GameEntry.h"

using namespace gamentry;

class Cube: public DXGame
{
public:
	Cube() : DXGame("Default Cube") 
	{
	}

	Cube(const char* _game_name) :
		DXGame(_game_name)
	{
	}

	void init() override
	{
		DXLog("Initialized Cube Game...");
	}

	bool update(float _deltaTime) override
	{
		//while(true)
			DXLog("Game Loop...");

		return true;
	}

	virtual void shutdown() override
	{
		DXLog("Shutdown Cube Game...");
	}

private:
	const char* game_name;
};

WINDOW_MAIN_ENTRY(Cube);