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

PxFilterData CreateFilterData(uint32_t layerMask);

PxFilterData CreateFilterData(uint32_t layerMask)
{
	PxFilterData fd;
	fd.word0 = layerMask;
	fd.word1 = 0,
	fd.word2 = 0;
	fd.word3 = 0;

	return fd;
}

YEPhysX::YEPhysX()
{
	YELog("\nCreated Physics instance....");

	actorGlobalPoses = std::vector<XMMATRIX>();
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());
	actorGlobalPoses.push_back(XMMatrixIdentity());

	pulleyJointsList = std::vector<PulleyJoint*>();

	_input = YEInput::GetInstance();

	_collision_listeners = std::list<YEPhysicsColliderListener*>();
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
	PxRigidStatic* groundPlane = PxCreatePlane(*_physics, PxPlane(0, 1, 0, 0.18), *_material);
	groundPlane->setName("Ground Plane");

	_scene->addActor(*groundPlane);
}

void YEPhysX::CreateStaticBox(const char* name, YEVector3* pos, YEVector3* size)
{
	PxBoxGeometry boxGeometry(size->_x, size->_y, size->_z);

	PxVec3 position = PxVec3(pos->_x, pos->_y, pos->_z);

	PxRigidStatic* staticBox = PxCreateStatic(*_physics, PxTransform(position), boxGeometry, *_material);

	PxShape* shapes[1];
	staticBox->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(CreateFilterData(CollisionGroups::LAYER_DEFAULT));
	staticBox->setName(name);

	_scene->addActor(*staticBox);
}

void YEPhysX::CreateDynamicSphere(const char* name, YEVector3* pos, yeFloat radius)
{
	PxSphereGeometry sphereGeometry(radius);

	PxVec3 position = PxVec3(pos->_x, pos->_y, pos->_z);
	
	_dynamicSphere = PxCreateDynamic(*_physics, PxTransform(position), sphereGeometry, *_material, 3.0f, PxTransform(PxVec3(0.0f,0.03f,0.0f)));
	
	PxShape* shapes[1];
	_dynamicSphere->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(CreateFilterData(CollisionGroups::LAYER_IGNORE));
	_dynamicSphere->setName(name);

	_dynamicSphere->setAngularDamping(0.5f);
	_dynamicSphere->setMass(10.0f);
	_dynamicSphere->setLinearVelocity(PxVec3(0.0f, 0.0f, 1.0f));
	_dynamicSphere->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
	_dynamicSphere->setMaxLinearVelocity(20.0f);

	_scene->addActor(*_dynamicSphere);
}

void YEPhysX::CreateCustomRigidBody()
{
}

void YEPhysX::AddForceToDynamicRigidBody(const YEVector3& force)
{
	_dynamicSphere->addForce(PxVec3(force._x, force._y, force._z), PxForceMode::eIMPULSE);
}

void YEPhysX::CreateJoint(const YEVector3& pos, const YEVector3& pos1, int numberOfAttached, bool inputPlayer)
{
	PxBoxGeometry boxGeom(0.25f,0.9f, 0.15f);
	PxVec3 newPos = PxVec3(pos._x - 1.92f, pos._y, pos._z);

	PxRigidDynamic* bodyA;
	PxRigidDynamic* bodyB;

	switch (numberOfAttached)
	{
	case 1:
		attachedBodies.push_back(PxCreateDynamic(*_physics, PxTransform(PxVec3(pos._x, pos._y, pos._z)), boxGeom, *_material, 1.0f));
		attachedBodiesCount += 1;

		pulleyJointsList.push_back(new PulleyJoint(*_physics, *attachedBodies[attachedBodiesCount], PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), PxVec3(0.0f, 1.0f, 0.0f)));
		
		pulleyJointAttachedBodiesMap.push_back(PulleyJointBodyInfo(attachedBodies[attachedBodiesCount], 0.0f, 0.03f, inputPlayer));

		pulleyJointAttachedBodies.resize(attachedBodiesCount);

		pulleyJointsList[pulleyJointID]->mBodies = 1;
		pulleyJointsList[pulleyJointID]->mBody[0]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

		for (size_t i = attachedBodiesID; i < attachedBodies.size(); i++)
			_scene->addActor(*attachedBodies[i]);

		attachedBodiesID += 1;
		pulleyJointID++; 
			
		break;

	case 2:
		
		bodyA = PxCreateDynamic(*_physics, PxTransform(PxVec3(pos._x, pos._y, pos._z)), boxGeom, *_material, 1.0f);
		bodyA->setName("Pulley Joint Body A");
		bodyB = PxCreateDynamic(*_physics, PxTransform(PxVec3(pos1._x, pos1._y, pos1._z)), boxGeom, *_material, 1.0f);
		bodyB->setName("Pulley Joint Body B");

		attachedBodies.push_back(bodyA);
		attachedBodies.push_back(bodyB);

		attachedBodiesCount += 2;
		
		pulleyJointsList.push_back(new PulleyJoint(*_physics, *attachedBodies[attachedBodiesCount-1], PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), PxVec3(0.0f, 1.0f, 0.0f),
			*attachedBodies[attachedBodiesCount], PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxVec3(0.0f, 1.0f, 0.0f)));

		pulleyJointAttachedBodiesMap.push_back(PulleyJointBodyInfo(attachedBodies[attachedBodiesCount-1], 0.0f, 0.03f, inputPlayer));
		pulleyJointAttachedBodiesMap.push_back(PulleyJointBodyInfo(attachedBodies[attachedBodiesCount], -3.0f, 0.03f, inputPlayer));

		pulleyJointAttachedBodies.resize(attachedBodiesCount);

		pulleyJointsList[pulleyJointID]->mBodies = 2;

		pulleyJointsList[pulleyJointID]->mBody[0]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		pulleyJointsList[pulleyJointID]->mBody[1]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

		for (size_t i = attachedBodiesID; i < attachedBodies.size(); i++)
			_scene->addActor(*attachedBodies[i]);

		attachedBodiesID += 2;
		pulleyJointID++;
		
		break;

	case 3:
		for (size_t i = 0; i < 3; i++)
			attachedBodies.push_back(PxCreateDynamic(*_physics, PxTransform(PxVec3(pos._x, pos._y, pos._z)), boxGeom, *_material, 1.0f, PxTransform(PxVec3(0.0, -0.25, 0.0))));

		for (size_t i = 0; i < attachedBodies.size(); i++)
			_scene->addActor(*attachedBodies[i]);

		break;

	default:
		YELog("\n[ERROR] Unsupported number of attached bodies for joint creation!");
		return;
	}
}

void YEPhysX::RotateJointBody()
{
	cpuRot -= 0.03f; cpuRotInc += 0.45; if (cpuRot > 0.95f) cpuRot = 0.95f; if (cpuRotInc > 26.0f) cpuRotInc = 0.0f;
}

bool YEPhysX::MoveJointBody(int dir, yeFloat left, yeFloat right)
{
	yeFloat limitLeft = left;
	yeFloat limitRight = right;

	if (dir == 1) 
		cpuRightDir += 0.03; 
	if (dir == -1)
		cpuRightDir -= 0.03;

	if (cpuRightDir < limitLeft)
	{
		cpuRightDir = limitLeft;

		return true;
	}
	if (cpuRightDir > limitRight)
	{
		cpuRightDir = limitRight;

		return true;
	}

	return false;
}

void YEPhysX::MoveJointBodyToPosition(int dir)
{
	if (dir == 1)
		cpuRightDir += 0.03;
	if (dir == -1)
		cpuRightDir -= 0.03;

	if (cpuRightDir < -2.4f)
		cpuRightDir = -2.4f;
	if (cpuRightDir > 5.0f)
		cpuRightDir = 5.0f;
}

void YEPhysX::MoveKinematicPulleyJointBody(int id, int dir, yeFloat left, yeFloat right)
{
	yeFloat limitLeft = left;
	yeFloat limitRight = right;

	if (dir == 1)
		pulleyJointAttachedBodiesMap[id].rightMoveDir += .05f;
	if (dir == -1)
		pulleyJointAttachedBodiesMap[id].rightMoveDir -= .05f;

	if (pulleyJointAttachedBodiesMap[id].rightMoveDir < limitLeft)
		pulleyJointAttachedBodiesMap[id].rightMoveDir = limitLeft;
	if (pulleyJointAttachedBodiesMap[id].rightMoveDir > limitRight)
		pulleyJointAttachedBodiesMap[id].rightMoveDir = limitRight;
}

void YEPhysX::RotatePulleyJointBody(int id, yeFloat rot, yeFloat rotInc, yeFloat limitRot, yeFloat limitRotInc, yeFloat restart)
{
	pulleyJointAttachedBodiesMap[id].cpuRot += rot; 
	pulleyJointAttachedBodiesMap[id].cpuRotInc += rotInc;

	if (pulleyJointAttachedBodiesMap[id].cpuRot > limitRot) 
		pulleyJointAttachedBodiesMap[id].cpuRot = restart; 

	if(pulleyJointAttachedBodiesMap[id].cpuRotInc > limitRotInc)
		pulleyJointAttachedBodiesMap[id].cpuRotInc = 0.0f;
}

void YEPhysX::ResetRotatePulleyJointBody(int id)
{
	pulleyJointAttachedBodiesMap[id].cpuRot += 0.03f;
	pulleyJointAttachedBodiesMap[id].cpuRotInc -= 0.05f;

	if (pulleyJointAttachedBodiesMap[id].cpuRot > 0.0)
		pulleyJointAttachedBodiesMap[id].cpuRot = 0.0;

	if (pulleyJointAttachedBodiesMap[id].cpuRotInc < 0.0)
		pulleyJointAttachedBodiesMap[id].cpuRotInc = 0.0;
}

void YEPhysX::ResetMovePulleyJointBody(int id)
{
	if (pulleyJointAttachedBodiesMap[id].rightMoveDir > 0.0f)
		pulleyJointAttachedBodiesMap[id].rightMoveDir -= .03f;
	else
		pulleyJointAttachedBodiesMap[id].rightMoveDir += .03f;

	if (pulleyJointAttachedBodiesMap[id].rightMoveDir < 0.0f ||
		pulleyJointAttachedBodiesMap[id].rightMoveDir > 0.0f)
		pulleyJointAttachedBodiesMap[id].rightMoveDir = 0.0f;
}

void YEPhysX::ResetDynamicSphere()
{
	_dynamicSphere->setGlobalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
	_dynamicSphere->putToSleep();
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
	sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;

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

	if (_input->keyDown(DIK_X))
	{
		_dynamicSphere->addForce(PxVec3(0.02f, 0.0f, 0.0f), PxForceMode::eIMPULSE);
	}

	if (_input->keyDown(DIK_G))
	{
		_dynamicSphere->addForce(PxVec3(-0.02f, 0.0f, 0.0f), PxForceMode::eIMPULSE);
	}

	if (_input->keyDown(DIK_F))
	{
		_dynamicSphere->addForce(PxVec3(0.0f, 0.0f, 0.02f), PxForceMode::eIMPULSE);
	}

	if (_input->keyDown(DIK_S))
	{
		_dynamicSphere->addForce(PxVec3(0.0f, 0.0f, -0.02f), PxForceMode::eIMPULSE);
	}

	for (size_t i = 0; i < pulleyJointsList.size(); i++)
		pulleyJointsList[i]->mLocalPose[0] = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxLerp(0.0, cpuRot, cpuRotInc), PxVec3(1, 0, 0)));

	for (size_t i = 0; i < pulleyJointAttachedBodiesMap.size(); i++)
	{
		if (pulleyJointAttachedBodiesMap[i].receivesInput)
			pulleyJointAttachedBodiesMap[i].box->setKinematicTarget(PxTransform(PxVec3(pulleyJointAttachedBodiesMap[i].rightMoveDir + pulleyJointAttachedBodiesMap[i].offset, pulleyJointAttachedBodiesMap[i].box->getGlobalPose().p.y, pulleyJointAttachedBodiesMap[i].box->getGlobalPose().p.z), PxQuat(PxLerp(0, pulleyJointAttachedBodiesMap[i].cpuRot, pulleyJointAttachedBodiesMap[i].cpuRotInc), PxVec3(1, 0, 0))));
		if (!pulleyJointAttachedBodiesMap[i].receivesInput)
			pulleyJointAttachedBodiesMap[i].box->setKinematicTarget(PxTransform(PxVec3(pulleyJointAttachedBodiesMap[i].rightMoveDir + pulleyJointAttachedBodiesMap[i].offset, pulleyJointAttachedBodiesMap[i].box->getGlobalPose().p.y, pulleyJointAttachedBodiesMap[i].box->getGlobalPose().p.z), PxQuat(PxLerp(0, pulleyJointAttachedBodiesMap[i].cpuRot, pulleyJointAttachedBodiesMap[i].cpuRotInc), PxVec3(1, 0, 0))));
	}

	// Raycast ignoring Layer mask
	uint32_t queryMask = ~(LAYER_IGNORE);

	PxQueryFilterData filterData;
	filterData.data.word0 = queryMask;
	filterData.flags = PxQueryFlag::eSTATIC;

	PxVec3 unitDir = PxVec3(0.0f,0.0f,_dynamicSphere->getGlobalPose().p.z);
	PxVec3 dir = unitDir.getNormalized();

	if (_scene->raycast(_dynamicSphere->getGlobalPose().p, dir, 1.0f, hit, PxHitFlag::eDEFAULT, filterData))
	{
		if (hit.block.actor != nullptr)
		{
			PxRaycastHit raycastHit = hit.block;
			
			PxActor* actor = reinterpret_cast<PxActor*>(raycastHit.actor);

			YELogCStr(actor->getName());

			NotifyCollision(actor->getName());
		}
	}

	YELog("\nYEPhysics: Ball Velocity %f" + std::to_string(_dynamicSphere->getLinearVelocity().magnitude()));
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

			actorGlobalPoses[i] = mWorld;
		}
	}
}

void YEPhysX::RenderCallback()
{
	PxScene* scene;
	PxGetPhysics().getScenes(&scene, 1);

	PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC);

	if(nbActors)
	{
		PxArray<PxRigidActor*> actors(nbActors);
		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
		for (PxU32 i = 0; i < nbActors; i++)
		{
			PxArray<PxRigidActor*> rigidActors(nbActors);
			
			Render(&actors[0], static_cast<PxU32>(actors.size()));
		}
	}
}

void YEPhysX::SetKinematicPulleyJointBody(int id)
{
	pulleyJointAttachedBodies[attachedBodiesKinematicID] = pulleyJointAttachedBodiesMap[id].box;
	attachedBodiesKinematicID++;
}

XMMATRIX YEPhysX::GetGlobalPose(UINT actorID)
{
	return actorGlobalPoses[actorID];
}

void YEPhysX::Attach(YEPhysicsColliderListener* observer)
{
	_collision_listeners.push_back(observer);
}

void YEPhysX::NotifyCollision(const char* actorName)
{
	for (auto& listener : _collision_listeners)
	{
		listener->OnNotify(actorName);
	}
}