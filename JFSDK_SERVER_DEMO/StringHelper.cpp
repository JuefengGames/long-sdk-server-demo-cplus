#include "StringHelper.h"
#include <string>
#include<stringapiset.h>
#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

std::string StringHelper::UTF8ToGBK(const std::string& strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
    WCHAR* wszGBK = new WCHAR[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    delete[]szGBK;
    delete[]wszGBK;
    return strTemp;
}

std::string StringHelper::calculateMD5(const std::string& input)
{
    boost::uuids::detail::md5 md5;

    // 输入数据
    md5.process_bytes(input.data(), input.size());

    // 获取结果
    boost::uuids::detail::md5::digest_type digest;
    md5.get_digest(digest);

    // 转换结果为十六进制字符串
    const auto charDigest = reinterpret_cast<const char*>(&digest);
    std::string md5string;
    boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(md5string));

    return md5string;
}
