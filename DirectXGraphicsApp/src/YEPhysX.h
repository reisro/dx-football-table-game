#pragma once

#ifndef _YE_PHYSX_H
#define _YE_PHYSX_H

#include "YEPhysics.h"
#include "PxPhysicsAPI.h"
#include "DXTypes.h"
#include "YEVector3.h"
#include "DirectXMath.h"
#include "YEInput.h"
#include "YEObserver.h"
#include <vector>
#include <map>

class PulleyJoint;

using namespace DirectX;

using namespace physx;

struct PulleyJointBodyInfo
{
	PulleyJointBodyInfo(PxRigidDynamic* b, float o, float md,  bool input) : box(b), offset(o), rightMoveDir(md), receivesInput(input) {}

	PxRigidDynamic* box;
	float offset;
	float rightMoveDir;
	float cpuRot=0.0f;
	float cpuRotInc=0.0f;
	bool receivesInput;
};

enum CollisionGroups
{
	LAYER_DEFAULT = 1 << 0,
	LAYER_IGNORE = 1 << 2
};

class DX_API YEPhysX : public YEPhysics, YEPhysicsColliderTransmitter
{
public:
	YEPhysX();
	virtual ~YEPhysX();

	// Static Creation Functions
	void CreateDefaultPlane() override;

	void CreateStaticBox(const char* name, YEVector3* pos, YEVector3* size) override;

	void CreateDynamicSphere(const char* name, YEVector3* pos, yeFloat radius) override;

	void CreateCustomRigidBody() override;

	void AddForceToDynamicRigidBody(const YEVector3& force) override;

	void CreateJoint(const YEVector3& pos, const YEVector3& pos1, int numberOfAttached, bool inputPlayer) override;

	void RotateJointBody() override;

	bool MoveJointBody(int dir, yeFloat left, yeFloat right) override;

	void MoveJointBodyToPosition(int dir) override;

	void MoveKinematicPulleyJointBody(int id, int dir, yeFloat left, yeFloat right) override;

	void RotatePulleyJointBody(int id, yeFloat rot, yeFloat rotInc, yeFloat limitRot, yeFloat limitRotInc, yeFloat restart) override;

	void ResetRotatePulleyJointBody(int id) override;

	void ResetMovePulleyJointBody(int id) override;

	void ResetDynamicSphere();

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

	void Attach(YEPhysicsColliderListener* observer) override;

	void NotifyCollision(const char* actorName) override;

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

	PxRaycastBuffer hit;
	
	float rightDir = 0.0f;
	float leftDir = 1.0f;
	float cpuRightDir = 0.0f;
	float cpuRot = 0.0f;
	float cpuRotInc = 0.0f;
	bool once = false;

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

	std::list<YEPhysicsColliderListener*> _collision_listeners;
};

#endif _YE_PHYSX_H