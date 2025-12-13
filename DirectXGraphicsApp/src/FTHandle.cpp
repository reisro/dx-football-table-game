#include "FTHandle.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTHandle::FTHandle(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, L"C:\\Game Assets\\football_handle_right.fbx")),
	_mesh_component1(new YEMeshComponent(this, L"C:\\Game Assets\\football_player.fbx")),
	_mesh_component2(new YEMeshComponent(this, L"C:\\Game Assets\\football_player.fbx")),
	_physics_component(new YEPhysicsComponent())
{
	addComponent(_mesh_component);
	addComponent(_mesh_component1);
	addComponent(_mesh_component2);
	addComponent(_physics_component);

	hasChildren = true;
	_numberChildren = 2;
}

FTHandle::~FTHandle()
{
}

void FTHandle::start()
{
	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
	_mesh_component1->LoadModel(_mesh_component1->GetFilenamePath());
	_mesh_component2->LoadModel(_mesh_component2->GetFilenamePath());

	//YEPhysics::GetInstance()->CreateJoint(2);
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
