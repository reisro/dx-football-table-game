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
	virtual		 ~DXWindow();

	virtual void  Create();

protected:

	DXRendering* dxRendering;

	HINSTANCE	 hInstance;
	LPCSTR		 windowName;
	HWND		 hWnd;
	WNDCLASS	 wndClass;
	LPCSTR		 titleName;
	MSG			 msg;

	int          cmdShow;

private:
	dxInt        width;
	dxInt        height;

	// windows callback event handler 
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif _DXWINDOW_H
