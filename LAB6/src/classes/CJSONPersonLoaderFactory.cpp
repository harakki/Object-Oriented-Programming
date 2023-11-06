#include "CJSONPersonLoaderFactory.hpp"

CAbstractPersonLoader *CJSONPersonLoaderFactory::createLoader()
{
    return new CJSONLoader();
}

bool CJSONPersonLoaderFactory::isMatch(std::string path)
{
    std::string ext = "json";

    size_t point_position = path.rfind('.');

    if (point_position == std::string::npos)
    {
        return false;
    }

    std::string file_ext = path.substr(point_position + 1);

    return std::equal(file_ext.rbegin(), file_ext.rend(), ext.rbegin(), ext.rend(),
                      [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}