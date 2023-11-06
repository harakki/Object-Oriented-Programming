#ifndef CXML_PERSON_LOADER_FACTORY_HPP
#define CXML_PERSON_LOADER_FACTORY_HPP

#include <iostream>

#include "CAbstractPersonLoaderFactory.hpp"
#include "CXMLLoader.hpp"

class CXMLPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override;

    bool isMatch(std::string path) override;
};

#endif // CXML_PERSON_LOADER_FACTORY_HPP