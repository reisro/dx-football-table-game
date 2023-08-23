#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#define MAX_LOADSTRING 100

#include "pch.h"
#include "DXRendering.h"
#include "dear_imgui/imgui.h"
#include "dear_imgui/backends/imgui_impl_win32.h"

class DX_API DXWindow
{
public:
						 DXWindow();
						 DXWindow(int width, int height);
						 DXWindow(const DXWindow& rhs);
	virtual		        ~DXWindow();

	virtual void		 Setup();
	virtual void         Create();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND				 hWnd;
	WNDCLASSEX			 wc;
	MSG					 msg;

private:

	DXRendering					 dxRendering;

	dxInt						 width;
	dxInt						 height;
};

#endif _DXWINDOW_H