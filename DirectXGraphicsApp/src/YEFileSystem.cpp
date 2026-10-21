#include "YEFileSystem.h"
#include "YEFileSystem.h"

YEFileSystem::~YEFileSystem()
{
}

const char* YEFileSystem::FindAssetAt(const char* _assetPath)
{
    char* dynamicMessage = nullptr;

    try
    {
        fs::path assetPath(_assetPath);

        std::string abs_path = fs::absolute(_assetPath).string();
                
        if (fs::exists(_assetPath))
        {
            std::cout << abs_path << std::endl;
        }

        dynamicMessage = static_cast<char*>(malloc(abs_path.length() + 1));

        if (dynamicMessage != nullptr)
        {
            strcpy_s(dynamicMessage, abs_path.length() + 1, abs_path.c_str());
        }
        else
        {
            return nullptr;
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;

        return nullptr;
    }

    return dynamicMessage;
}

const char* YEFileSystem::FindExecutablePath(const char* _assetPath)
{
    char* dynamicMessage = nullptr;

    #ifdef _WIN32
        wchar_t path[MAX_PATH] = { 0 };
        GetModuleFileNameW(NULL, path, MAX_PATH);

        std::string abs_path = fs::path(path).parent_path().string();

		const size_t finalLength = abs_path.length() + strlen(_assetPath) + 1;

        char* _finalPath = static_cast<char*>(malloc(finalLength));

        if (_finalPath != nullptr)
        {
            strcpy_s(_finalPath, finalLength, abs_path.c_str());

            strcat_s(_finalPath, finalLength, _assetPath);

            //free(_finalPath);
        }

        return _finalPath;
    #else
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        return std::string(result, (count > 0) ? count : 0);
    #endif
}