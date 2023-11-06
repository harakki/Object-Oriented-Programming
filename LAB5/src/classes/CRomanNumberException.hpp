#ifndef CROMAN_NUMBER_EXCEPTION_HPP
#define CROMAN_NUMBER_EXCEPTION_HPP

#include "CException.hpp"

class CRomanNumberException : public CException
{
  public:
    CRomanNumberException(const std::string &errorMsg);
};

#endif // CROMAN_NUMBER_EXCEPTION_HPP