#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#include "DXAPI.h"
#include "DXRendering.h"

class DX_API DXWindow
{
public:
	DXWindow();
	DXWindow(int width, int height);
	DXWindow(const DXWindow& rhs);
	virtual ~DXWindow();

	virtual void Create();

protected:

	DXRendering* dxRendering;

private:

};

#endif _DXWINDOW_H
