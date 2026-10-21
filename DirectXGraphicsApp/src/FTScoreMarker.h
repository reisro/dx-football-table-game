#pragma once

#ifndef _H_FT_SCORE_H_MARKER_H
#define _H_FT_SCORE_H_MARKER_H

#include "YEGameObject.h"
#include "YEMeshComponent.h"
#include "YEFileSystem.h"

class FTScoreMarker : public YEGameObject
{
public:
	FTScoreMarker(const YEGameContext& _game_context);
	virtual ~FTScoreMarker();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void SetInitialPosition(float pos);
	void SetMarkerOffset(float offset);
	void PlaceMarkerAt(int number);
	void ResetMarkerUpdate() { _markerUpdated = false; }

	bool _isPositiveOffset;

private:
	YEMeshComponent* _mesh_component;
	bool			 _markerUpdated;
	float			 _marker_offset;
	float			 _marker_pos;
	float            _marker_startPos;
};

#endif _H_FT_SCORE_H_MARKER_H