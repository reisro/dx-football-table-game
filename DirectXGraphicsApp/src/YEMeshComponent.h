#pragma once

#ifndef _YE_MESH_COMPONENT_H_
#define _YE_MESH_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEMesh.h"

class YEMeshComponent : public YEBaseComponent
{
	public:

	YEMeshComponent();

	virtual ~YEMeshComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

private:
	YEMesh* ModelMesh;
};

#endif

