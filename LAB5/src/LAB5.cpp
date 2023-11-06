#include <iostream>
#include <map>
#include <stdexcept>

#include "classes/CException.hpp"
#include "classes/CRomanNumber.hpp"
#include "classes/CRomanNumberException.hpp"

int main()
{
    CRomanNumber romanNumb_700(700);
    CRomanNumber romanNumb_970(970);

    try
    {
        std::cout << (romanNumb_970 - romanNumb_700) << std::endl;
    }
    catch (const CRomanNumberException &exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    try
    {
        std::cout << (romanNumb_700 - romanNumb_970) << std::endl;
    }
    catch (const CRomanNumberException &exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    try
    {
        std::cout << (romanNumb_970 - romanNumb_700) << std::endl;
    }
    catch (const CRomanNumberException &exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
    }

    return 0;
}
