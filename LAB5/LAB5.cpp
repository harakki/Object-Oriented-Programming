#include <iostream>
#include <map>
#include <stdexcept>

using std::string;

class CRomanNumber
{
  public:
    CRomanNumber();
    CRomanNumber(unsigned short input_number);
    CRomanNumber(const CRomanNumber &copy);

    CRomanNumber operator+(const CRomanNumber &roman_number) const
    {
        int temp = m_number + roman_number.m_number;
        return CRomanNumber(permissionForOperation(temp));
    }

    CRomanNumber operator-(const CRomanNumber &roman_number) const
    {
        int temp = m_number - roman_number.m_number;
        return CRomanNumber(permissionForOperation(temp));
    }

    CRomanNumber operator*(const CRomanNumber &roman_number) const
    {
        int temp = m_number * roman_number.m_number;
        return CRomanNumber(permissionForOperation(temp));
    }

    CRomanNumber operator/(const CRomanNumber &roman_number) const
    {
        int temp = m_number / roman_number.m_number;
        return CRomanNumber(permissionForOperation(temp));
    }

    bool operator==(const CRomanNumber &roman_number) const
    {
        return m_number == roman_number.m_number;
    }

    bool operator!=(const CRomanNumber &roman_number) const
    {
        return m_number != roman_number.m_number;
    }

    bool operator>(const CRomanNumber &roman_number) const
    {
        return m_number > roman_number.m_number;
    }

    bool operator<(const CRomanNumber &roman_number) const
    {
        return m_number < roman_number.m_number;
    }

    bool operator>=(const CRomanNumber &roman_number) const
    {
        return m_number >= roman_number.m_number;
    }

    bool operator<=(const CRomanNumber &roman_number) const
    {
        return m_number <= roman_number.m_number;
    }

    friend std::ostream &operator<<(std::ostream &out, const CRomanNumber &roman_number)
    {
        out << convertToRoman(roman_number.m_number);
        return out;
    }

  protected:
    static string convertToRoman(unsigned short decimal_number)
    {
        string conv_result;

        // Словарь соответствий римских и десятичных чисел
        std::map<unsigned short, std::string> roman_digits = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
            {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};

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

  private:
    unsigned short m_number;

    static unsigned short permissionForOperation(int decimal_number)
    {
        if (decimal_number < 1 || decimal_number > 3999)
        {
            // "Операция не разрешена."
            throw (int)EPERM;
        }
        else
        {
            return (unsigned short)decimal_number;
        }
    }
};

CRomanNumber::CRomanNumber()
{
    m_number = 1;
};

CRomanNumber::CRomanNumber(unsigned short input_number)
{
    m_number = input_number;
};

CRomanNumber::CRomanNumber(const CRomanNumber &copy)
{
    m_number = copy.m_number;
};

// class CException : public std::exception
// {
//   public:
//     virtual const char *what() noexcept = 0;
//
//   protected:
//     int getErrorCode()
//     {
//         return m_error_code;
//     }
//
//     void setErrorCode(int error_code)
//     {
//         m_error_code = error_code;
//     }
//
//   private:
//     int m_error_code;
// };

// class CRomanNumberException : public CException
// {
//   public:
//     CRomanNumberException(int error_code);
//
//     const char *what() noexcept override
//     {
//         string message;
//         if (getErrorCode() == EPERM)
//         {
//             message = "The result went beyond the range of acceptable numbers!";
//             std::cerr << "Error: " << message << std::endl;
//         }
//         else
//         {
//             message = "Unknown error";
//             std::cerr << "Error: " << message << std::endl;
//         }
//     }
// };
//
// CRomanNumberException::CRomanNumberException(int errorCode)
// {
//     setErrorCode(errorCode);
// }

int main()
{

    CRomanNumber romanNumb_700(700);
    CRomanNumber romanNumb_970(970);

    try
    {
        std::cout << (romanNumb_970 - romanNumb_700) << std::endl;
        std::cout << (romanNumb_700 - romanNumb_970) << std::endl;
        std::cout << (romanNumb_970 - romanNumb_700) << std::endl;
    }
    catch (const int &err_msg)
    {
        std::cerr << "ERR: " << err_msg << std::endl;
    }

    return 0;
}
