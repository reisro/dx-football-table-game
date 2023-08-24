#pragma once

#ifndef _DXGRAPHICS_API_H_
#define _DXGRAPHICS_API_H_

#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>

// PhysicX define to suppress windows global min.max macros
#define NOMINMAX
#include <Windows.h>
#include <windowsx.h>

#include "DXTypes.h"

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
static void DXLog(std::string msg)
{
	std::cout << msg << std::endl;
}

#endif _DXGRAPHICS_API_H_