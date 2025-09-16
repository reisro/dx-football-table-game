#pragma once

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "DXGame.h"
#include "DXTimer.h"
#include "YEWindow.h"

namespace YE
{
	class DX_API YEApplication
	{
	public:
		YEApplication();
		~YEApplication();

		static void Setup(const YEngineConfig::DXConfig& config);
		static bool Init();
		static bool InitEngine();
		static bool InitWindow();
		static void InitRenderer();
		static YEApplication* GetInstance();
		
		void Run(DXGame* gameApp);
	
	protected:
		static YEApplication* instance;

	private:
		DXGame*	 _gameApp;
		bool  _isRunning;
		bool  _isInitialized;
	};
}

#endif _DX_APPLICATION_H_