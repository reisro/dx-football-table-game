#pragma once

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "DXWindow.h"

namespace YE
{
	class DX_API DXApplication
	{
	public:
		DXApplication();
		~DXApplication();

		static void Setup(const DXEngineConfig::DXConfig& config);
		static bool Init(DXWindow* window);
		static bool InitWindow();
		static void InitRenderer();
		static void Run();

	private:
		DXWindow window;
	};
}

#endif _DX_APPLICATION_H_