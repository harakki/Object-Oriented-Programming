#include "CXMLLoader.hpp"

std::list<CPerson> CXMLLoader::load(std::string path)
{
    std::list<CPerson> people;
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
            else
            {
                throw "XML isn't contain a part of information!";
            }

            pugi::xml_node last_name_node = person.child("_last_name");
            if (last_name_node)
            {
                last_name = last_name_node.text().as_string();
            }
            else
            {
                throw "XML isn't contain a part of information!";
            }

            pugi::xml_node age_node = person.child("age");
            if (age_node)
            {
                age = age_node.text().as_int();
            }
            else
            {
                throw "XML isn't contain a part of information!";
            }

            people.push_back(CPerson(first_name, last_name, age));
        }
    }
    else
    {
         throw "Failed to load XML document!";
    }

    return people;
}

std::list<CPerson> CXMLLoader::reload()
{
    std::list<CPerson> people;
    people = load(m_current_path);

    return people;
}