#ifndef CABSTRACT_PERSON_LOADER_FACTORY_HPP
#define CABSTRACT_PERSON_LOADER_FACTORY_HPP

#include <iostream>
#include "CAbstractPersonLoader.hpp"

class CAbstractPersonLoaderFactory
{
  public:
    virtual CAbstractPersonLoader *createLoader() = 0;
    virtual bool isMatch(std::string path) = 0;
};

#endif // CABSTRACT_PERSON_LOADER_FACTORY_HPP