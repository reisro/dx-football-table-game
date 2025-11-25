#include "FTBall.h"
#include "YEGameContext.h"
#include "YEPhysX.h"

FTBall::FTBall(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_ball.fbx")),
	_physics_component(new YEPhysicsComponent)
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
}

void FTBall::shutdown()
{
}

void FTBall::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	if (hasRigidBody)
	{
		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(_physics_component->GetPhysicsEngine());

		XMMATRIX globalPose = phsyX->GetGlobalPose(_id);

		_physics_component->getTransformComponent()->setPosition(
			globalPose.r[3].m128_f32[0],
			globalPose.r[3].m128_f32[1],
			globalPose.r[3].m128_f32[2]);
	}
}