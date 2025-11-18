#include "YEPhysics.h"
#include "YEPhysX.h"

YEPhysics* YEPhysics::_instance = nullptr;

YEPhysics::YEPhysics()
{
}

YEPhysics::~YEPhysics()
{
}

void YEPhysics::CreateInstance()
{
	if(YEngineConfig::YEConfig::instance.physicsAPI == YEngineConfig::PhysicsAPI::PhysX)
		_instance = new YEPhysX();
}

void YEPhysics::Setup()
{
}

bool YEPhysics::Init()
{
	return false;
}

void YEPhysics::PostInit()
{
}

void YEPhysics::Clean()
{
}
