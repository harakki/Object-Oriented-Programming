#ifndef CEXCEPTION_HPP
#define CEXCEPTION_HPP

#include <iostream>
#include <exception>

class CException : public std::exception
{
  public:
    virtual const char *what() const noexcept override;

  protected:
    std::string getErrorMsg();

    void setErrorMsg(const std::string & error_message);

  private:
    std::string m_error_message;
};

#endif // CEXCEPTION_HPP