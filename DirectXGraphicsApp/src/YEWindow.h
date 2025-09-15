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
					
	static YEWindow*	 CreateInstance();
	static YEWindow*     GetInstance();

	virtual void		 Setup();
	virtual void         Create();
	virtual void		 Show(uint16_t _width, uint16_t _height);
	virtual void		 Update();

private:

	DXRenderer*					 dxRenderer;

	dxInt						 width;
	dxInt						 height;
};

#endif _DXWINDOW_H