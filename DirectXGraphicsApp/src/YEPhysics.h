#pragma once

//-----------------------------------------------------------------------------
// Base Header Includes
//-----------------------------------------------------------------------------
#include "DXAPI.h"
#include "DXTypes.h"
#include "YEVector3.h"
#include "DXSubsystem.h"

// Renderer subsystem for DirectX
class DX_API YEPhysics : public DXSubsystem
{
public:
	YEPhysics();
	virtual ~YEPhysics();

	static void CreateInstance();
	virtual void CreateDefaultPlane();
	virtual void CreateStaticBox(const char* name, YEVector3* pos, YEVector3* size);
	virtual void CreateDynamicSphere(const char* name, YEVector3* pos, yeFloat radius);
	virtual void CreateCustomRigidBody();
	virtual void AddForceToDynamicRigidBody(const YEVector3& force);
	virtual void CreateJoint(const YEVector3& pos, const YEVector3& pos1, int numberOfAttached, bool inputPlayer);
	virtual void RotateJointBody();
	virtual bool MoveJointBody(int dir, yeFloat left, yeFloat right);
	virtual void MoveJointBodyToPosition(int dir);
	virtual void MoveKinematicPulleyJointBody(int id, int dir, yeFloat left, yeFloat right);
	virtual void RotatePulleyJointBody(int id, yeFloat rot, yeFloat rotInc, yeFloat limitRot, yeFloat limitRotInc, yeFloat restart);
	virtual void ResetRotatePulleyJointBody(int id);

	static YEPhysics* GetInstance();

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() override;

	// Required operations to start for this subsystem
	virtual bool Init() override;

	// Operations needed after initialization
	virtual void PostInit() override;

	// Clean resources before shutting down
	virtual void Clean() override;

	// Physics simulation step
	virtual void Simulate(dxDouble deltaTime);

	// Render callback for physics debug rendering
	virtual void RenderCallback();

	static YEPhysics* _instance;
};