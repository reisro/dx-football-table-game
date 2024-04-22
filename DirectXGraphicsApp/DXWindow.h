#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#define MAX_LOADSTRING 100

#include "pch.h"
#include "DXRenderer.h"

class DX_API DXWindow
{
public:
						 DXWindow();
						 DXWindow(int width, int height);
						 DXWindow(const DXWindow& rhs);
	virtual		        ~DXWindow();

	static void			 CreateInstance();

	virtual void		 Setup();
	virtual void         Create();
	virtual void		 Show();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND				 hWnd;
	WNDCLASSEX			 wc;
	MSG					 msg;

private:

	DXRenderer*					 dxRenderer;

	dxInt						 width;
	dxInt						 height;
};

#endif _DXWINDOW_H