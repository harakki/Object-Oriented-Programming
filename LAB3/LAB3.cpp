#include <iostream>

//	key		- уникальное значение
//	value	- данные, которые могут повторяться

template <typename key, typename value> class CAVLTree
{
  public:
    // Конструктор класса
    CAVLTree(key key);

    // Геттеры и сеттеры

    // Функции класса
    CAVLTree *addNode()
    {
    }

  private:
    key m_key;
    value m_value;

    int m_height;

    std::unique_ptr<CAVLTree> m_right;
    std::unique_ptr<CAVLTree> m_left;
};

template <typename key, typename value> CAVLTree<key, value>::CAVLTree(key key)
{
    m_key = key;
    m_height = 0;

    m_left = nullptr;
    m_right = nullptr;
}

template <typename key, typename value> class CDictionary
{
  public:
    CDictionary();

  private:
};

template <typename key, typename value> CDictionary<key, value>::CDictionary()
{
}

int main()
{
    CAVLTree<int, int> tree(10);
}