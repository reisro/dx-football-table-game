#pragma once

#ifndef _YE_PHYSX_H
#define _YE_PHYSX_H

#include "YEPhysics.h"
#include "PxPhysicsAPI.h"

using namespace physx;

class DX_API YEPhysX : public YEPhysics
{
public:
	YEPhysX();
	virtual ~YEPhysX();

	static void CreateInstance();

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() override;

	// Required operations to start for this subsystem
	virtual bool Init() override;

	// Operations needed after initialization
	virtual void PostInit() override;

	// Clean resources before shutting down
	virtual void Clean() override;

	static YEPhysX*					_instance;

	static PxFoundation*			_foundation;
	static PxDefaultAllocator		_allocator;
	static PxDefaultErrorCallback	_errorCallback;
	static PxDefaultCpuDispatcher*  _dispatcher;
	static PxPhysics*				_physics;
	static PxScene*					_scene;
	static PxMaterial*				_material;
	static PxPvd*					_pvd;
};

#endif _YE_PHYSX_H