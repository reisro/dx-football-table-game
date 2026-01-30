#pragma once
#pragma warning(disable : 4838) 

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "YEGame.h"
#include "YETimer.h"
#include "YEWindow.h"
#include "YEPhysics.h"
#include "YEInput.h"

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
		static bool InitInput();
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
		YEPhysics*			 _physics;
		YEInput*			 _input;
		YEGameContext		 _gameContext;
		yeFloat				 _accumulator;
		dxDouble             _targetFPS;
		dxDouble			 _frameDuration;
		bool				 _isRunning;
		bool				 _isInitialized;
		bool				 _isLoopInitialized;
	};
}

#endif _DX_APPLICATION_H_