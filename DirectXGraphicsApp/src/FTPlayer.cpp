#include "FTPlayer.h"
#include <YEPhysX.h>

FTPlayer::FTPlayer(const YEGameContext& _game_context, const wchar_t* _meshName):
	YEGameObject("Football Player", _game_context),
	_mesh_component(new YEMeshComponent(this, _meshName)),
	_physics_component(new YEPhysicsComponent(_game_context))
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

		XMMATRIX globalPose = phsyX->GetGlobalPose(_physics_component->_actorPhyicsID);

		YELog("YEGameObject: id:" + std::to_string(_id));

		_physics_component->getTransformComponent()->setTransformMatrix(globalPose);

		/*YELog("Global Pose: X:" + std::to_string(globalPose.r[3].m128_f32[0]) +
		" Y:" + std::to_string(globalPose.r[3].m128_f32[1]) +
		" Z:" + std::to_string(globalPose.r[3].m128_f32[2]));*/
	}
}
