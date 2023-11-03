#include <iostream>

template <typename DATATYPE> class CRomanNumber
{
  public:
    CRomanNumber();
    CRomanNumber(unsigned short input_number);
    CRomanNumber(const CRomanNumber<DATATYPE> &copy);

    CRomanNumber operator+(const CRomanNumber &roman_number) const
    {
    }

    CRomanNumber operator-(const CRomanNumber &roman_number) const
    {
    }

    CRomanNumber operator*(const CRomanNumber &roman_number) const
    {
    }
    
    CRomanNumber operator/(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator==(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator!=(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator>(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator<(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator>=(const CRomanNumber &roman_number) const
    {
    }
    
    bool operator<=(const CRomanNumber &roman_number) const
    {
    }
    
    friend std::ostream &operator<<(std::ostream &out, const Point &point)
    {
    }

  private:
    DATATYPE m_number;
};

template <typename DATATYPE> CRomanNumber<DATATYPE>::CRomanNumber()
{
    m_number = 1;
};

CRomanNumber<unsigned short>::CRomanNumber(unsigned short input_number)
{
    m_number = input_number;
};

template <typename DATATYPE> CRomanNumber<DATATYPE>::CRomanNumber(const CRomanNumber<DATATYPE> &copy)
{
    m_number = copy.m_number;
};

class CException
{
};

class CRomanNumberException : public CException
{
};

int main()
{
    return 0;
}