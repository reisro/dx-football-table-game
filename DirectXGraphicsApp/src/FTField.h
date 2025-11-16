#pragma once

#ifndef _FT_FIELD_H_
#define _FT_FIELD_H_

#include "YEGameObject.h"
#include "YEMeshComponent.h"

class FTField : public YEGameObject
{
public:
	FTField(const YEGameContext& _game_context);
	virtual ~FTField();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YEMeshComponent* _mesh_component;
};

#endif _FT_FIELD_H_