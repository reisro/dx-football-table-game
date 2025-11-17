#include "FTHandle.h"

FTHandle::FTHandle(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(nullptr)
{
}

FTHandle::~FTHandle()
{
}

void FTHandle::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_handle_right.fbx");

	addComponent(_mesh_component);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
