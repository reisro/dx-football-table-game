#pragma once

#ifndef _YEWINAPIWINDOW_H
#define _YEWINAPIWINDOW_H

#include "YEWindow.h"

// Windows platform includes
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

class YEWinAppWindow : public YEWindow
{
public:
	YEWinAppWindow();
	YEWinAppWindow(dxInt width, dxInt height);
	YEWinAppWindow(const YEWinAppWindow& rhs);

	virtual ~YEWinAppWindow();

	void  Setup()    override;
	void  Create()   override;
	void  Show()     override;
	void  Update()   override;
	void  OnResize(YERenderer* renderer) override;

	HINSTANCE  GetHInstance()	   { return GetModuleHandle(NULL); }
	HWND	   GetWindowsHandle()  { return hWnd; }

	static void CreateInstance();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HINSTANCE			 hInstance;
	HWND				 hWnd;
	WNDCLASSEX			 wc;
};

#endif // !_YEWINAPIWINDOW_H