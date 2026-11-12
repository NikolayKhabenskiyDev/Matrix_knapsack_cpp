#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>

template<class T>
class Node {

protected:

    T data;
    Node<T>** childs;
    Node<T>* parent;
    int arity;
    int depth;

public:

    Node()
    {
        data = NULL;
        arity = 2;
        depth = 0;
        childs = new Node<T>*[2];
        childs[0] = nullptr;
        childs[1] = nullptr;
        parent = nullptr;
    }

    Node(T item, int ar)
    {
        data = item;
        arity = ar;
        depth = 0;
        childs = new Node<T>*[arity];
        for (int ii = 0; ii < arity; ii++)
        {
            childs[ii] = nullptr;
        }
        parent = nullptr;
    }

    Node(Node<T>* other_node, Node<T>* parent_node)
    {
        data = other_node->data;
        arity = other_node->arity;
        childs = new Node<T>*[arity];
        parent = parent_node;
        depth = parent_node->depth + 1;
        for (int ii = 0; ii < arity; ii++)
        {
            if (other_node->childs[ii] == nullptr)
            {
                childs[ii] = nullptr;
            }
            else
            {
                childs[ii] = new Node<T>(other_node->childs[ii], this);
            }
        }
    }

    Node(Node<T>* other_node)
    {
        data = other_node->data;
        arity = other_node->arity;
        depth = 0;
        childs = new Node<T>*[arity];
        parent = nullptr;
        for (int ii = 0; ii < arity; ii++)
        {
            if (other_node->childs[ii] == nullptr)
            {
                childs[ii] = nullptr;
            }
            else
            {
                childs[ii] = new Node<T>(other_node->childs[ii], this);
            }
        }
    }

    Node& operator = (Node<T>* other_node)
    {
        delete this;
        data = other_node->data;
        arity = other_node->arity;
        depth = 0;
        childs = new Node<T>*[arity];
        parent = nullptr;
        for (int ii = 0; ii < arity; ii++)
        {
            if (other_node->childs[ii] == nullptr)
            {
                childs[ii] = nullptr;
            }
            else
            {
                childs[ii] = new Node<T>(other_node->childs[ii], this);
            }
        }
    }

    Node(Node<T>&& other_node)
    {
        data = other_node.data;
        arity = other_node.arity;
        depth = other_node.depth;
        childs = other_node.childs;
        parent = other_node.parent;
        other_node.data = 0;
        other_node.arity = 0;
        other_node.depth = 0;
        other_node.childs = nullptr;
        other_node.parent = nullptr;
    }

    Node& operator = (Node<T>&& other_node)
    {
        delete this;
        data = other_node.data;
        arity = other_node.arity;
        depth = other_node.depth;
        childs = other_node.childs;
        parent = other_node.parent;
        other_node.data = 0;
        other_node.arity = 0;
        other_node.depth = 0;
        other_node.childs = nullptr;
        other_node.parent = nullptr;
    }

    const T& GetData() const
    {
        return data;
    }

    Node<T>* GetChilds(int index) const
    {
        return childs[index];
    }

    Node<T>* GetParent() const
    {
        return parent;
    }

    int GetDepth() const
    {
        return depth;
    }

    int GetArity() const
    {
        return arity;
    }

    void SetData(const T& new_data)
    {
        data = new_data;
    }

    void SetChilds(Node<T>* new_node, int index)
    {
        childs[index] = new_node;
    }

    void SetParent(Node<T>* new_node)
    {
        parent = new_node;
    }

    void SetDepth(int new_depth)
    {
        depth = new_depth;
        for (int ii = 0; ii < arity; ii++)
        {
            if (childs[ii] != nullptr)
            {
                childs[ii]->SetDepth(new_depth + 1);
            }
        }
    }

    void AddChild(Node<T>* new_node)
    {
        arity++;
        Node<T>** new_childs = new Node<T>*[arity];
        for (int ii = 0; ii < arity; ii++)
        {
            new_childs[ii] = childs[ii];
        }
        new_childs[arity - 1] = new_node;
        new_node->SetParent(this);
        new_node->SetDepth = this->GetDepth() + 1;
        delete childs;
        childs = new_childs;
    }

    ~Node()
    {
        if (this != nullptr)
        {
            for (int ii = 0; ii < this->arity; ii++)
            {
                if (childs[ii] != nullptr)
                {
                    delete childs[ii];
                }
            }
            delete[] childs;
        }
    }

    friend bool operator != (const Node<T>& node1, const Node<T>& node2);
    friend bool operator == (const Node<T>& node1, const Node<T>& node2);
};

template <class T>
bool operator != (const Node<T>& node1, const Node<T>& node2)
{
    if (node1 == nullptr)
    {
        if (node2 == nullptr)
        {
            return 0;
        }
        return 1;
    }
    std::cout << node1->data << "  " << node2->data << std::endl;
    if (node1->data != node2->data || node1->arity != node2->arity)
    {
        return 1;
    }
    for (int ii = 0; ii < node1->arity; ii++)
    {
        if (node1->childs[ii] != node2->childs[ii])
        {
            return 1;
        }
    }
    return 0;
}

template <class T>
bool operator == (const Node<T>& node1, const Node<T>& node2)
{
    if (node1 != node2)
    {
        return 0;
    }
    return 1;
}

template <class T>
std::ostream& operator << (std::ostream& stream, Node<T>* node)
{
    if (node != nullptr)
    {
        for (int ii = node->GetArity() - 1; ii >= node->GetArity() / 2; ii--)
        {
            if (node->GetChilds(ii) != nullptr)
            {
                std::cout << node->GetChilds(ii);
            }
            else
            {
                std::cout << std::setw((node->GetDepth() + 1) * 20) << "_" << std::endl;
            }
        }

        std::cout << std::setw(node->GetDepth() * 20) << node->GetData() << std::endl;

        for (int ii = node->GetArity() / 2 - 1; ii >= 0; ii--)
        {
            if (node->GetChilds(ii) != nullptr)
            {
                std::cout << node->GetChilds(ii);
            }
            else
            {
                std::cout << std::setw((node->GetDepth() + 1) * 20) << "_" << std::endl;
            }
        }
    }
    else
    {
        stream << "_";
    }
    return stream;
}

#endif