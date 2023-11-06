#ifndef CJSON_PERSON_LOADER_FACTORY_HPP
#define CJSON_PERSON_LOADER_FACTORY_HPP

#include <iostream>

#include "CJSONLoader.hpp"
#include "CAbstractPersonLoaderFactory.hpp"

class CJSONPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override;

    bool isMatch(std::string path) override;
};

#endif // CJSON_PERSON_LOADER_FACTORY_HPP