#include "CPerson.hpp"

std::string CPerson::getFirstName()
{
    return m_first_name;
}

std::string CPerson::getLastName()
{
    return m_last_name;
}

int CPerson::getAge()
{
    return m_age;
}

CPerson::CPerson(std::string first_name, std::string last_name, int age)
{
    m_first_name = first_name;
    m_last_name = last_name;
    m_age = age;
}