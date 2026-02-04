#include "YEAudio.h"
#include "YEAudio.h"

YEAudio::YEAudio():
	_mSystem(nullptr)
{
}

YEAudio::~YEAudio()
{
	Shutdown();
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

void YEAudio::Update()
{
	if (_mSystem)
	{
		_mSystem->update();
	}
}

void YEAudio::Shutdown()
{
	if (_mSystem) 
	{
		_mSystem->release();
		_mSystem = nullptr;
	}
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

bool YEAudio::LoadLoopSound(const char* soundName, const char* filename)
{
	FMOD_RESULT result;
	FMOD::Sound* sound = nullptr;

	// Create sound with default mode
	// FMOD_DEFAULT = FMOD_LOOP_OFF | FMOD_2D | FMOD_CREATESAMPLE
	result = _mSystem->createSound(filename, FMOD_LOOP_NORMAL, nullptr, &sound);

	if (!CheckError(result, "createSound"))
		return false;

	// Store sound in map for later retrieval
	_loadedSounds[soundName] = sound;

	YELog("YEAudio: " + std::string(soundName));

	return true;
}

bool YEAudio::LoadOneShotSound(const char* soundName, const char* filename)
{
	FMOD_RESULT result;
	FMOD::Sound* sound = nullptr;

	// Create sound with default mode
	// FMOD_DEFAULT = FMOD_LOOP_OFF | FMOD_2D | FMOD_CREATESAMPLE
	result = _mSystem->createSound(filename, FMOD_LOOP_OFF, nullptr, &sound);

	if (!CheckError(result, "createSound"))
		return false;

	// Store sound in map for later retrieval
	_loadedSounds[soundName] = sound;

	YELog("YEAudio: " + std::string(soundName));

	return true;
}

void YEAudio::UnloadSound(const char* filename)
{
	auto it = _loadedSounds.find(filename);

	if (it != _loadedSounds.end())
	{
		it->second->release();

		_loadedSounds.erase(it);
	}
}

void YEAudio::SetVolume(const char* soundName, float volume)
{
}

FMOD::Channel* YEAudio::PlaySound(const char* soundName, bool paused, float volume, int prority)
{
	auto it = _loadedSounds.find(soundName);
	
	if (it == _loadedSounds.end())
	{
		YELog("Sound not found: " + std::string(soundName));

		return nullptr;
	}

	FMOD::Channel* channel = nullptr;
	
	FMOD_RESULT result;

	// Play Sound
	// Parameters: sound, channelGroup, paused, channel
	result = _mSystem->playSound(it->second,
		nullptr,
		paused,
		&channel);

	if (!CheckError(result, "playSound"))
		return nullptr;

	// Set volume
	result = channel->setVolume(volume);

	if (!CheckError(result, "setVolume"))
		return nullptr;

	// Set priority
	result = channel->setPriority(prority);

	if (!CheckError(result, "setPriority"))
		return nullptr;

	return channel;
}
