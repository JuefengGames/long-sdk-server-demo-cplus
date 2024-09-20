#include "LibcurlHttpHelper.h"
#include <iostream>
#include <string>
#include "curl/curl.h"
#include "StringHelper.h"


#ifdef _DEBUG
#pragma comment(lib,"libcurl_a_debug.lib")
#else
#pragma comment(lib,"libcurl_a.lib")
#endif
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
using namespace std;

std::string LibcurlHttpHelper::sendHttpPost(std::string url, std::string postDATA, std::string headerList)
{
    string url_post0 = url;
    string paramsLogin0 = postDATA;
    string resPost0;
    auto res3 = curl_post_req(url_post0, paramsLogin0, resPost0, headerList);
    if (res3 == CURLE_OK)
    {
        cout << StringHelper::UTF8ToGBK(resPost0) << endl;
        return StringHelper::UTF8ToGBK(resPost0);
    }
    else {
        return "";
    }
}

std::string LibcurlHttpHelper::sendHttpGet(std::string url)
{
    string url_post0 = url;
    string resPost0;
    auto res3 = curl_get_req(url_post0, resPost0);
    if (res3 == CURLE_OK)
    {
        cout << StringHelper::UTF8ToGBK(resPost0) << endl;
        return StringHelper::UTF8ToGBK(resPost0);
    }
    else {
        return "";
    }
}

std::string LibcurlHttpHelper::urlEncode(std::string param)
{
    return curl_escape(param.c_str(), 0);
}

size_t LibcurlHttpHelper::req_reply(void* ptr, size_t size, size_t nmemb, void* stream)
{
    //��ע�͵�������Դ�ӡ��������cookie����Ϣ
    //cout << "----->reply" << endl;
    string* str = (string*)stream;
    //cout << *str << endl;
    (*str).append((char*)ptr, size * nmemb);
    return size * nmemb;
}

CURLcode LibcurlHttpHelper::curl_get_req(const std::string& url, std::string& response)
{
    // init curl  
    CURL* curl = curl_easy_init();
    // res code  
    CURLcode res;
    if (curl)
    {
        // set params  
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // url  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3); // set transport and time out time  
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
        // start req  
        res = curl_easy_perform(curl);
    }
    // release curl  
    curl_easy_cleanup(curl);
    return res;
}

CURLcode LibcurlHttpHelper::curl_post_req(const std::string& url, const std::string& postParams, std::string& response, std::string headerList)
{
    // curl��ʼ��  
    CURL* curl = curl_easy_init();
    // curl����ֵ 
    CURLcode res;
    if (curl)
    {
        // set params
        //����curl������ͷ
        struct curl_slist* header_list = NULL;
        header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
        header_list = curl_slist_append(header_list, "Content-Type:application/x-www-form-urlencoded; charset=UTF-8");
        header_list = curl_slist_append(header_list, headerList.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        //��������Ӧͷ����0�������� 1�������
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        //��������Ϊpost����
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        //���������URL��ַ
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //����post����Ĳ���
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());

        //����ssl��֤
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        //CURLOPT_VERBOSE��ֵΪ1ʱ������ʾ��ϸ�ĵ�����Ϣ
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

        //�������ݽ��պ�д�뺯��
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);

        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        //���ó�ʱʱ��
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

        // ����post����
        res = curl_easy_perform(curl);
    }
    //�ͷ�curl 
    curl_easy_cleanup(curl);
    return res;
}