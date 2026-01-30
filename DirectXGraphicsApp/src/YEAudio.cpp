#include "YEAudio.h"

YEAudio::YEAudio():
	_mSystem(nullptr)
{
}

YEAudio::~YEAudio()
{
}

bool YEAudio::initialize()
{
	FMOD_RESULT result;
	
	// Create FMOD system object
	result = FMOD::System_Create(&_mSystem);

	if (!CheckError(result, "System_Create"))
		return false;

	// Verify FMOD version
	unsigned int version;
	result = _mSystem->getVersion(&version);

	if (!CheckError(result, "getVersion"))
		return false;

	if (version < FMOD_VERSION)
	{
		YELog("FMOD lib version doesn't match header version" + FMOD_VERSION);

		return false;
	}

	// Get number of sound cards
	int numDrivers;
	result = _mSystem->getNumDrivers(&numDrivers);

	if (!CheckError(result, "getNumDrivers"))
		return false;

	if (numDrivers == 0)
	{
		result = _mSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		
		if (!CheckError(result, "setOutput"))
			return false;
	}

	// Initalize FMOD System
	// Parameters: maxChannels, initFlags, extraDriverData
	result = _mSystem->init(512, FMOD_INIT_NORMAL, nullptr);
	
	if (!CheckError(result, "init"))
		return false;
	
	YELog("YEAudio: FMOD initializaed successfully...");

	return true;
}

bool YEAudio::CheckError(FMOD_RESULT result, const char* context)
{
	if (result != FMOD_OK)
	{
		YELog("YEAudio: FMOD error... ");

		return false;
	}

	return true;
}
