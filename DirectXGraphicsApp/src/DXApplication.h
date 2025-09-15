#pragma once

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "DXGame.h"
#include "DXTimer.h"
#include "YEWindow.h"

namespace YE
{
	class DX_API DXApplication
	{
	public:
		DXApplication();
		~DXApplication();

		static void Setup(const YEngineConfig::DXConfig& config);
		static bool Init();
		static bool InitWindow();
		static void InitRenderer();
		static void Run(DXGame* gameApp);

	protected:
		static DXApplication* instance;

	private:
		YEWindow* _window;
		DXGame*	 _gameApp;
	};
}

#endif _DX_APPLICATION_H_