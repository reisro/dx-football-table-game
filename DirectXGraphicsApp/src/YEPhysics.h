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
	virtual void CreateDynamicSphere(YEVector3* pos, yeFloat radius);
	virtual void CreateCustomRigidBody();
	virtual void CreateJoint(int numberOfAttached);

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