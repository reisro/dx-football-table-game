#pragma once

#ifndef _DX_CONFIG_H
#define _DX_CONFIG_H

namespace YEngineConfig
{
	enum class GraphicsAPI
	{
		DirectX9,
		DirectX10,
		DirectX11,
		DirectX12,
		OpenGL_4_5,
		Vulkan
	};

	enum class Platform
	{
		Windows,
		Linux,
		MacOS,
		Android,
		iOS
	};

	enum class InputAPI
	{
		XInput
	};

	//-----------------------------------------------------------------------------
	// API Support
	//-----------------------------------------------------------------------------
	// 
	// Support DirectX 11 rendering API (render driver and resource types).
	#if !defined (DX11_RENDER_SUPPORT)
		#define DX11_RENDER_SUPPORT
	#endif

	struct AppResolution
	{
		dxInt width;
		dxInt height;
	};

	struct DX_API YEConfig
	{
		YEConfig():
		
			#ifdef DX11_RENDER_SUPPORT
				graphicsAPI(GraphicsAPI::DirectX11),
			#endif // DX11_RENDER_SUPPORT
			
				inputAPI(InputAPI::XInput),
				platform(Platform::Windows)
		{
		}

		GraphicsAPI			graphicsAPI;
		Platform			platform;
		InputAPI			inputAPI;
		AppResolution		resolution;
		static YEConfig		instance;
	};
}

#endif _DX_CONFIG_H