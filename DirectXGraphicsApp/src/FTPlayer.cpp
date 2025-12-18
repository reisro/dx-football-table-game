#include "FTPlayer.h"
#include <YEPhysX.h>

FTPlayer::FTPlayer(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_player.fbx")),
	_physics_component(new YEPhysicsComponent())
{
	addComponent(_mesh_component);
	addComponent(_physics_component);
}

FTPlayer::~FTPlayer()
{
}

void FTPlayer::start()
{
	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	YEPhysics::GetInstance()->CreateJoint(*new YEVector3(0.0f, 1.1f, 3.63704f), 2);
}

void FTPlayer::shutdown()
{
}

void FTPlayer::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	if (hasRigidBody)
	{
		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		XMMATRIX globalPose = phsyX->GetGlobalPose(_id);

		YELog("YEGameObject: id:" + std::to_string(_id));

		_physics_component->getTransformComponent()->setPosition(
			globalPose.r[3].m128_f32[0],
			globalPose.r[3].m128_f32[1],
			globalPose.r[3].m128_f32[2]);

		_physics_component->getTransformComponent()->setTransformMatrix(globalPose);

		/*YELog("Global Pose: X:" + std::to_string(globalPose.r[3].m128_f32[0]) +
		" Y:" + std::to_string(globalPose.r[3].m128_f32[1]) +
		" Z:" + std::to_string(globalPose.r[3].m128_f32[2]));*/
	}
}
