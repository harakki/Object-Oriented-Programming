#include "CJSONLoader.hpp"

std::list<CPerson> CJSONLoader::load(std::string path)
{
    std::list<CPerson> people;
    m_current_path = path;

    // Вывод информации из потока файла и парсинг в json_data
    std::ifstream json_file_stream(m_current_path);

    if (json_file_stream.is_open())
    {
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
            throw "JSON isn't contain a part of information!";
        }
    }
    else
    {
        json_file_stream.close();

        throw "File isn't available!";
    }

    return people;
}

std::list<CPerson> CJSONLoader::reload()
{
    std::list<CPerson> people;
    people = load(m_current_path);

    return people;
}