#pragma once

#ifndef YE_FILE_SYSTEM_H
#define YE_FILE_SYSTEM_H

#include "pch.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class DX_API YEFileSystem
{
public:
	YEFileSystem() = default;
	~YEFileSystem();

	static const char* FindAssetAt(const char* _assetPath);
	static const char* FindExecutablePath(const char* _assetPath);

};

#endif