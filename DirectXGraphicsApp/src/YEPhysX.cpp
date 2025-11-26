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

	actorGlobalPoses = std::vector<XMMATRIX>();
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
	_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_STATIC, 1.0f);

	_material = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*_physics, PxPlane(0, 1, 0, 0), *_material);
	groundPlane->setGlobalPose(PxTransform(PxVec3(0.0f, -1.0f, 0.0f)));
	_scene->addActor(*groundPlane);
}

void YEPhysX::CreateDynamicSphere(const YEVector3& pos, yeFloat radius)
{
	PxSphereGeometry sphereGeometry(radius);

	PxVec3 position = PxVec3(pos._x, pos._y, pos._z);
	
	PxRigidDynamic* dynamic = PxCreateDynamic(*_physics, PxTransform(position), sphereGeometry, *_material, 10.0f);

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

	CreateDefaultPlane();

	return true;
}

void YEPhysX::PostInit()
{
}

void YEPhysX::Clean()
{
}

void YEPhysX::Simulate()
{
	_scene->simulate(1.0f / 60.0f);
	_scene->fetchResults(true);

	RenderCallback();
}

void YEPhysX::Render(PxRigidActor** actors, const PxU32 numActors)
{
	PxShape* shapes[2];

	for (PxU32 i = 0; i < numActors; i++)
	{
		PxU32 nbShapes = actors[i]->getNbShapes();
		actors[i]->getShapes(shapes, nbShapes);

		for (PxU32 j = 0; j < nbShapes; j++)
		{
			const PxMat44 shapePose(PxShapeExt::getGlobalPose(*shapes[j], *actors[i]));
			const PxGeometry& geom = shapes[j]->getGeometry();

			XMFLOAT4X4 world;
			world._11 = shapePose.column0.x; world._12 = shapePose.column0.y; world._13 = shapePose.column0.z; world._14 = shapePose.column0.w;
			world._21 = shapePose.column1.x; world._22 = shapePose.column1.y; world._23 = shapePose.column1.z; world._24 = shapePose.column1.w;
			world._31 = shapePose.column2.x; world._32 = shapePose.column2.y; world._33 = shapePose.column2.z; world._34 = shapePose.column2.w;
			world._41 = shapePose.column3.x; world._42 = shapePose.column3.y; world._43 = shapePose.column3.z; world._44 = shapePose.column3.w;

			XMMATRIX mWorld = XMLoadFloat4x4(&world);

			actorGlobalPoses.push_back(mWorld);
		}
	}
}

void YEPhysX::RenderCallback()
{
	PxScene* scene;
	PxGetPhysics().getScenes(&scene, 1);

	PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	if(nbActors)
	{
		PxArray<PxRigidActor*> actors(nbActors);
		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
		for (PxU32 i = 0; i < nbActors; i++)
		{
			PxArray<PxRigidActor*> rigidActors(nbActors);
			
			Render(&actors[0], static_cast<PxU32>(actors.size()));
		}
	}
}

XMMATRIX YEPhysX::GetGlobalPose(UINT actorID)
{
	return actorGlobalPoses[actorID];
}
