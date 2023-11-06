#ifndef CROMAN_NUMBER_HPP
#define CROMAN_NUMBER_HPP

#include "CRomanNumberException.hpp"

#include <map>

class CRomanNumber
{
  public:
    CRomanNumber();
    CRomanNumber(unsigned short input_number);
    CRomanNumber(const CRomanNumber &copy);

    int getDecimalNumber();

    std::string getRomanNumber();

    CRomanNumber operator+(const CRomanNumber &roman_number) const;

    CRomanNumber operator-(const CRomanNumber &roman_number) const;

    CRomanNumber operator*(const CRomanNumber &roman_number) const;

    CRomanNumber operator/(const CRomanNumber &roman_number) const;

    bool operator==(const CRomanNumber &roman_number) const;

    bool operator!=(const CRomanNumber &roman_number) const;

    bool operator>(const CRomanNumber &roman_number) const;

    bool operator<(const CRomanNumber &roman_number) const;

    bool operator>=(const CRomanNumber &roman_number) const;

    bool operator<=(const CRomanNumber &roman_number) const;

    friend std::ostream &operator<<(std::ostream &out, const CRomanNumber &roman_number);

  protected:
    static std::string convertToRoman(unsigned short decimal_number);

  private:
    unsigned short m_number;

    static unsigned short permissionForOperation(int decimal_number);
};

#endif // CROMAN_NUMBER_HPP