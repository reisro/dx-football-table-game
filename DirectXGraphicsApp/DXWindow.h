#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#define MAX_LOADSTRING 100

#include "DXAPI.h"
#include "DXRendering.h"

class DX_API DXWindow
{
public:
						 DXWindow();
						 DXWindow(int width, int height);
						 DXWindow(const DXWindow& rhs);
	virtual		        ~DXWindow();

	virtual void         Create();

protected:

private:

	dxInt				 width;
	dxInt                height;
};

#endif _DXWINDOW_H