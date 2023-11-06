#ifndef CPERSON_HPP
#define CPERSON_HPP

#include <iostream>

class CPerson
{
  public:
    CPerson(std::string first_name, std::string last_name, int age);

    std::string getFirstName();

    std::string getLastName();

    int getAge();

  private:
    std::string m_first_name;
    std::string m_last_name;
    int m_age;
};

#endif // CPERSON_HPP