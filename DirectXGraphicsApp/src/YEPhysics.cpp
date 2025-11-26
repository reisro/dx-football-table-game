#include "YEPhysics.h"
#include "DXConfig.h"
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

void YEPhysics::CreateDefaultPlane()
{
}

void YEPhysics::CreateDynamicSphere(YEVector3* pos, yeFloat radius)
{
}

YEPhysics* YEPhysics::GetInstance()
{
	return _instance;
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

void YEPhysics::Simulate()
{
}

void YEPhysics::RenderCallback()
{
}
