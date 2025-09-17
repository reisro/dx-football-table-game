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

	void  Setup() override;
	void  Create() override;
	void  Show() override;
	void  Update() override;
	HWND GetWindowsHandle() { return hWnd; }

	static void CreateInstance();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND				 hWnd;
	WNDCLASSEX			 wc;

private:
	dxInt						 _width;
	dxInt						 _height;
};

#endif // !_YEWINAPIWINDOW_H