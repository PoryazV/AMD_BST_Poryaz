#include <iostream>
#include <stdexcept>

class HeapTree
{
private:
    //Сам узел, состоит из хранимой информации (числа) и ссылок на левый и правый узлы
    struct Node
    {
        int data;
        Node* left;
        Node* right;
        Node(int data_){data = data_; left = nullptr; right = nullptr;}
    };
    //В самом дереве только корневой узел, от него можно найти все остальные
    Node* rootNode;
public:
    //При создании в дереве нет корневого узла. Он добавляется с первый добавленным числом
    HeapTree(){rootNode = nullptr;}
    //Метод получения ссылки корневой узел
    Node* root()
    {
        return rootNode;
    }
    //Метод проверки наличия узла
    bool has(int data)
    {
        if(rootNode == nullptr)
        {
            return false;
        }
        Node* node = rootNode;
        while(data!=node->data)
        {
            if(data<node->data)
            {
                if(node->left == nullptr)
                {
                    return false;
                }
                node = node->left;
            }
            else if(data>node->data)
            {
                if(node->right == nullptr)
                {
                    return false;
                }
                node = node->right;
            }
        }
        return true;
    }
    //Метод получения ссылки на необходимый узел
    Node* find(int data)
    {
        if(rootNode == nullptr)
        {
            throw std::runtime_error("No such data in this heap tree\n");
        }
        Node* node = rootNode;
        while(data!=node->data)
        {
            if(data<node->data)
            {
                if(node->left == nullptr)
                {
                    throw std::runtime_error("No such data in this heap tree\n");
                }
                node = node->left;
            }
            else if(data>node->data)
            {
                if(node->right == nullptr)
                {
                    throw std::runtime_error("No such data in this heap tree\n");
                }
                node = node->right;
            }
        }
        return node;
    }
    //Метод получения минимального значения в дереве
    int min()
    {
        if(rootNode == nullptr)
        {
            throw std::runtime_error("No data in this heap tree\n");
        }
        Node* node = rootNode;
        while(node->left!=nullptr)
        {
            node = node->left;
        }
        return node->data;
    }
    //Метод получения максимального значения в дереве
    int max()
    {
        if(rootNode == nullptr)
        {
            throw std::runtime_error("No data in this heap tree\n");
        }
        Node* node = rootNode;
        while(node->right!=nullptr)
        {
            node = node->right;
        }
        return node->data;
    }
    //Метод добавления узла
    void add(int data)
    {
        bool f = true;
        if(rootNode == nullptr)
        {
            rootNode = new Node(data);
            f = false;
        }
        else
        {
            Node* node = rootNode;
            while(data!=node->data)
            {
                if(data<node->data)
                {
                    if(node->left == nullptr)
                    {
                        node->left = new Node(data);
                        f = false;
                        break;
                    }
                    node = node->left;
                }
                else if(data>node->data)
                {
                    if(node->right == nullptr)
                    {
                        node->right = new Node(data);
                        f = false;
                        break;
                    }
                    node = node->right;
                }
            }
        }
        if(f)
        {
            throw std::runtime_error("Data already in this BST\n");
        }
    }
    //Метод удаления узла
    void remove(int data)
    {
        if(!has(data))
        {
            throw std::runtime_error("No such data in this BST\n");
        }
        Node* node = find(data);
        if(node->left==nullptr && node->right==nullptr)
        {
            Node* node_ = rootNode;
            while(node_->left!=node && node_->right!=node)
            {
                if(data<node_->data)
                {
                    node_=node_->left;
                }
                else
                {
                    node_=node_->right;
                }
            }
            if(node_->left==node)
            {
                node_->left = nullptr;
            }
            else
            {
                node_->right = nullptr;
            }
            delete node;
        }
        else if(node->left!=nullptr && node->right==nullptr)
        {
            Node* nodeD = node->left;
            *node = *nodeD;
            delete nodeD;
        }
        else if(node->left==nullptr && node->right!=nullptr)
        {
            Node* nodeD = node->right;
            *node = *nodeD;
            delete nodeD;
        }
        else if(node->left!=nullptr && node->right!=nullptr)
        {
            Node* nodeL = node->left;
            Node* node_ = node->right;
            if(node_->left==nullptr)
            {
                Node* nodeD = node_;
                *node = *node_;
                node->left = nodeL;
                delete nodeD;
            }
            else
            {
                Node* nodeR = node_;
                Node* node__ = node_->left;
                while(node__->left!=nullptr)
                {
                    node_ = node_->left;
                    node__ = node_->left;
                }
                Node* nodeD = node__;
                *node = *node__;
                node->left = nodeL;
                node->right = nodeR;
                node_->left = node__->right;
                delete(nodeD);
            }
        }
    }
};

int main()
{
    //Создаем дерево из примера
    HeapTree tree;
    tree.add(8);
    tree.add(3);
    tree.add(10);
    tree.add(1);
    tree.add(6);
    tree.add(4);
    tree.add(14);
    tree.add(13);
    tree.add(7);
    //Проверяем корневой узел, минимальное и максимальные значения, наличие узла 6 и 9.
    std::cout << "Root node: " << tree.root()->data << std::endl;
    std::cout << "Min node: " << tree.min() << "; Max node: " << tree.max() << std::endl;
    std::cout << "Has 6: " << tree.has(6) << "; Has 9: " << tree.has(9) << std::endl;
    //Проверяем правильнось нахождения узла: значение самого узла, значение левого от него узла , значение правого от него узла
    std::cout << "Trying to find 6:\nFound node: " << tree.find(6)->data << "; Left from found node: " << tree.find(6)->left->data << "; Right from found node: " << tree.find(6)->right->data << std::endl;
    std::cout << "Removing nodes: 7, 14, 3, 1, 8" << std::endl;
    //Проверяем все ситуации удаления, включая удаление корневого узла
    tree.remove(7);
    tree.remove(14);
    tree.remove(3);
    tree.remove(1);
    tree.remove(8);
    //Проверяем корневой узел
    std::cout << "New root node: " << tree.root()->data << "; Left from new root node: " << tree.root()->left->data << "; Right from new root node: " << tree.root()->right->data << std::endl;
}
