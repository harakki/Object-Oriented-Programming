#ifndef CXML_LOADER_HPP
#define CXML_LOADER_HPP

#include <iostream>
#include <list>

#include "../../include/pugixml/pugixml.hpp"
#include "CAbstractPersonLoader.hpp"

class CXMLLoader : public CAbstractPersonLoader
{
  public:
    std::list<CPerson> load(std::string path);

    std::list<CPerson> reload();

  private:
    std::string m_current_path;
};

#endif // CXML_LOADER_HPP