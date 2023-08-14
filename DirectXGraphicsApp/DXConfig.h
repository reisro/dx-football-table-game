#pragma once

#ifndef _DX_CONFIG_H
#define _DX_CONFIG_H

#include "DXAPI.h"

namespace DXEngineConfig
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

	//-----------------------------------------------------------------------------
	// API Support
	//-----------------------------------------------------------------------------
	// 
	// Support DirectX 11 rendering API (render driver and resource types).
	#if !defined (DX11_RENDER_SUPPORT)
		#define DX11_RENDER_SUPPORT
	#endif

	struct DX_API DXConfig
	{
		DXConfig():
		
			#ifdef DX11_RENDER_SUPPORT
				graphicsAPI(GraphicsAPI::DirectX11)
			#endif // DX11_RENDER_SUPPORT
		{
		}

		GraphicsAPI			graphicsAPI;
		static DXConfig		instance;
	};
}

#endif _DX_CONFIG_H