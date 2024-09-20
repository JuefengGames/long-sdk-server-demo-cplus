#include "PlayerLoginTokenCheck.h"
#include <iostream>
#include <string>
#include "LibcurlHttpHelper.h"
#include "KeysConfig.h"
#include "StringHelper.h"

std::string PlayerLoginTokenCheck::checkToken(const std::string& appId, const std::string& memId, const std::string& userToken)
{
    std::string sourceStr = "app_id=" + appId + "&mem_id=" + memId + "&user_token=" + userToken + "&app_key=" + "YOUR_SERVER_KEY";
    std::cout << "before sourceStr =" << sourceStr << std::endl;
    std::string sign = StringHelper::calculateMD5(sourceStr);
    std::cout << "after sign =" << sign << std::endl;

    try {
        std::string body = "app_id=" + appId + "&mem_id=" + memId + "&user_token=" + userToken + "&sign=" + sign;
        std::string postResult = LibcurlHttpHelper::sendHttpPost(KeysConfig::TOKEN_CHECK_API_URL, body);
        return postResult;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error(e.what());
    }
}
