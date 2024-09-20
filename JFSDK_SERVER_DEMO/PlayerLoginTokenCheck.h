#pragma once
#include <string>
class PlayerLoginTokenCheck
{
public:
	std::string checkToken(const std::string& appId, const std::string& memId, const std::string& userToken);
};

