#pragma once

#ifndef _DXGRAPHICS_API_H_
#define _DXGRAPHICS_API_H_

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

//-----------------------------------------------------------------------------
// Standard headers
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>
#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include "dxerr.h"

//-----------------------------------------------------------------------------
// // PhysicX define to suppress windows global min.max macros
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <windowsx.h>

//-----------------------------------------------------------------------------
// Utilities Macros
//-----------------------------------------------------------------------------
#define _DXGE_STRING(String)
#define DXGE_LOG(x) DebugLog(x)

#ifndef _DXGE_SAFE_DELETE
#define _DXGE_SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif

#ifndef _DXGE_SAFE_DELETE_ARRAY
#define _DXGE_SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif 

#ifndef _DXGE_SAFE_RELEASE
#define _DXGE_SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

//-----------------------------------------------------------------------------
// Global Defines & Macros
//-----------------------------------------------------------------------------
// Macros to provide automatic integration with DLL interface where applicable.
// DLL Compilation
#ifndef DXGRAPHICS_API_EXPORTS
#define DX_API __declspec(dllexport)
#else 
#define DX_API __declspec(dllimport)
#endif

//-----------------------------------------------------------------------------
// Utilities Functions
//-----------------------------------------------------------------------------
static void YELog(std::string msg)
{
	std::cout << msg << std::endl;
}

//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

//---------------------------------------------------------------------------------------
// Convenience macro for deleting objects.
//---------------------------------------------------------------------------------------

#define SafeDelete(x) { delete x; x = 0; }

//---------------------------------------------------------------------------------------
// Simple d3d error checker for book demos.
//---------------------------------------------------------------------------------------

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			YELog("HR Result Failed...");					   \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

#endif _DXGRAPHICS_API_H_