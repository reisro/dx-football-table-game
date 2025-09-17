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
						 YEWindow(dxInt width, dxInt height);
						 YEWindow(const YEWindow& rhs);
						 virtual ~YEWindow();
					
	static YEWindow*	 CreateInstance();
	static YEWindow*     GetInstance();

	virtual void		 Setup();
	virtual void         Create();
	virtual void		 Show();
	virtual void		 Update();

protected:
	static YEWindow* instance;

private:

	DXRenderer*					 dxRenderer;

	dxInt						 _width;
	dxInt						 _height;
};

#endif _DXWINDOW_H