#pragma once
#include <string>
#include <map>
class shifr
{
public:
    std::string encrypt(std::string in, const int key);
    std::string decrypt(std::string in, const int key);
private:
    void isInvalidKey(std::string in, const int key);
    void isInvalidMsg(std::string in, const int key);
};
class encryptException: public std::invalid_argument
{
public:
    explicit encryptException (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit encryptException (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
