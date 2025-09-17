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

		static void Setup(const YEngineConfig::YEConfig& config);
		static bool Init();
		static bool InitEngine();
		static bool InitWindow();
		static bool InitRenderer();
		static YEApplication* GetInstance();
		
		void Start(DXGame* gameApp);
	
	protected:
		static YEApplication* instance;

	private:
		MSG		 _msg;
		DXGame*	 _gameApp;
		bool	_isRunning;
		bool	_isInitialized;
	};
}

#endif _DX_APPLICATION_H_