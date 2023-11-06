#include <iostream>
#include <stack>

// key   - уникальное значение
// value - данные, которые могут повторяться

using std::unique_ptr;

template <typename key>
concept comparable = requires(key item) { item < item; };

template <comparable key, typename value> class CDictionary
{
  public:
    CDictionary();

    value &operator[](const key &key)
    {
        return getValue(root, key);
    }

    bool empty() const
    {
        return m_count == 0;
    }

    int size() const
    {
        return m_count;
    }

    void clear()
    {
        deleteAllVertexes(root);
        m_count = 0;
    }

    value erase(const key &key)
    {
        value value;
        deleteVertex(root, key, value);
        return value;
    }

    value find(const key &key)
    {
        return findValue(root, key);
    }

    bool contains(const key &key)
    {
        return containsKey(root, key);
    }

    class CIterator
    {
      public:
        CIterator(CDictionary<key, value> &dictionary) : dictionary(dictionary)
        {
            // Инициализация итератора
            current = dictionary.root.get();

            // Перемещение влево до самого левого узла
            pushLeftNodes(current);
        }

        // Операторы для перемещения итератора
        CIterator &operator++()
        {
            if (!stack.empty() || current)
            {
                if (current->m_right)
                {
                    current = std::move(current->m_right.get());

                    while (current && current->m_left)
                    {
                        pushLeftNodes(current);
                    }
                }
                else
                {
                    if (!stack.empty())
                    {
                        current = stack.top();
                        stack.pop();
                    }
                    else
                    {
                        current = nullptr;
                    }
                }
            }

            return *this;
        }

        bool operator!=(const CIterator &other) const
        {
            return current != other.current;
        }

        // Оператор доступа к значению
        value &operator*()
        {
            return current->m_value;
        }

      private:
        CDictionary<key, value> &dictionary;
        typename CDictionary<key, value>::Tree *current;
        std::stack<typename CDictionary<key, value>::Tree *> stack;

        void pushLeftNodes(typename CDictionary<key, value>::Tree *node)
        {
            while (node != nullptr)
            {
                stack.push(node);
                node = std::move(node->m_left.get());
            }
        }
    };

    // Методы для получения начального итератора и итератора конца
    CIterator begin()
    {
        return CIterator(*this);
    }

    CIterator end()
    {
        return CIterator(*this);
    }

  protected:
    struct Tree
    {
        key m_key;
        value m_value;

        int m_height;

        unique_ptr<Tree> m_left;
        unique_ptr<Tree> m_right;

        Tree(const key &key, const value &value)
        {
            m_key = key;
            m_value = value;

            m_height = 1;

            m_left = nullptr;
            m_right = nullptr;
        }
    };

    int m_count;
    unique_ptr<Tree> root;

  private:
    int getHeight(unique_ptr<Tree> &node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->m_height;
    }

    int getBalanceFactor(unique_ptr<Tree> &node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->m_left) - getHeight(node->m_right);
    }

    void fixHeight(unique_ptr<Tree> &node)
    {
        if (node != nullptr)
        {
            node->m_height = 1 + std::max(getHeight(node->m_left), getHeight(node->m_right));
        }
    }

    void rotateLeft(unique_ptr<Tree> &node)
    {
        unique_ptr<Tree> new_root = std::move(node->m_right);
        node->m_right = std::move(new_root->m_left);
        new_root->m_left = std::move(node);
        fixHeight(new_root);
        node = std::move(new_root);
    }

    void rotateRight(unique_ptr<Tree> &node)
    {
        unique_ptr<Tree> new_root = std::move(node->m_left);
        node->m_left = std::move(new_root->m_right);
        new_root->m_right = std::move(node);
        fixHeight(new_root);
        node = std::move(new_root);
    }

    void balance(unique_ptr<Tree> &node)
    {
        if (node != nullptr)
        {
            fixHeight(node);
            int balance_factor = getBalanceFactor(node);

            if (balance_factor > 1)
            {
                if (getBalanceFactor(node->m_left) < 0)
                {
                    rotateLeft(node->m_left);
                }
                rotateRight(node);
            }

            else if (balance_factor < -1)
            {
                if (getBalanceFactor(node->m_right) > 0)
                {
                    rotateRight(node->m_right);
                }
                rotateLeft(node);
            }
        }
    };

    value &getValue(unique_ptr<Tree> &node, const key &key)
    {
        if (node == nullptr)
        {
            node = make_unique<Tree>(key, value());
            m_count++;
        }

        else if (key < node->m_key)
            return getValue(node->m_left, key);

        else if (key > node->m_key)
            return getValue(node->m_right, key);

        return node->m_value;
    }

    unique_ptr<Tree> &getLeftmost(unique_ptr<Tree> &node)
    {
        if (node && node->m_left)
            return getLeftmost(node->m_left);

        return node;
    }

    void deleteVertex(unique_ptr<Tree> &node, const key &key, value &value)
    {
        if (!node)
        {
            return;
        }

        if (key < node->m_key)
            deleteVertex(node->m_left, key, value);

        else if (key > node->m_key)
            deleteVertex(node->m_right, key, value);

        else
        {
            value = node->m_value;

            if (!node->m_left && !node->m_right)
                node.reset();

            else if (node->m_left && !node->m_right)
                node = std::move(node->m_left);

            else if (!node->m_left && node->m_right)
                node = std::move(node->m_right);

            else
            {
                unique_ptr<Tree> &leftmost = getLeftmost(node->m_right);
                leftmost->m_left = std::move(node->m_left);
                leftmost->m_right = std::move(node->m_right);

                node = std::move(leftmost);
            }

            m_count--;
        }

        balance(node);
    }

    value &findValue(unique_ptr<Tree> &node, const key &key)
    {
        if (!node)
        {
            throw "Key is not found!";
        }

        if (key < node->m_key)
        {
            return findValue(node->m_left, key);
        }

        else if (key > node->m_key)
        {
            return findValue(node->m_right, key);
        }

        return node->m_value;
    }

    bool containsKey(unique_ptr<Tree> &node, const key &key)
    {
        if (!node)
        {
            return false;
        }

        if (key == node->m_key)
        {
            return true;
        }

        if (key < node->m_key)
        {
            return containsKey(node->m_left, key);
        }
        else
        {
            return containsKey(node->m_right, key);
        }
    }

    void deleteAllVertexes(unique_ptr<Tree> &node)
    {
        if (node != nullptr)
        {
            deleteAllVertexes(node->m_left);
            deleteAllVertexes(node->m_right);
            node.reset();
        }
    }
};

template <comparable key, typename value> CDictionary<key, value>::CDictionary()
{
    m_count = 0;
}

int main()
{
    CDictionary<int, std::string> dictionary;
    dictionary[1] = "One";
    dictionary[2] = "Two";
    dictionary[3] = "Three";
    dictionary[4] = "Four";

    for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}