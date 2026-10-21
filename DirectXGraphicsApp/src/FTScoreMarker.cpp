#include "FTScoreMarker.h"
#include <FTFieldWalls.h>

FTScoreMarker::FTScoreMarker(const YEGameContext& _game_context):
	YEGameObject("FTScoreMarker", _game_context),
	_mesh_component(nullptr)
{
}

FTScoreMarker::~FTScoreMarker()
{
}

void FTScoreMarker::start()
{
	_mesh_component = new YEMeshComponent(this, ".//Game Assets//marker_new.fbx");

	const char* _executablePath = YEFileSystem::FindExecutablePath(_mesh_component->GetFilenamePath());

	addComponent(_mesh_component);

	_mesh_component->LoadModel(_executablePath);
}

void FTScoreMarker::shutdown()
{
}

void FTScoreMarker::update(float _deltaTime)
{
}

void FTScoreMarker::SetInitialPosition(float pos)
{
	_marker_pos = pos;
}

void FTScoreMarker::SetMarkerOffset(float offset)
{
	_marker_offset = offset;
}

void FTScoreMarker::PlaceMarkerAt(int number)
{
	if (!_markerUpdated)
	{
		if (_isPositiveOffset)
			_transform->setPosition(_marker_pos + (_marker_offset * number), 1.35f, -10.2f);
		else
			_transform->setPosition(_marker_pos - (_marker_offset * number), 1.35f, 10.2f);
	}

	_markerUpdated = true;
}