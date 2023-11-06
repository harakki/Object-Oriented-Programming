#include "CException.hpp"

const char *CException::what() const noexcept
{
    return m_error_message.c_str();
}

std::string CException::getErrorMsg()
{
    return m_error_message;
}

void CException::setErrorMsg(const std::string &error_message)
{
    m_error_message = error_message;
}