#ifndef CJSON_LOADER_HPP
#define CJSON_LOADER_HPP

#include <iostream>
#include <fstream>
#include <list>

#include "../../include/nlohmann/json.hpp"
#include "CAbstractPersonLoader.hpp"

class CJSONLoader : public CAbstractPersonLoader
{
  public:
    std::list<CPerson> load(std::string path) override;

    std::list<CPerson> reload();

  private:
    std::string m_current_path;
};

#endif // CJSON_LOADER_HPP