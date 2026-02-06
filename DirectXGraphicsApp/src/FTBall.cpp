#include "FTBall.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTBall::FTBall(const YEGameContext& _game_context):
	YEGameObject("Football Ball", _game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_ball.fbx")),
	_physics_component(new YEPhysicsComponent(_game_context))
{
	addComponent(_mesh_component);
	addComponent(_physics_component);
}

FTBall::~FTBall()
{
}

void FTBall::start()
{
	// initialize mesh component to load its mesh
	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	YEPhysics::GetInstance()->CreateDynamicSphere(_game_object_name, new YEVector3(.0f,0.0f,0.0f), 0.15f);
}

void FTBall::shutdown()
{
}

void FTBall::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	if (hasRigidBody)
	{
		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		XMMATRIX globalPose = phsyX->GetGlobalPose(_physics_component->_actorPhyicsID);

		_physics_component->getTransformComponent()->setTransformMatrix(globalPose);
	}
}