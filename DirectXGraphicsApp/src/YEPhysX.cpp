#include "YEPhysX.h"
#include "samples/PulleyJoint.h"
#include <dinput.h>

YEPhysX* YEPhysX::_instance = nullptr;
PxFoundation* YEPhysX::_foundation = nullptr;
PxDefaultAllocator YEPhysX::_allocator;
PxDefaultErrorCallback YEPhysX::_errorCallback;
PxDefaultCpuDispatcher* YEPhysX::_dispatcher = nullptr;
PxPhysics* YEPhysX::_physics = nullptr;
PxScene* YEPhysX::_scene = nullptr;
PxMaterial* YEPhysX::_material = nullptr;
PxPvd* YEPhysX::_pvd = nullptr;
PxPvdTransport* YEPhysX::_transport = nullptr;

#define PVD_HOST "127.0.0.1"

YEPhysX::YEPhysX()
{
	YELog("\nCreated Physics instance....");

	actorGlobalPoses = std::vector<XMMATRIX>();
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());

	_input = YEInput::GetInstance();
}

YEPhysX::~YEPhysX()
{
	_scene->release();
	_physics->release();
	_dispatcher->release();
	_pvd->release();
	_transport->release();
	_foundation->release();
}

void YEPhysX::CreateDefaultPlane()
{
	PxRigidStatic* groundPlane = PxCreatePlane(*_physics, PxPlane(0, 1, 0, 0), *_material);
	_scene->addActor(*groundPlane);
}

void YEPhysX::CreateDynamicSphere(YEVector3* pos, yeFloat radius)
{
	PxSphereGeometry sphereGeometry(radius);

	PxVec3 position = PxVec3(pos->_x, pos->_y, pos->_z);
	
	_dynamicSphere = PxCreateDynamic(*_physics, PxTransform(position), sphereGeometry, *_material, 1.0f);

	_dynamicSphere->setAngularDamping(0.5f);
	_dynamicSphere->setLinearVelocity(PxVec3(0.0f, -1.0f, 0.0f));

	_scene->addActor(*_dynamicSphere);
}

void YEPhysX::CreateCustomRigidBody()
{
}

void YEPhysX::CreateJoint(const YEVector3& pos, int numberOfAttached)
{
	PxBoxGeometry boxGeom(1.0f, 6.0f, 1.0f);

	for (size_t i = 0; i < numberOfAttached; i++)
		attachedBodies.push_back(PxCreateDynamic(*_physics, PxTransform(PxVec3(0, 7, 0)), boxGeom, *_material, 1.0f));

	_joint = new PulleyJoint(*_physics, *attachedBodies[0], PxTransform(PxVec3(pos._x,pos._y, pos._z)), PxVec3(5.0f, 10.0f, 0.0f),
		*attachedBodies[1], PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxVec3(0.0f, 10.0f, 0.0f));

	_joint->mBody[0]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	_joint->mBody[1]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

	_scene->addActor(*attachedBodies[0]);
	_scene->addActor(*attachedBodies[1]);
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

	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	_pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	PxSceneDesc sceneDesc(_physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = _dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	_scene = _physics->createScene(sceneDesc);
	_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_DYNAMIC, 1.0f);

	PxPvdSceneClient* pvdClient = _scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	_material = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	return true;
}

void YEPhysX::PostInit()
{
}

void YEPhysX::Clean()
{
}

void YEPhysX::Simulate(dxDouble deltaTime)
{
	_scene->simulate(1.0f/60.0f);
	_scene->fetchResults(true);

	RenderCallback();

	_input->poll();

	if(_input->keyDown(DIK_D))
	{
		_dynamicSphere->addForce(PxVec3(0.0f, 0.0f, 0.0002f), PxForceMode::eIMPULSE);
	}

	if (_input->keyDown(DIK_A))
	{
		_dynamicSphere->addForce(PxVec3(0.0002f, 0.0f, 0.0f), PxForceMode::eIMPULSE);
	}

	if (_input->keyDown(DIK_W))
	{
		_dynamicSphere->addForce(PxVec3(0.0f, 2.0f, 0.0f), PxForceMode::eIMPULSE);
	}

	_joint->mLocalPose[0] = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxLerp(0.0, rot, rotInc), PxVec3(1, 0, 0)));
	attachedBodies[0]->setKinematicTarget(PxTransform(PxVec3(rightDir + 15, attachedBodies[0]->getGlobalPose().p.y, 0), PxQuat(PxLerp(0.0, rot, rotInc), PxVec3(1, 0, 0))));
	attachedBodies[1]->setKinematicTarget(PxTransform(PxVec3(rightDir, attachedBodies[1]->getGlobalPose().p.y, 0), PxQuat(PxLerp(0.0, rot, rotInc), PxVec3(1, 0, 0))));
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

			if (geom.getType() == PxGeometryType::eSPHERE)
			{
				//std::cout << shapePose.column3.x << " " << shapePose.column3.y << " " << shapePose.column3.z << " " << shapePose.column0.w << std::endl;
			}

			XMFLOAT4X4 world;
			world._11 = shapePose.column0.x; world._12 = shapePose.column0.y; world._13 = shapePose.column0.z; world._14 = shapePose.column0.w;
			world._21 = shapePose.column1.x; world._22 = shapePose.column1.y; world._23 = shapePose.column1.z; world._24 = shapePose.column1.w;
			world._31 = shapePose.column2.x; world._32 = shapePose.column2.y; world._33 = shapePose.column2.z; world._34 = shapePose.column2.w;
			world._41 = shapePose.column3.x; world._42 = shapePose.column3.y; world._43 = shapePose.column3.z; world._44 = shapePose.column3.w;

			XMMATRIX mWorld = XMLoadFloat4x4(&world);

			if (geom.getType() == PxGeometryType::eSPHERE)
				//std::cout << shapePose.column3.x << " " << shapePose.column3.y << " " << shapePose.column3.z << " " << shapePose.column0.w << std::endl;

				if (geom.getType() == PxGeometryType::ePLANE)
					std::cout << shapePose.column3.x << " " << shapePose.column3.y << " " << shapePose.column3.z << " " << shapePose.column0.w << std::endl;

			actorGlobalPoses[i] = mWorld;
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
