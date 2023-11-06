#include <iostream>

// key   - уникальное значение
// value - данные, которые могут повторяться

class CAVLTree
{
  public:
    void tree_avl_add(int data)
    {
        tree_avl_add_internal(m_root, data);
    }

  private:
    struct Node
    {
        int data;

        int balance_factor;

        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(int val) : data(val), balance_factor(0), left(nullptr), right(nullptr)
        {
        }
    };

    std::unique_ptr<Node> m_root;
    int m_growth;

    void tree_avl_add_internal(std::unique_ptr<Node> &node, int data)
    {
        if (node == nullptr)
        {
            node = std::make_unique<Node>(data);
            m_growth = true;
        }
        else if (node->data > data)
        {
            tree_avl_add_internal(node->left, data);

            if (m_growth)
            {
                if (node->balance_factor > 0)
                {
                    node->balance_factor = 0;
                    m_growth = false;
                }
                else if (node->balance_factor == 0)
                {
                    node->balance_factor = -1;
                    m_growth = true;
                }
                else
                {
                    if (node->left->balance_factor < 0)
                    {
                        tree_avl_rotate_LL(node);
                        m_growth = false;
                    }
                    else
                    {
                        tree_avl_rotate_LR(node);
                        m_growth = false;
                    }
                }
            }
        }
        else if (node->data < data)
        {
            tree_avl_add_internal(node->right, data);

            if (m_growth)
            {
                if (node->balance_factor < 0)
                {
                    node->balance_factor = 0;
                    m_growth = false;
                }
                else if (node->balance_factor == 0)
                {
                    node->balance_factor = 1;
                    m_growth = true;
                }
                else
                {
                    if (node->right->balance_factor > 0)
                    {
                        tree_avl_rotate_RR(node);
                        m_growth = false;
                    }
                    else
                    {
                        tree_avl_rotate_RL(node);
                        m_growth = false;
                    }
                }
            }
        }
        else
        {
            // Вершина уже в дереве
        }
    }

    void tree_avl_rotate_LL(std::unique_ptr<Node> &node)
    {
        std::unique_ptr<Node> new_root = std::move(node->left);
        node->left = std::move(new_root->right);
        new_root->right = std::move(node);
        node = std::move(new_root);

        node->right->balance_factor = 0;
        node->balance_factor = 0;
    }

    void tree_avl_rotate_RR(std::unique_ptr<Node> &node)
    {
        std::unique_ptr<Node> new_root = std::move(node->right);
        node->right = std::move(new_root->left);
        new_root->left = std::move(node);
        node = std::move(new_root);

        node->left->balance_factor = 0;
        node->balance_factor = 0;
    }

    void tree_avl_rotate_LR(std::unique_ptr<Node> &node)
    {
        tree_avl_rotate_RR(node->left);
        tree_avl_rotate_LL(node);
    }

    void tree_avl_rotate_RL(std::unique_ptr<Node> &node)
    {
        tree_avl_rotate_LL(node->right);
        tree_avl_rotate_RR(node);
    }
};

//template <typename key, typename value> class CDictionary /*: protected CAVLTree*/
//{
//  public:
//    CDictionary();
//
//    value &operator[](const key &key)
//    {
//    }
//
//    bool empty() const
//    {
//    }
//
//    int size() const
//    {
//    }
//
//    void clear()
//    {
//    }
//
//    value erase(key &key)
//    {
//    }
//    value find(key &key)
//    {
//    }
//
//    bool contains(key &key)
//    {
//    }
//};
//
//template <typename key, typename value> CDictionary<key, value>::CDictionary()
//{
//}

int main()
{
    return 0;
}