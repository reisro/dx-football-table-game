#include "FTHandle.h"
#include "YEGameContext.h"
#include <YEPhysX.h>

FTHandle::FTHandle(const YEGameContext& _game_context, FTPlayer* p1, FTPlayer* p2, const wchar_t* meshName):
	YEGameObject(_game_context),
	_mesh_component(new YEMeshComponent(this, meshName)),
	_player_left(p1),
	_player_right(p2),
	_meshFilename(meshName)
{
	addComponent(_mesh_component);
}

FTHandle::~FTHandle()
{
}

void FTHandle::start()
{
	YEPhysics::GetInstance()->CreateJoint(*_player_left->_transform->getPosition(),
										  *_player_right->_transform->getPosition(), 2, _isCPU);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());
}

void FTHandle::shutdown()
{
}

void FTHandle::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	YEPhysX* phsyX = reinterpret_cast<YEPhysX*>(YEPhysics::GetInstance());
	
	XMMATRIX globalPose = phsyX->GetGlobalPose(_player_left->getPhysicsComponent()->_actorPhyicsID);
	
	XMFLOAT4X4 world;
	world._11 = globalPose.r[0].m128_f32[0]; world._12 = globalPose.r[0].m128_f32[1]; world._13 = globalPose.r[0].m128_f32[2]; world._14 = globalPose.r[0].m128_f32[3];
	world._21 = globalPose.r[1].m128_f32[0]; world._12 = globalPose.r[1].m128_f32[1]; world._13 = globalPose.r[1].m128_f32[2]; world._14 = globalPose.r[1].m128_f32[3];
	world._31 = globalPose.r[2].m128_f32[0]; world._12 = globalPose.r[2].m128_f32[1]; world._13 = globalPose.r[2].m128_f32[2]; world._14 = globalPose.r[2].m128_f32[3];
	world._41 = globalPose.r[3].m128_f32[0] + 15.0f; world._12 = globalPose.r[3].m128_f32[1]; world._13 = globalPose.r[3].m128_f32[2]; world._14 = globalPose.r[3].m128_f32[3];

	_transform->setTransformMatrix(globalPose);
}
