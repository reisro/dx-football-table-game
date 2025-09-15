#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#define MAX_LOADSTRING 100

#include "pch.h"
#include "DXRenderer.h"

class DX_API YEWindow
{
public:
						 YEWindow();
						 YEWindow(int width, int height);
						 YEWindow(const YEWindow& rhs);
						 virtual ~YEWindow();
	
						void* GetWindowsHandle() { return hWnd; }
					
	static void			 CreateInstance();

	virtual void		 Setup();
	virtual void         Create();
	virtual void		 Show(uint16_t _width, uint16_t _height);

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