#include <iostream>

// key   - уникальное значение
// value - данные, которые могут повторяться

template <typename key, typename value> class CAVLTree
{
  public:
    CAVLTree(key key);

    void addNode()
    {
    }

    void delNode()
    {
    }

  private:
    key m_key;
    value m_value;

    int m_balance_factor;

    std::unique_ptr<CAVLTree> m_right;
    std::unique_ptr<CAVLTree> m_left;
};

template <typename key, typename value> CAVLTree<key, value>::CAVLTree(key key)
{
    m_key = key;
    m_balance_factor = 0;

    m_left = nullptr;
    m_right = nullptr;
}

template <typename key, typename value> class CDictionary
{
  public:
    CDictionary();

    value &operator[](const key &key)
    {
    }

    bool empty() const
    {
    }

    int size() const
    {
    }

    void clear()
    {
    }

    value erase(key &key)
    {
    }
    value find(key &key)
    {
    }

    bool contains(key &key)
    {
    }
};

template <typename key, typename value> CDictionary<key, value>::CDictionary()
{
}

int main()
{
    return 0;
}