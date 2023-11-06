#define CATCH_CONFIG_MAIN

#include "include/catch2/catch_amalgamated.hpp"

#include "../LAB6/src/classes/CAbstractPersonLoader.hpp"
#include "../LAB6/src/classes/CAbstractPersonLoaderFactory.hpp"
#include "../LAB6/src/classes/CJSONLoader.hpp"
#include "../LAB6/src/classes/CJSONPersonLoaderFactory.hpp"
#include "../LAB6/src/classes/CPerson.hpp"
#include "../LAB6/src/classes/CXMLLoader.hpp"
#include "../LAB6/src/classes/CXMLPersonLoaderFactory.hpp"

#include "../LAB6/src/classes/CJSONLoader.cpp"
#include "../LAB6/src/classes/CJSONPersonLoaderFactory.cpp"
#include "../LAB6/src/classes/CPerson.cpp"
#include "../LAB6/src/classes/CXMLLoader.cpp"
#include "../LAB6/src/classes/CXMLPersonLoaderFactory.cpp"

#include "../LAB6/include/pugixml/pugiconfig.hpp"
#include "../LAB6/include/pugixml/pugixml.cpp"
#include "../LAB6/include/pugixml/pugixml.hpp"

SCENARIO("Create loaders using Loader Factories", "[CPersonLoaderFactory]")
{
    GIVEN("Factories for JSON and XML:")
    {
        CJSONPersonLoaderFactory factory_json;
        CXMLPersonLoaderFactory factory_xml;

        WHEN("creating JSON loader")
        {
            CAbstractPersonLoader *loader = factory_json.createLoader();

            REQUIRE(loader != nullptr);

            CJSONLoader *json_loader = dynamic_cast<CJSONLoader *>(loader);
        }

        WHEN("object from factory is the part of JSON loader")
        {
            CAbstractPersonLoader *loader = factory_json.createLoader();
            CJSONLoader *json_loader = dynamic_cast<CJSONLoader *>(loader);

            REQUIRE(json_loader != nullptr);
        }

        WHEN("creating XML loader")
        {
            CAbstractPersonLoader *loader = factory_xml.createLoader();

            REQUIRE(loader != nullptr);
        }

        WHEN("object from factory is the part of XML loader")
        {
            CAbstractPersonLoader *loader = factory_xml.createLoader();
            CXMLLoader *xml_loader = dynamic_cast<CXMLLoader *>(loader);

            REQUIRE(xml_loader != nullptr);
        }
    }
}

SCENARIO("Checking the operation of the file extension verification function", "[CPersonLoaderFactory]")
{
    GIVEN("Names of files with extensions")
    {
        CJSONPersonLoaderFactory factory_json;
        CJSONPersonLoaderFactory factory_xml;

        std::string name_json = "file.json";
        std::string name_jmon = "file.jmon";
        std::string name_eptrts = "file.eptrts";

        std::string name_xml = "Person.xml";
        std::string name_xaml = "file.xaml";
        std::string name_fffee2 = "file.fffe2";

        std::string name_x = "file.x";
        std::string name = "file";
        std::string name_ = "file.";

        WHEN("JSON factory processed filenames")
        {
            REQUIRE(factory_json.isMatch(name_json));
            REQUIRE_FALSE(factory_json.isMatch(name_xml));
            REQUIRE_FALSE(factory_json.isMatch(name_jmon));
            REQUIRE_FALSE(factory_json.isMatch(name_eptrts));
            REQUIRE_FALSE(factory_json.isMatch(name_x));
            REQUIRE_FALSE(factory_json.isMatch(name));
            REQUIRE_FALSE(factory_json.isMatch(name_));
        }

        WHEN("XML factory processed filenames")
        {
            REQUIRE(factory_xml.isMatch(name_xml)); // ошибка библ. при REQ => false, а при REQ_F => !true
            REQUIRE_FALSE(factory_xml.isMatch(name_json));
            REQUIRE_FALSE(factory_xml.isMatch(name_jmon));
            REQUIRE_FALSE(factory_xml.isMatch(name_fffee2));
            REQUIRE_FALSE(factory_xml.isMatch(name_x));
            REQUIRE_FALSE(factory_xml.isMatch(name));
            REQUIRE_FALSE(factory_xml.isMatch(name_));
        }
    }
}

SCENARIO("Loading the file", "[CLoader]")
{
    GIVEN("Loader for JSON and XML files")
    {
        CJSONLoader json_loader = CJSONLoader();
        CXMLLoader xml_loader = CXMLLoader();

        WHEN("file isn't available for JSON loader")
        {
            REQUIRE_THROWS(json_loader.load("doesntexist.json"));
        }

        WHEN("file isn't available for XML loader")
        {
            REQUIRE_THROWS(xml_loader.load("doesntexist.xml"));
        }

        WHEN("file dosn't contain the row for JSON loader")
        {
            REQUIRE_THROWS(xml_loader.load("../LAB6-TESTS/test.json"));
        }

        WHEN("file dosn't contain the row for XML loader")
        {
            REQUIRE_THROWS(xml_loader.load("../LAB6-TESTS/test.xml"));
        }

        WHEN("function of JSON loader reads information from a file")
        {
            std::list<CPerson> people = json_loader.load("../LAB6/Person.json");

            // Итератор на первый элемент в списке
            std::list<CPerson>::iterator person = people.begin();

            std::string first_name = person->getFirstName();
            std::string last_name = person->getLastName();
            unsigned short age = person->getAge();

            REQUIRE(first_name == "Biba");
            REQUIRE(last_name == "Boba");
            REQUIRE(age == 20);
        }

        WHEN("function of JSON loader reads information from a file")
        {
            std::list<CPerson> people = xml_loader.load("../LAB6/Person.xml");

            std::list<CPerson>::iterator person = people.begin();

            std::string first_name = person->getFirstName();
            std::string last_name = person->getLastName();
            unsigned short age = person->getAge();

            REQUIRE(first_name == "Biba");
            REQUIRE(last_name == "Boba");
            REQUIRE(age == 20);
        }
    }
}

SCENARIO("Reloading the file", "[CLoader]")
{
    GIVEN("Reloaded person from JSON and XML files")
    {
        CJSONLoader json_loader = CJSONLoader();
        CXMLLoader xml_loader = CXMLLoader();

        json_loader.load("../LAB6/Person.json");
        xml_loader.load("../LAB6/Person.xml");

        std::list<CPerson> json_people = json_loader.reload();
        std::list<CPerson> xml_people = xml_loader.reload();

        std::list<CPerson>::iterator json_person = json_people.begin();
        std::list<CPerson>::iterator xml_person = xml_people.begin();

        WHEN("function of JSON loader reads information from reloaded a file")
        {
            std::string json_first_name = json_person->getFirstName();
            std::string json_last_name = json_person->getLastName();
            unsigned short json_age = json_person->getAge();

            REQUIRE(json_first_name == "Biba");
            REQUIRE(json_last_name == "Boba");
            REQUIRE(json_age == 20);
        }

        WHEN("function of XML loader reads information from reloaded a file")
        {
            std::string xml_first_name = xml_person->getFirstName();
            std::string xml_last_name = xml_person->getLastName();
            unsigned short xml_age = xml_person->getAge();

            REQUIRE(xml_first_name == "Biba");
            REQUIRE(xml_last_name == "Boba");
            REQUIRE(xml_age == 20);
        }
    }
}

SCENARIO("Person class functionality test", "[CPerson]")
{
    GIVEN("object \"person\", created with constructor")
    {
        CPerson person = CPerson("Lera", "Yazagit", 25);

        WHEN("getting first name")
        {
            REQUIRE(person.getFirstName() == "Lera");
        }

        WHEN("getting last name")
        {
            REQUIRE(person.getLastName() == "Yazagit");
        }

        WHEN("getting age")
        {
            REQUIRE(person.getAge() == 25);
        }
    }
}