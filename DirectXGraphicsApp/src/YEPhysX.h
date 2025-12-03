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

using namespace DirectX;

using namespace physx;

class DX_API YEPhysX : public YEPhysics
{
public:
	YEPhysX();
	virtual ~YEPhysX();

	// Static Creation Functions
	void CreateDefaultPlane() override;

	void CreateDynamicSphere(YEVector3* pos, yeFloat radius) override;

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

	PxRigidDynamic*					_dynamicSphere;
	YEInput*						_input;

	std::vector<XMMATRIX> actorGlobalPoses;
};

#endif _YE_PHYSX_H