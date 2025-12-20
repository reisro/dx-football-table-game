#include "FTHandle.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTHandle::FTHandle(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_handle.fbx")),
	_physics_component(new YEPhysicsComponent()),
	_player_left(p1),
	_player_right(p2)
{
}

FTHandle::~FTHandle()
{
}

void FTHandle::start()
{
	YEPhysics::GetInstance()->CreateJoint(*_player_left->_transform->getPosition(),
										  *_player_right->_transform->getPosition(), 2);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

	XMMATRIX globalPose = phsyX->GetGlobalPose(_player_left->_id);

	_transform->setTransformMatrix(globalPose);
}
