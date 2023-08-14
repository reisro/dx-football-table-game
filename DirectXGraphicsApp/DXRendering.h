#pragma once

#ifndef _DX_RENDERING_H
#define _DX_RENDERING_H

#include "DXAPI.h"
#include "DXSubsystem.h"

class DXRendering: public DXSubsystem
{
public:
	DXRendering();
	DXRendering(const DXRendering& rhs);
	virtual ~DXRendering();

	void Setup() override;
	bool Init()  override;
	void PostInit() override;

protected:

	static DXRendering* instance;

private:

};

#endif _DX_RENDERING_H
