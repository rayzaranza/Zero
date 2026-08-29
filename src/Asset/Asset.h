#pragma once
#include <string>

namespace ZY
{
    class Asset
    {
    public:
        static std::string getFileContent(const std::string& path);
    };
}
