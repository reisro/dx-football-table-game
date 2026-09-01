#include "YEFileSystem.h"

YEFileSystem::~YEFileSystem()
{
}

const wchar_t* YEFileSystem::FindAssetAt(const wchar_t* _assetPath)
{
    fs::path assetPath(_assetPath);

    const wchar_t* entry;
    
    if (fs::exists(assetPath))
    {
        // Asset found, handle accordingly
        try
        {
           entry = fs::relative(_assetPath).c_str();
        }
        catch (const fs::filesystem_error& e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
    }
    else
    {
        // Asset not found, handle accordingly
        std::cerr << "Asset not found: " << _assetPath << std::endl;
        entry = 0; // or some other indication of failure
	}

    return entry;
}