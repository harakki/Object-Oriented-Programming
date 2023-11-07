#include "CRomanNumber.hpp"

int CRomanNumber::getDecimalNumber()
{
    return m_number;
}

std::string CRomanNumber::getRomanNumber()
{
    return convertToRoman(m_number);
}

CRomanNumber CRomanNumber::operator+(const CRomanNumber &roman_number) const
{
    int temp = m_number + roman_number.m_number;
    return CRomanNumber(permissionForOperation(temp));
}

CRomanNumber CRomanNumber::operator-(const CRomanNumber &roman_number) const
{
    int temp = m_number - roman_number.m_number;
    return CRomanNumber(permissionForOperation(temp));
}

CRomanNumber CRomanNumber::operator*(const CRomanNumber &roman_number) const
{
    int temp = m_number * roman_number.m_number;
    return CRomanNumber(permissionForOperation(temp));
}

CRomanNumber CRomanNumber::operator/(const CRomanNumber &roman_number) const
{
    int temp = m_number / roman_number.m_number;
    return CRomanNumber(permissionForOperation(temp));
}

bool CRomanNumber::operator==(const CRomanNumber &roman_number) const
{
    return m_number == roman_number.m_number;
}

bool CRomanNumber::operator!=(const CRomanNumber &roman_number) const
{
    return m_number != roman_number.m_number;
}

bool CRomanNumber::operator>(const CRomanNumber &roman_number) const
{
    return m_number > roman_number.m_number;
}

bool CRomanNumber::operator<(const CRomanNumber &roman_number) const
{
    return m_number < roman_number.m_number;
}

bool CRomanNumber::operator>=(const CRomanNumber &roman_number) const
{
    return m_number >= roman_number.m_number;
}

bool CRomanNumber::operator<=(const CRomanNumber &roman_number) const
{
    return m_number <= roman_number.m_number;
}

std::ostream &operator<<(std::ostream &out, const CRomanNumber &roman_number)
{
    return out << roman_number.convertToRoman(roman_number.m_number);
}

std::string CRomanNumber::convertToRoman(unsigned short decimal_number)
{
    std::string conv_result;

    // Словарь соответствий римских и десятичных чисел
    std::map<unsigned short, std::string> roman_digits = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
                                                          {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
                                                          {5, "V"},    {4, "IV"},   {1, "I"}};

    for (auto it = roman_digits.rbegin(); it != roman_digits.rend(); ++it)
    {
        while (decimal_number >= it->first)
        {
            conv_result += it->second;
            decimal_number -= it->first;
        }
    }

    return conv_result;
}

unsigned short CRomanNumber::permissionForOperation(int decimal_number)
{
    if (decimal_number < 1 || decimal_number > 3999)
    {
        throw CRomanNumberException("The result is out of the range of acceptable values!");
    }
    else
    {
        return decimal_number;
    }
}

CRomanNumber::CRomanNumber()
{
    m_number = 1;
};

CRomanNumber::CRomanNumber(unsigned short input_number)
{
    m_number = permissionForOperation(input_number);
};

CRomanNumber::CRomanNumber(const CRomanNumber &copy)
{
    m_number = copy.m_number;
};