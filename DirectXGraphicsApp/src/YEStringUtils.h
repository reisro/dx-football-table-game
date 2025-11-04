#include <codecvt>
#include <locale>
#include <string>
#include <iostream>
#include <wtypes.h>

namespace YEStringUtils 
{
	static std::string ConvertLPWSTRToString(const wchar_t* lpwstr)
	{
		size_t convertedChars = 0;
		char str_c[1024];
		wcstombs_s(&convertedChars, str_c, sizeof(str_c), lpwstr, _TRUNCATE);
		std::string out_str = str_c;
		return out_str;
	}
}