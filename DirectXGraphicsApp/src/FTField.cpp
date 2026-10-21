#include "FTField.h"
#include <YEPhysX.h>

FTField::FTField(const YEGameContext& _game_context):
	YEGameObject("Football Field", _game_context),
	_mesh_component(new YEMeshComponent(this, ".//Game Assets//football_table_field2.fbx"))
{
}

FTField::~FTField()
{
}

void FTField::start()
{
	const char* _executablePath = YEFileSystem::FindExecutablePath(_mesh_component->GetFilenamePath());

	addComponent(_mesh_component);

	_mesh_component->LoadModel(_executablePath);

	YEPhysics::GetInstance()->CreateDefaultPlane();
}

void FTField::shutdown()
{
}

void FTField::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}