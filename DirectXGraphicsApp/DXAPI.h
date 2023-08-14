#pragma once

#ifndef _DXGRAPHICS_API_H_
#define _DXGRAPHICS_API_H_

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <memory>

// PhysicX define to suppress windows global min.max macros
#define NOMINMAX
#include <Windows.h>

#include "DXTypes.h"

//-----------------------------------------------------------------------------
// Utilities Macros
//-----------------------------------------------------------------------------
#define _RFGE_STRING(String)
#define RFGE_LOG(x) DebugLog(x)

#ifndef _RFGE_SAFE_DELETE
#define _RFGE_SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif

#ifndef _RFGE_SAFE_DELETE_ARRAY
#define _RFGE_SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif 

#ifndef _RFGE_SAFE_RELEASE
#define _RFGE_SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
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
static void DebugLog(std::string msg)
{
	std::cout << msg << std::endl;
}

#endif _DXGRAPHICS_API_H_