
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
		return true;
	}

	virtual void shutdown() override
	{
		DXLog("Shutdown Cube Game...");
	}

private:
	uint32_t m_width;
	uint32_t m_height;
};

WINDOW_MAIN_ENTRY(Cube);