#include "FTField.h"
#include <YEPhysX.h>

FTField::FTField(const YEGameContext& _game_context):
	YEGameObject(_game_context),
	_mesh_component(nullptr),
	_physics_component(nullptr)
{
}

FTField::~FTField()
{
}

void FTField::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_table_field.fbx");
	_physics_component = new YEPhysicsComponent(this);

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

	if (hasRigidBody)
	{
		YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());

		XMMATRIX globalPose = phsyX->GetGlobalPose(_id);

		_physics_component->getTransformComponent()->setPosition(
			globalPose.r[3].m128_f32[0],
			globalPose.r[3].m128_f32[1],
			globalPose.r[3].m128_f32[2]);
	}
}