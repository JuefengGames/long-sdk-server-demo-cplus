#pragma once
#include <string>

class OrderInfoPojo
{
private:
    std::string orderId;  // juefeng games order id£¬Globally unique

    std::string gameRole; // game role identify

    std::string gameArea; // game area identify

    std::string productName; // VIP

    std::string productDesc; // 100 diamonds

    std::string remark;  // Developer order information, returned as is, maximum length 64 characters

    std::string payTime; // 2024-01-13 12:15:30

    std::string amount;  // 648.00 , 0.99, 100

    std::string payWay;  // 1

    std::string sign;
public:
    // Getter and Setter for orderId
    std::string getOrderId() const { return orderId; }
    void setOrderId(const std::string& orderId) { this->orderId = orderId; }

    // Getter and Setter for gameRole
    std::string getGameRole() const { return gameRole; }
    void setGameRole(const std::string& gameRole) { this->gameRole = gameRole; }

    // Getter and Setter for gameArea
    std::string getGameArea() const { return gameArea; }
    void setGameArea(const std::string& gameArea) { this->gameArea = gameArea; }

    // Getter and Setter for productName
    std::string getProductName() const { return productName; }
    void setProductName(const std::string& productName) { this->productName = productName; }

    // Getter and Setter for productDesc
    std::string getProductDesc() const { return productDesc; }
    void setProductDesc(const std::string& productDesc) { this->productDesc = productDesc; }

    // Getter and Setter for remark
    std::string getRemark() const { return remark; }
    void setRemark(const std::string& remark) { this->remark = remark; }

    // Getter and Setter for payTime
    std::string getPayTime() const { return payTime; }
    void setPayTime(const std::string& payTime) { this->payTime = payTime; }

    // Getter and Setter for amount
    std::string getAmount() const { return amount; }
    void setAmount(const std::string& amount) { this->amount = amount; }

    // Getter and Setter for payWay
    std::string getPayWay() const { return payWay; }
    void setPayWay(const std::string& payWay) { this->payWay = payWay; }

    // Getter and Setter for sign
    std::string getSign() const { return sign; }
    void setSign(const std::string& sign) { this->sign = sign; }
};

