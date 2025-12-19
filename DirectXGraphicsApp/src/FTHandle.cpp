#include "FTHandle.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTHandle::FTHandle(const YEGameContext& _game_context, bool isEmpty):
	YEGameObject(_game_context, isEmpty),
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
	//_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	YEPhysics::GetInstance()->CreateJoint(*new YEVector3(0.0f, 0.55f, 3.63704f), 2);
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
