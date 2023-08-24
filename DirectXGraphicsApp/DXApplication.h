#pragma once

#ifndef _DX_APPLICATION_H_
#define _DX_APPLICATION_H_

#include "pch.h"
#include "DXWindow.h"

namespace RFE
{
	class DX_API DXApplication
	{
	public:
		DXApplication();
		~DXApplication();

		static void Setup(const DXEngineConfig::DXConfig& config);
		static bool Init();
		static bool InitWindow();
		static bool InitRenderer();
		static void Run(std::unique_ptr<DXWindow> window);

	private:
		DXWindow window;
	};
}

#endif _DX_APPLICATION_H_