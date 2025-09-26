#pragma once
#pragma warning(disable : 4838) 

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "YEGame.h"
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
		
		void Run(YEGame* gameApp);
	
	protected:
		static YEApplication* instance;

	private:
		MSG			_msg;
		YEGame*		_gameApp;
		DXRenderer* _renderer;
		bool		_isRunning;
		bool		_isInitialized;
		bool		_isLoopInitialized;
	};
}

#endif _DX_APPLICATION_H_