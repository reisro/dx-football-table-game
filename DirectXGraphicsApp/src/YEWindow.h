#pragma once

#ifndef _DXWINDOW_H
#define _DXWINDOW_H

#define MAX_LOADSTRING 100

#include "pch.h"
#include "YERenderer.h"

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
	virtual void		 OnResize(YERenderer* renderer);

public:
	dxInt				 _width;
	dxInt				 _height;

protected:
	static YEWindow*	 instance;

private:

	YERenderer*			 dxRenderer;
};

#endif _DXWINDOW_H