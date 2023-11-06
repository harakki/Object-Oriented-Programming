#ifndef CABSTRACT_PERSON_LOADER_HPP
#define CABSTRACT_PERSON_LOADER_HPP

#include "CPerson.hpp"
#include <list>

class CAbstractPersonLoader
{
  public:
    virtual std::list<CPerson> load(std::string path) = 0;
};

#endif // CABSTRACT_PERSON_LOADER_HPP