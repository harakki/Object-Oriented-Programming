#include <iostream>
#include <list>

#include "classes/CJSONLoader.hpp"
#include "classes/CJSONPersonLoaderFactory.hpp"
#include "classes/CXMLLoader.hpp"
#include "classes/CXMLPersonLoaderFactory.hpp"

int main()
{
    CJSONPersonLoaderFactory json_people_loader_factory;

    std::cout << "----JSON LF---- " << json_people_loader_factory.isMatch("Person.json") << std::endl;

    if (json_people_loader_factory.isMatch("Person.json"))
    {
        CAbstractPersonLoader *people_loader = json_people_loader_factory.createLoader();

        std::list<CPerson> people = people_loader->load("Person.json");

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

    std::cout << "\n----XML LF---- " << xml_people_loader_factory.isMatch("Person.xml") << std::endl;

    if (xml_people_loader_factory.isMatch("Person.xml"))
    {
        CAbstractPersonLoader *people_loader = xml_people_loader_factory.createLoader();

        std::list<CPerson> people = people_loader->load("Person.xml");

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