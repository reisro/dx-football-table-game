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

void YEPhysics::CreateStaticBox(YEVector3* pos, YEVector3* size)
{
}

void YEPhysics::CreateDynamicSphere(YEVector3* pos, yeFloat radius)
{
}

void YEPhysics::CreateCustomRigidBody()
{
}

void YEPhysics::CreateJoint(const YEVector3& pos, const YEVector3& pos1, int numberOfAttached, bool inputPlayer)
{
}

void YEPhysics::RotateJointBody()
{
}

bool YEPhysics::MoveJointBody(int dir, yeFloat left, yeFloat right)
{
	return true;
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

void YEPhysics::Simulate(dxDouble deltaTime)
{
}

void YEPhysics::RenderCallback()
{
}
