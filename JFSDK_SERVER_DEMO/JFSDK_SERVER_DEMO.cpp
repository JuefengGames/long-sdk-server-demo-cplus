#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/thread_pool.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <map>
#include "TestSentCallBack.h"
#include "OrderInfoPojo.h"
#include "OrderCallBackController.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


OrderInfoPojo parseOrderInfo(const std::string& str) {
    OrderInfoPojo orderInfo;
    std::map<std::string, std::string> paramMap;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, '&')) {
        auto pos = token.find('=');
        if (pos != std::string::npos) {
            std::string key = token.substr(0, pos);
            std::string value = token.substr(pos + 1);
            paramMap[key] = value;
        }
    }

    if (paramMap.find("orderId") != paramMap.end()) {
        orderInfo.setOrderId(paramMap["orderId"]);
    }
    if (paramMap.find("gameRole") != paramMap.end()) {
        orderInfo.setGameRole(paramMap["gameRole"]);
    }
    if (paramMap.find("gameArea") != paramMap.end()) {
        orderInfo.setGameArea(paramMap["gameArea"]);
    }
    if (paramMap.find("productName") != paramMap.end()) {
        orderInfo.setProductName(paramMap["productName"]);
    }
    if (paramMap.find("productDesc") != paramMap.end()) {
        orderInfo.setProductDesc(paramMap["productDesc"]);
    }
    if (paramMap.find("remark") != paramMap.end()) {
        orderInfo.setRemark(paramMap["remark"]);
    }
    if (paramMap.find("payTime") != paramMap.end()) {
        orderInfo.setPayTime(paramMap["payTime"]);
    }
    if (paramMap.find("amount") != paramMap.end()) {
        orderInfo.setAmount(paramMap["amount"]);
    }
    if (paramMap.find("payWay") != paramMap.end()) {
        orderInfo.setPayWay(paramMap["payWay"]);
    }
    if (paramMap.find("sign") != paramMap.end()) {
        orderInfo.setSign(paramMap["sign"]);
    }

    return orderInfo;
}

std::string urlControl(std::string urlPath, std::string data = "") {
    if (urlPath == "/juefeng/callback") {
        return OrderCallBackController::callBack(parseOrderInfo(data));
    }
    else if (urlPath == "/test/callback") {
        return TestSentCallBack::sendCallBackPost();
    }
    return "";
}

void handle_request(http::request<http::string_body>&& req, std::shared_ptr<tcp::socket> socket) {
    auto res = std::make_shared<http::response<http::string_body>>(http::status::ok, req.version());
    res->set(http::field::server, "Boost.Beast/1.0");

    // 处理不同方法的请求
    if (req.method() == http::verb::get) {
        res->set(http::field::content_type, "text/html");
        res->body() = "Get received";
    }
    else if (req.method() == http::verb::post) {
        res->set(http::field::content_type, "text/plain");
        res->body() = "Post received";
    }
    else {
        *res = http::response<http::string_body>{ http::status::bad_request, req.version() };
        res->set(http::field::content_type, "text/plain");
        res->body() = "Unsupported HTTP method";
    }
    std::cout << "获取到请求：" << req.target() << std::endl;
    std::string rsdata = urlControl(req.target(), req.body());
    if (rsdata != "") {
        res->body() = rsdata;
    }
    res->prepare_payload();

    http::async_write(*socket, *res, [res, socket](beast::error_code ec, std::size_t) {
        if (ec) {
            std::cerr << "Error sending response: " << ec.message() << std::endl;
        }
        else {
            socket->shutdown(tcp::socket::shutdown_send, ec);
            if (ec) {
                std::cerr << "Error shutting down socket: " << ec.message() << std::endl;
            }
        }
        });
}

void do_session(std::shared_ptr<tcp::socket> socket) {
    auto buffer = std::make_shared<beast::flat_buffer>();
    auto req = std::make_shared<http::request<http::string_body>>();

    http::async_read(*socket, *buffer, *req, [socket, buffer, req](beast::error_code ec, std::size_t) {
        if (!ec) {
            handle_request(std::move(*req), socket);
        }
        else {
            std::cerr << "Error reading request: " << ec.message() << std::endl;
            socket->shutdown(tcp::socket::shutdown_send, ec);
        }
        });
}

void do_accept(tcp::acceptor& acceptor, net::thread_pool& pool) {
    acceptor.async_accept(net::make_strand(pool), [&](beast::error_code ec, tcp::socket socket) {
        if (!ec) {
            do_session(std::make_shared<tcp::socket>(std::move(socket)));
        }
        else {
            std::cerr << "Error accepting connection: " << ec.message() << std::endl;
        }
        do_accept(acceptor, pool);
        });
}

void setUnbuffered(std::ostream& os) {
    os.setf(std::ios::unitbuf);
}

int main() {
    try {
        setUnbuffered(std::cout);
        std::setvbuf(stdout, nullptr, _IONBF, 0);
        const unsigned int num_threads = std::thread::hardware_concurrency();
        net::io_context ioc;
        net::thread_pool pool(num_threads);
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));
        do_accept(acceptor, pool);

        std::cout << "服务器正在监听" << std::endl;
        ioc.run();
        pool.join();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}