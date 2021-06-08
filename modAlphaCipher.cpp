#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "modAlphaCipher.h"
using namespace std;
std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
std::map <wchar_t, int> alphaNum;
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (int i = 0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
}
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring& str)
{
    std::vector<int> result;
    for(auto c:str) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty key");
    wstring output;
    std::locale loc("ru_RU.UTF-8");
    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            output += c;
        } else if (c >= L'а' && c <= L'я') {
            output += toupper(c, loc);
        } else {
            throw cipher_error("Invalid key");
        }
    }
    return output;
}
inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty Open Text");
    wstring output;
    std::locale loc("ru_RU.UTF-8");
    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            output += c;
        } else if (c >= L'а' && c <= L'я') {
            output += toupper(c, loc);
        } else {
            throw cipher_error("Invalid Open Text");
        }
    }
    return output;
}
inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & in)
{
    if (in.empty()) throw cipher_error("Empty Cipher Text");
    wstring output;
    std::locale loc("ru_RU.UTF-8");
    for (wchar_t c : in) {
        if (c >= L'А' && c <= L'Я') {
            output += c;
        } else {
            throw cipher_error("Invalid Cipher Text");
        }
    }
    return output;
}
