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

void YEPhysics::CreateStaticBox(const char* name, YEVector3* pos, YEVector3* size)
{
}

void YEPhysics::CreateDynamicSphere(const char* name, YEVector3* pos, yeFloat radius)
{
}

void YEPhysics::CreateCustomRigidBody()
{
}

void YEPhysics::AddForceToDynamicRigidBody(const YEVector3& force)
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

void YEPhysics::MoveJointBodyToPosition(int dir)
{
}

void YEPhysics::MoveKinematicPulleyJointBody(int id, int dir, yeFloat left, yeFloat right)
{
}

void YEPhysics::RotatePulleyJointBody(int id, yeFloat rot, yeFloat rotInc, yeFloat limitRot, yeFloat limitRotInc, yeFloat restart)
{
}

void YEPhysics::ResetRotatePulleyJointBody(int id)
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

void YEPhysics::Simulate(dxDouble deltaTime)
{
}

void YEPhysics::RenderCallback()
{
}
