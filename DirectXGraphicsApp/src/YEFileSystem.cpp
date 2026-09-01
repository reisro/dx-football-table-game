#include "YEFileSystem.h"

YEFileSystem::~YEFileSystem()
{
}

const wchar_t* YEFileSystem::FindAssetAt(const wchar_t* _assetPath)
{
    fs::path assetPath(_assetPath);

    const wchar_t* entry = nullptr;
    
    if (fs::exists(".//"))
    {
        // Asset found, handle accordingly
        try
        {
            // fs::absolute returns a path, use .string() to get std::string (UTF-8), or .wstring() for std::wstring
            std::wstring absPath = fs::absolute(assetPath).wstring();
            //int size_needed = WideCharToMultiByte(CP_UTF8, 0, absPath.c_str(), -1, NULL, 0, NULL, NULL);
            // ... (your logic here, e.g., allocate buffer and convert if needed)

			entry = absPath.data(); // or store it in a member variable if needed
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
        entry = nullptr; // or some other indication of failure
    }

    return entry;
}