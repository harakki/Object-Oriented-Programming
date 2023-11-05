#include <iostream>
#include <map>
#include <stdexcept>

using std::string;

class CException : public std::exception
{
  public:
    virtual const char *what() const noexcept override
    {
        return m_error_message.c_str();
    }

  protected:
    string getErrorMsg()
    {
        return m_error_message;
    }

    void setErrorMsg(const string &error_message)
    {
        m_error_message = error_message;
    }

  private:
    string m_error_message;
};

class CRomanNumberException : public CException
{
  public:
    CRomanNumberException(const string &errorMsg);
};

CRomanNumberException::CRomanNumberException(const string &errorMsg)
{
    setErrorMsg(errorMsg);
}

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
        return out << convertToRoman(roman_number.m_number);
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
            throw CRomanNumberException("The result is out of the range of acceptable values!");
        }
        else
        {
            return decimal_number;
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
