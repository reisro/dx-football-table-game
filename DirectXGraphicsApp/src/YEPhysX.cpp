#include "YEPhysX.h"

YEPhysX* YEPhysX::_instance = nullptr;
PxFoundation* YEPhysX::_foundation = nullptr;
PxDefaultAllocator YEPhysX::_allocator;
PxDefaultErrorCallback YEPhysX::_errorCallback;
PxDefaultCpuDispatcher* YEPhysX::_dispatcher = nullptr;
PxPhysics* YEPhysX::_physics = nullptr;
PxScene* YEPhysX::_scene = nullptr;
PxMaterial* YEPhysX::_material = nullptr;
PxPvd* YEPhysX::_pvd = nullptr;

YEPhysX::YEPhysX()
{
	YELog("\nCreated Physics instance....");
}

YEPhysX::~YEPhysX()
{
}

void YEPhysX::CreateDefaultPlane()
{
	PxSceneDesc sceneDesc(_physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = _dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	_scene = _physics->createScene(sceneDesc);

	_material = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*_physics, PxPlane(0, 1, 0, 0), *_material);
	_scene->addActor(*groundPlane);
}

void YEPhysX::CreateDynamicSphere()
{
	PxReal sphereStartingHeight = 5.0f;

	PxSphereGeometry sphereGeometry(1.0f);
	
	PxRigidDynamic* dynamic = PxCreateDynamic(*_physics, PxTransform(PxVec3(0.0f, sphereStartingHeight, 0.0f)), sphereGeometry, *_material, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(PxVec3(0.0f, -1.0f, 0.0f));

	_scene->addActor(*dynamic);
}

void YEPhysX::Setup()
{
}

bool YEPhysX::Init()
{
	_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, _allocator, _errorCallback);
	
	_pvd = PxCreatePvd(*_foundation);
	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, PxTolerancesScale(), true, _pvd);
	_dispatcher = PxDefaultCpuDispatcherCreate(2);

	return true;
}

void YEPhysX::PostInit()
{
}

void YEPhysX::Clean()
{
}

void YEPhysX::RenderCallback()
{
	_scene->simulate(1.0f / 60.0f);
	_scene->fetchResults(true);
}
