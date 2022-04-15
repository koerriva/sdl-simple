#pragma once

#include <string>
#include <vector>

class Base64
{
private:
    /* data */
public:
    Base64(){};
    ~Base64(){};

    std::string encode(std::string in,size_t len);
    std::vector<int> decode(std::string in,size_t* outlen);
};
