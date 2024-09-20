#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>

class LibcurlHttpHelper
{
public:
	static std::string sendHttpPost(std::string url, std::string postDATA, std::string headerList = "");
	static std::string sendHttpGet(std::string url);
	static std::string urlEncode(std::string param);
private:
	static size_t  req_reply(void* ptr, size_t size, size_t nmemb, void* stream);
	static CURLcode curl_get_req(const std::string& url, std::string& response);
	static CURLcode curl_post_req(const std::string& url, const std::string& postParams, std::string& response, std::string headerList = "");
};