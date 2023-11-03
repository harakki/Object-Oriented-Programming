#include <iostream>

using std::string;

class CPerson
{
  public:
    CPerson(string first_name, string last_name, int age);

    // Getters
    string getFirstName()
    {
        return m_first_name;
    }

    string getLastName()
    {
        return m_last_name;
    }

    int getAge()
    {
        return m_age;
    }

  private:
    string m_first_name;
    string m_last_name;
    int m_age;
};

CPerson::CPerson(string first_name, string last_name, int age)
{
    m_first_name = first_name;
    m_last_name = last_name;
    m_age = age;
}

class CAbstractPersonLoader
{
  public:
    virtual CPerson load(string path) = 0;
};

class CJSONLoader : public CAbstractPersonLoader
{
  public:
    CPerson load(string path) override
    {
    }

    CPerson reload(){};

  private:
    string m_current_path;
};

class CXMLLoader : public CAbstractPersonLoader
{
  public:
    CPerson load(string path) override
    {
    }

    CPerson reload(){};

  private:
    string m_current_path;
};

class CAbstractPersonLoaderFactory
{
  public:
    virtual CAbstractPersonLoader *createLoader() = 0;
    virtual bool isMatch(string path) = 0;
};

class CJSONPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override
    {
    }

    bool isMatch(string path) override
    {
    }
};

class CXMLPersonLoaderFactory : public CAbstractPersonLoaderFactory
{
  public:
    CAbstractPersonLoader *createLoader() override
    {
    }

    bool isMatch(string path) override
    {
    }
};

int main()
{
    return 0;
}