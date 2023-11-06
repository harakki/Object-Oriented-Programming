#include "CXMLPersonLoaderFactory.hpp"

CAbstractPersonLoader *CXMLPersonLoaderFactory::createLoader()
{
    return new CXMLLoader();
}

bool CXMLPersonLoaderFactory::isMatch(std::string path)
{
    std::string ext = "xml";

    size_t point_position = path.rfind('.');

    if (point_position == std::string::npos)
    {
        return false;
    }

    std::string file_ext = path.substr(point_position + 1);

    return std::equal(file_ext.rbegin(), file_ext.rend(), ext.rbegin(), ext.rend(),
                      [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}