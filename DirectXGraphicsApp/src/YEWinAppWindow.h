#pragma once

#ifndef _YEWINAPIWINDOW_H
#define _YEWINAPIWINDOW_H

#include "YEWindow.h"

class YEWinAPIWindow : public YEWindow
{
public:
	YEWinAPIWindow();
	YEWinAPIWindow(int width, int height);
	YEWinAPIWindow(const YEWinAPIWindow& rhs);

	virtual ~YEWinAPIWindow();

	void Setup() override;
	void Create() override;
	void Show(uint16_t _width, uint16_t _height) override;

	static void CreateInstance();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // !_YEWINAPIWINDOW_H