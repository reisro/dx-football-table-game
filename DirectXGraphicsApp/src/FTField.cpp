#include "FTField.h"
#include <YEPhysX.h>

FTField::FTField(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(nullptr)
{
}

FTField::~FTField()
{
}

void FTField::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_table_field1.fbx");

	addComponent(_mesh_component);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	YEPhysics::GetInstance()->CreateDefaultPlane();
}

void FTField::shutdown()
{
}

void FTField::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}