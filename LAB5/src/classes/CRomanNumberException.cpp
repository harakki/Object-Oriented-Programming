#include "CRomanNumberException.hpp"

CRomanNumberException::CRomanNumberException(const std::string &errorMsg)
{
    setErrorMsg(errorMsg);
}