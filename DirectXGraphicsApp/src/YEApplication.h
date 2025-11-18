#pragma once
#pragma warning(disable : 4838) 

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "YEGame.h"
#include "DXTimer.h"
#include "YEWindow.h"

struct YEGameContext;

namespace YE
{
	enum class GamePrimitives
	{
		Cube,
		Capsule,
		Cylinder,
		Torus
	};

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
		static bool InitPhysics();
		static void CreatePrimitive(GamePrimitives primitive);
		static void Import3DModel();

		static YEApplication* GetInstance();
		
		void Run(YEGame* gameApp);
	
	protected:
		static YEApplication* instance;

	private:
		MSG			         _msg;
		YEGame*		         _gameApp;
		YERenderer*			 _renderer;
		YEGameContext		 _gameContext;
		bool				 _isRunning;
		bool				 _isInitialized;
		bool				 _isLoopInitialized;
	};
}

#endif _DX_APPLICATION_H_