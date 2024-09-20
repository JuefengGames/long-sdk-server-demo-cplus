#pragma once
#include <string>
class StringHelper
{
public:
	static std::string UTF8ToGBK(const std::string& strUTF8);
	static std::string calculateMD5(const std::string& input);
};

