#include <fstream>
#include <iostream>
#include <list>

#include "nlohmann/json.hpp"
#include "pugixml/pugixml.hpp"

using std::list;
using std::string;

class CPerson
{
  public:
    CPerson(string first_name, string last_name, int age);

    // Getters
    string getFirstName()
    {
        return m_first_name;
    }

    string getLastName()
    {
        return m_last_name;
    }

    int getAge()
    {
        return m_age;
    }

  private:
    string m_first_name;
    string m_last_name;
    int m_age;
};

CPerson::CPerson(string first_name, string last_name, int age)
{
    m_first_name = first_name;
    m_last_name = last_name;
    m_age = age;
}

class CAbstractPersonLoader
{
  public:
    virtual list<CPerson> load(string path) = 0;
};

class CJSONLoader : public CAbstractPersonLoader
{
  public:
    list<CPerson> load(string path) override
    {
        list<CPerson> people;
        m_current_path = path;

        // Вывод информации из потока файла и парсинг в json_data
        std::ifstream json_file_stream(m_current_path);

        nlohmann::json json_data = nlohmann::json::parse(json_file_stream);
        json_file_stream.close();

        // Цикл десереализации файла в объекты людей
        if (json_data.is_array())
        {
            for (const auto &person : json_data)
            {
                std::string temp_first_name;
                std::string temp_last_name;
                unsigned short temp_age = 0;

                if (person.find("_first_name") != person.end())
                {
                    std::string first_name = person["_first_name"];
                    temp_first_name = first_name;
                }

                if (person.find("_last_name") != person.end())
                {
                    std::string last_name = person["_last_name"];
                    temp_last_name = last_name;
                }

                if (person.find("Age") != person.end())
                {
                    unsigned short age = person["Age"];
                    temp_age = age;
                }

                // Добавление в конец списка нового объекта
                people.push_back(CPerson(temp_first_name, temp_last_name, temp_age));
            }
        }
        else
        {
            std::cerr << "JSON isn't contain a part of information!" << std::endl;
        }

        return people;
    }

    list<CPerson> reload()
    {
        list<CPerson> people;
        people = load(m_current_path);

        return people;
    }

  private:
    string m_current_path;
};

class CXMLLoader : public CAbstractPersonLoader
{
  public:
    list<CPerson> load(string path) override
    {
        list<CPerson> people;
        m_current_path = path;

        pugi::xml_document xml_doc;

        if (xml_doc.load_file(m_current_path.c_str()))
        {
            pugi::xml_node root = xml_doc.child("people");

            for (pugi::xml_node person = root.child("person"); person; person = person.next_sibling("person"))
            {
                std::string first_name;
                std::string last_name;
                unsigned short age = 0;

                pugi::xml_node first_name_node = person.child("_first_name");
                if (first_name_node)
                {
                    first_name = first_name_node.text().as_string();
                }

                pugi::xml_node last_name_node = person.child("_last_name");
                if (last_name_node)
                {
                    last_name = last_name_node.text().as_string();
                }

                pugi::xml_node age_node = person.child("age");
                if (age_node)
                {
                    age = age_node.text().as_int();
                }

                people.push_back(CPerson(first_name, last_name, age));
            }
        }
        else
        {
            std::cerr << "Failed to load XML document!" << std::endl;
        }

        return people;
    }

    list<CPerson> reload()
    {
        list<CPerson> people;
        people = load(m_current_path);

        return people;
    }

  private:
    string m_current_path;
};

class CAbstractPersonLoaderFactory
{
  public:
    virtual CAbstractPersonLoader *createLoader() = 0;
    virtual bool isMatch(string path) = 0;
};

class CJSONPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override
    {
        return new CJSONLoader();
    }

    bool isMatch(string path) override
    {
        string ext = "json";

        size_t point_position = path.rfind('.');

        if (point_position == std::string::npos)
        {
            return false;
        }

        std::string file_ext = path.substr(point_position + 1);

        return std::equal(file_ext.rbegin(), file_ext.rend(), ext.rbegin(), ext.rend(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    }
};

class CXMLPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override
    {
        return new CXMLLoader();
    }

    bool isMatch(string path) override
    {
        string ext = "xml";

        size_t point_position = path.rfind('.');

        if (point_position == std::string::npos)
        {
            return false;
        }

        std::string file_ext = path.substr(point_position + 1);

        return std::equal(file_ext.rbegin(), file_ext.rend(), ext.rbegin(), ext.rend(),
                          [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    }
};

int main()
{
    CJSONPersonLoaderFactory json_people_loader_factory;

    std::cout << "----JSON LF----" << std::endl;

    if (json_people_loader_factory.isMatch("Person.xml"))
    {
        CAbstractPersonLoader *people_loader = json_people_loader_factory.createLoader();

        list<CPerson> people = people_loader->load("Person.xml");

        for (CPerson &person : people)
        {
            std::cout << person.getFirstName() << " " << person.getLastName() << " is " << person.getAge()
                      << " years old." << std::endl;
        }
    }
    else
    {
        std::cerr << "File extension isn't match!" << std::endl;
    };

    CXMLPersonLoaderFactory xml_people_loader_factory;

    std::cout << "\n----XML LF----" << std::endl;

    if (xml_people_loader_factory.isMatch("Person.xml"))
    {
        CAbstractPersonLoader *people_loader = xml_people_loader_factory.createLoader();

        list<CPerson> people = people_loader->load("Person.xml");

        for (CPerson &person : people)
        {
            std::cout << person.getFirstName() << " " << person.getLastName() << " is " << person.getAge()
                      << " years old." << std::endl;
        }
    }
    else
    {
        std::cerr << "File extension isn't match!" << std::endl;
    };

    return 0;
}