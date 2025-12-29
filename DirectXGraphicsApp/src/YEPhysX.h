#pragma once

#ifndef _YE_PHYSX_H
#define _YE_PHYSX_H

#include "YEPhysics.h"
#include "PxPhysicsAPI.h"
#include "DXTypes.h"
#include "YEVector3.h"
#include "DirectXMath.h"
#include "YEInput.h"
#include <vector>
#include <map>

class PulleyJoint;

using namespace DirectX;

using namespace physx;

struct PulleyJointBodyInfo
{
	PulleyJointBodyInfo(PxRigidDynamic* b, float o, bool input) : box(b), offset(o), receivesInput(input) {}

	PxRigidDynamic* box;
	float offset;
	bool receivesInput;
};

class DX_API YEPhysX : public YEPhysics
{
public:
	YEPhysX();
	virtual ~YEPhysX();

	// Static Creation Functions
	void CreateDefaultPlane() override;

	void CreateStaticBox(YEVector3* pos, YEVector3* size) override;

	void CreateDynamicSphere(YEVector3* pos, yeFloat radius) override;

	void CreateCustomRigidBody() override;

	void CreateJoint(const YEVector3& pos, const YEVector3& pos1, int numberOfAttached, bool inputPlayer) override;

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() override;

	// Required operations to start for this subsystem
	virtual bool Init() override;

	// Operations needed after initialization
	virtual void PostInit() override;

	// Clean resources before shutting down
	virtual void Clean() override;

	// Physics simulation step
	virtual void Simulate(dxDouble deltaTime) override;

	// Render physics actors
	void Render(PxRigidActor** actors, const PxU32 numActors);

	// Render callback for physics debug rendering
	virtual void RenderCallback() override;

	void SetKinematicPulleyJointBody(int id);

	virtual XMMATRIX GetGlobalPose(UINT actorID);

	static YEPhysX*					_instance;
	static PxFoundation*			_foundation;
	static PxDefaultAllocator		_allocator;
	static PxDefaultErrorCallback	_errorCallback;
	static PxDefaultCpuDispatcher*  _dispatcher;
	static PxPhysics*				_physics;
	static PxScene*					_scene;
	static PxMaterial*				_material;
	static PxPvd*					_pvd;
	static PxPvdTransport*			_transport;
	
	float rot = 3.0f;
	float rotInc = 0.0f;
	float rightDir = 1.0f;
	float leftDir = 1.0f;

	int pulleyJoints = 0;
	int pulleyJointID = 0;
	int attachedBodiesCount = -1;
	int attachedBodiesID = 0;
	int attachedBodiesKinematicID = 0;

	PxRigidDynamic*					_dynamicSphere;
	YEInput*						_input;

	std::vector<XMMATRIX>			 actorGlobalPoses;
	std::vector<PxRigidDynamic*>	 attachedBodies;
	std::vector <PulleyJoint*>		 pulleyJointsList;
	std::vector<PulleyJointBodyInfo> pulleyJointAttachedBodiesMap;
	std::vector<PxRigidDynamic*>	 pulleyJointAttachedBodies;
};

#endif _YE_PHYSX_H