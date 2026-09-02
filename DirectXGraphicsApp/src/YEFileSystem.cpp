#include "YEFileSystem.h"

YEFileSystem::~YEFileSystem()
{
}

const char* YEFileSystem::FindAssetAt(const char* _assetPath)
{
    fs::path assetPath(_assetPath);

    std::string abs_path = fs::absolute(_assetPath).string();

    if (fs::exists(_assetPath))
    {
        std::cout << abs_path << std::endl;
    }

    char* dynamicMessage = static_cast<char*>(malloc(abs_path.length() + 1));

    if (dynamicMessage == nullptr)
    {
        return nullptr;
    }

    strcpy_s(dynamicMessage, abs_path.length() + 1, abs_path.c_str());

    return dynamicMessage;
}