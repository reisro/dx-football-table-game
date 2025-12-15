#include "FTHandle.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTHandle::FTHandle(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_handle_right.fbx")),
	_physics_component(new YEPhysicsComponent())
{
	addComponent(_mesh_component);
	addComponent(_physics_component);
}

FTHandle::~FTHandle()
{
}

void FTHandle::start()
{
	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	YEPhysics::GetInstance()->CreateJoint(*_transform->getPosition(), 2);
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
