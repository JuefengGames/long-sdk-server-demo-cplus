#include "OrderCallBackController.h"
#include "KeysConfig.h"
#include <iostream>
#include "StringHelper.h"

std::string OrderCallBackController::callBack(OrderInfoPojo infoPojo)
{
    std::string signFromJueFeng = infoPojo.getSign();
    std::cout << "收到的签名" << signFromJueFeng << std::endl;
    std::string devSignStr =
        "amount=" + infoPojo.getAmount() +
        "&gameArea=" + infoPojo.getGameArea() +
        "&gameRole=" + infoPojo.getGameRole() +
        "&orderId=" + infoPojo.getOrderId() +
        "&payTime=" + infoPojo.getPayTime() +
        "&payWay=" + infoPojo.getPayWay() +
        "&productDesc=" + infoPojo.getProductDesc() +
        "&productName=" + infoPojo.getProductName() +
        "&remark=" + infoPojo.getRemark() +
        KeysConfig::SERVER_KEY;
    std::cout<<" before sign deSignStr=" + devSignStr<<std::endl;
    std::string devSign = StringHelper::calculateMD5(devSignStr);
    std::cout << " after sign devSign=" + devSign << std::endl;
    if (signFromJueFeng._Equal(devSign)) {
        std::cout << "-------- sign is ok" << std::endl;
        /**
         *
         *  Do somthing
         *
         */
        return "success";
    }
    else {
        std::cout << "-------- sign is error" << std::endl;
    }
    return "failed";

}
