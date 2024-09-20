#include "TestSentCallBack.h"
#include <string>
#include "LibcurlHttpHelper.h"
#include "StringHelper.h"
#include "KeysConfig.h"

std::string TestSentCallBack::sendCallBackPost()
{
    std::string amount = "68.0";
    std::string gameArea = "195";
    std::string gameRole = "35734";
    std::string orderId = "ZFB20240204141435717198";
    std::string payTime = "2024-02-04 14:15:00";
    std::string payWay = "10";
    std::string productName = "100 diamonds";
    std::string productDesc = "100 diamonds";
    std::string remark = "31991TJUEFENG7Fe3N630347256561664";
    std::string serverKey = KeysConfig::SERVER_KEY;

    std::string devSignStr =
        "amount=" + amount +
        "&gameArea=" + gameArea +
        "&gameRole=" + gameRole +
        "&orderId=" + orderId +
        "&payTime=" + payTime +
        "&payWay=" + payWay +
        "&productDesc=" + productDesc +
        "&productName=" + productName +
        "&remark=" + remark +
        serverKey;

    std::string sign = StringHelper::calculateMD5(devSignStr);
    std::string postData =
        "amount=" + amount +
        "&gameArea=" + gameArea +
        "&gameRole=" + gameRole +
        "&orderId=" + orderId +
        "&payTime=" + payTime +
        "&payWay=" + payWay +
        "&productDesc=" + productDesc +
        "&productName=" + productName +
        "&remark=" + remark +
        "&sign=" + sign;
    std::string posturl = "http://localhost:8080/juefeng/callback";
    std::string postResult = LibcurlHttpHelper::sendHttpPost(posturl, postData);
    std::cout << "请求响应数据：" << postResult << std::endl;
    std::cout.flush();
    if (postResult._Equal("")) {
        postResult = "/juefeng/callback called but response data is null";
    }
    return postResult;
}
