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

struct CustomRigidBodyActor: PxCustomGeometry::Callbacks
{
	PxVec3 customGeometry;

	PxRigidDynamic* rigidBody;
	yeFloat mass;
	YEVector3* initialPosition;
	YEVector3* initialVelocity;

	virtual PxBounds3 getLocalBounds(const PxGeometry&) const
	{
		return PxBounds3(-PxVec3(customGeometry.x * 0.5f, customGeometry.y * 0.5f, customGeometry.x * 0.5f),
			PxVec3(customGeometry.x * 0.5f, customGeometry.y * 0.5f, customGeometry.x * 0.5f));
	}

	virtual PxBounds3 getLocalBounds(const PxGeometry& geometry) const
	{
		return PxBounds3::empty();
	}

	virtual bool generateContacts(const PxGeometry&, const PxGeometry&, const PxTransform&, const PxTransform&,
		const PxReal, const PxReal, const PxReal,
		PxContactBuffer&) const
	{
		return false;
	}

	virtual PxU32 raycast(const PxVec3& origin, const PxVec3& unitDir, const PxGeometry&, const PxTransform& pose,
		PxReal maxDist, PxHitFlags hitFlags, PxU32, PxGeomRaycastHit* rayHits, PxU32, PxRaycastThreadContext*) const
	{
		PxBoxGeometry barGeom(customGeometry * 0.5f);
		PxTransform p0 = pose;
		PxGeomRaycastHit hits[2];
		PxGeometryQuery::raycast(origin, unitDir, barGeom, p0, maxDist, hitFlags, 1, hits + 0);
		p0 = pose.transform(PxTransform(PxQuat(PX_PIDIV2, PxVec3(0, 1, 0))));
		PxGeometryQuery::raycast(origin, unitDir, barGeom, p0, maxDist, hitFlags, 1, hits + 1);
		rayHits[0] = hits[0].distance < hits[1].distance ? hits[0] : hits[1];
		return hits[0].distance < PX_MAX_REAL || hits[1].distance < PX_MAX_REAL ? 1 : 0;
	}

	virtual bool overlap(const PxGeometry&, const PxTransform& pose0, const PxGeometry& geom1, const PxTransform& pose1, PxOverlapThreadContext*) const
	{
		PxBoxGeometry barGeom(customGeometry * 0.5f);
		PxTransform p0 = pose0;
		if (PxGeometryQuery::overlap(barGeom, p0, geom1, pose1, PxGeometryQueryFlags(0)))
			return true;
		p0 = pose0.transform(PxTransform(PxQuat(PX_PIDIV2, PxVec3(0, 1, 0))));
		if (PxGeometryQuery::overlap(barGeom, p0, geom1, pose1, PxGeometryQueryFlags(0)))
			return true;
		return false;
	}

	virtual bool sweep(const PxVec3& unitDir, const PxReal maxDist,
		const PxGeometry&, const PxTransform& pose0, const PxGeometry& geom1, const PxTransform& pose1,
		PxGeomSweepHit& sweepHit, PxHitFlags hitFlags, const PxReal inflation, PxSweepThreadContext*) const
	{
		PxBoxGeometry barGeom(customGeometry * 0.5f);
		PxTransform p0 = pose0;
		PxGeomSweepHit hits[2];
		PxGeometryQuery::sweep(unitDir, maxDist, geom1, pose1, barGeom, p0, hits[0], hitFlags, inflation);
		p0 = pose0.transform(PxTransform(PxQuat(PX_PIDIV2, PxVec3(0, 1, 0))));
		PxGeometryQuery::sweep(unitDir, maxDist, geom1, pose1, barGeom, p0, hits[1], hitFlags, inflation);
		sweepHit = hits[0].distance < hits[1].distance ? hits[0] : hits[1];
		return hits[0].distance < PX_MAX_REAL || hits[1].distance < PX_MAX_REAL;
	}

	virtual void visualize(const PxGeometry&, PxRenderOutput&, const PxTransform&, const PxBounds3&) const {}
	virtual void computeMassProperties(const PxGeometry&, PxMassProperties&) const {}
	virtual bool usePersistentContactManifold(const PxGeometry&, PxReal&) const { return false; }
};

class DX_API YEPhysX : public YEPhysics
{
public:
	YEPhysX();
	virtual ~YEPhysX();

	// Static Creation Functions
	void CreateDefaultPlane() override;

	void CreateDynamicSphere(YEVector3* pos, yeFloat radius) override;

	void CreateCustomRigidBody() override;

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