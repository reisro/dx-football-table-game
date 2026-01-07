#include "FTPlayerWhite.h"

FTPlayerWhite::FTPlayerWhite(const YEGameContext& _game_context) :
	YEGameObject(_game_context),
	_mesh_component(nullptr)
{
}

FTPlayerWhite::~FTPlayerWhite()
{
}

void FTPlayerWhite::start()
{
	_mesh_component = new YEMeshComponent(this, L"C:\\Game Assets\\football_player_white.fbx");

	addComponent(_mesh_component);

	_mesh_component->LoadModel(_mesh_component->GetFilenamePath());

	_behaviour_tree = new PlayerOpponentBehaviour();
	_behaviour_tree->SetComposite(new YESelector()); // Set the root node appropriately
}

void FTPlayerWhite::shutdown()
{
}

void FTPlayerWhite::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);
}
