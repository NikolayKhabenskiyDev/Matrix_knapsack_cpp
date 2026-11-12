#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "Node.h"

int FindArity(Pair<int, int> item1, Pair<int, int> item2)
{
    return 2;
}

int FindArity(RectangleMatrix<int>* big_matr, RectangleMatrix<int>* small_matr)
{
    
    return CountAllFit(big_matr, small_matr) + 1;
}

int FindArity(Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent> item1,
    Pair<ArraySequenceMut<Pair<int, int>>, MatrKnapContent> item2)
{
    if (item2.GetData().GetAmount() == 0)
    {
        return 1;
    }
    int end_index = item2.GetData().GetAmount() - 1;
    std::cout << end_index;
    return FindArity(item1.GetData().GetMatr(), item2.GetData().GetItem(end_index)->GetMatr());
}

template <class T>
class ArrNode
{
private:
    T* data;
    int arity;
    int depth;
	int elem_amount;
    ArrNode<T>** childs;
    ArrNode<T>* parent;

public:

    ArrNode()
    {
        this->data = new T[2];
        this->arity = 2;
        this->depth = 0;
        this->elem_amount = 0;
        this->childs = new ArrNode<T>*[2];
        for (int ii = 0; ii < 2; ii++)
        {
            this->childs[ii] = nullptr;
        }
        this->parent = nullptr;
    }

	ArrNode(int ar)
	{
        this->arity = ar;
        this->data = new T[this->arity - 1];
        this->depth = 0;
        this->elem_amount = 0;
        this->childs = new ArrNode<T>*[this->arity];
        for (int ii = 0; ii < this->arity; ii++)
        {
            this->childs[ii] = nullptr;
        }
        this->parent = nullptr;
	}

    ArrNode(int ar, ArrNode<T>* parent_node)
    {
        this->arity = ar;
        this->data = new T[this->arity - 1];
        this->depth = parent_node->depth + 1;
        this->elem_amount = 0;
        this->childs = new ArrNode<T>*[this->arity];
        for (int ii = 0; ii < this->arity; ii++)
        {
            this->childs[ii] = nullptr;
        }
        this->parent = parent_node;
    }

    ArrNode(T* items, int amount, int ar)
    {
        this->arity = ar;
        this->data = new T[this->arity - 1];
        this->depth = 0;
        this->elem_amount = 0;
        this->childs = new ArrNode<T>*[this->arity];
        for (int ii = 0; ii < this->arity; ii++)
        {
            this->childs[ii] = nullptr;
        }
        for (int ii = 0; ii < amount; ii++)
        {
            this->InsertElem(items[ii], ar);
        }
        this->parent = nullptr;
    }

    ArrNode(ArrNode<T>* other_node)
    {
        delete this;
        this->arity = other_node->arity;
        this->depth = 0;
        this->childs = new Node<T>*[this->arity];
        this->data = new T[this->arity - 1];
        for (int ii = 0; ii < elem_amount; ii++)
        {
            this->data[ii] = other_node->data[ii];
        }
        for (int ii = 0; ii < this->arity; ii++)
        {
            if (other_node->childs[ii] == nullptr)
            {
                this->childs[ii] = nullptr;
            }
            else
            {
                this->childs[ii] = new Node<T>(other_node->childs[ii], this);
            }
        }
        this->parent = nullptr;
    }

    ArrNode(const ArrNode<T>& other_node)
    {
        this->arity = other_node.arity;
        this->depth = 0;
        this->childs = new Node<T>*[this->arity];
        this->data = new T[this->arity - 1];
        for (int ii = 0; ii < elem_amount; ii++)
        {
            this->data[ii] = other_node.data[ii];
        }
        for (int ii = 0; ii < this->arity; ii++)
        {
            if (other_node.childs[ii] == nullptr)
            {
                this->childs[ii] = nullptr;
            }
            else
            {
                this->childs[ii] = new Node<T>(other_node.childs[ii], this);
            }
        }
        this->parent = nullptr;
    }

    ArrNode(ArrNode<T>* other_node, ArrNode<T>* parent_node)
    {
        this->arity = other_node->arity;
        this->depth = parent_node->depth + 1;
        this->childs = new Node<T>*[this->arity];
        this->data = new T[this->arity - 1];
        for (int ii = 0; ii < elem_amount; ii++)
        {
            this->data[ii] = other_node->data[ii];
        }
        for (int ii = 0; ii < this->arity; ii++)
        {
            if (other_node->childs[ii] == nullptr)
            {
                this->childs[ii] = nullptr;
            }
            else
            {
                this->childs[ii] = new Node<T>(other_node->childs[ii], this);
            }
        }
        this->parent = parent_node;
    }

    ArrNode(ArrNode<T>&& other_node)
    {
        delete this;
        this->arity = other_node.arity;
        this->depth = other_node.depth;
        this->childs = other_node.childs;
        this->data = other_node.data;
        this->parent = other_node.parent;
        other_node.arity = 0;
        other_node.depth = 0;
        other_node.childs = nullptr;
        other_node.data = nullptr;
        other_node.parent = nullptr;
    }

    ArrNode<T>& operator = (const ArrNode<T>& other_node)
    {
        delete this->childs;
        delete this->data;
        this->arity = other_node.arity;
        this->depth = 0;
        this->childs = new Node<T>*[this->arity];
        this->data = new T[this->arity - 1];
        for (int ii = 0; ii < elem_amount; ii++)
        {
            this->data[ii] = other_node.data[ii];
        }
        for (int ii = 0; ii < this->arity; ii++)
        {
            if (other_node.childs[ii] == nullptr)
            {
                this->childs[ii] = nullptr;
            }
            else
            {
                this->childs[ii] = new Node<T>(other_node.childs[ii], this);
            }
        }
        this->parent = nullptr;
    }

    int GetAmount() const
    {
        return this->elem_amount;
    }

    T GetData(int index) const
    {
        return this->data[index];
    }

    T* GetArrData() const
    {
        return this->data;
    }

    ArrNode<T>* GetChilds(int index) const
    {
        return this->childs[index];
    }

    ArrNode<T>* GetParent() const
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

    ArrNode<T>* InsertElem(T elem, int node_arity)
    {
        if (this->elem_amount == 0)
        {
            this->data[0] = elem;
            this->elem_amount++;
            return this;
        }
        if (this->arity == 1)
        {
            if (this->childs[0] == nullptr)
            {
                this->childs[0] = new ArrNode<T>(node_arity, this);
            }
            return this->childs[0]->InsertElem(elem, node_arity);
        }
        if (Less(elem, this->data[0]))
        {
            if (this->childs[0] == nullptr)
            {
                this->childs[0] = new ArrNode<T>(node_arity, this);
                this->childs[0]->data[0] = elem;
                this->childs[0]->elem_amount++;
                return this->childs[0];
            }
            else
            {
                return this->childs[0]->InsertElem(elem, node_arity);
            }
        }
        for (int ii = 1; ii < this->arity - 1; ii++)
        {
            if (ii > this->elem_amount - 1)
            {
                this->data[ii] = elem;
                this->elem_amount++;
                return this;
            }
            if (Less(elem, this->data[ii]))
            {
                if (this->childs[ii] == nullptr)
                {
                    this->childs[ii] = new ArrNode<T>(node_arity, this);
                    this->childs[ii]->data[0] = elem;
                    this->childs[ii]->elem_amount++;
                    return this->childs[ii];
                }
                else
                {
                    return this->childs[ii]->InsertElem(elem, node_arity);
                }
            }
        }
        if (Less(this->data[elem_amount - 1], elem))
        {
            if (this->childs[this->arity - 1] == nullptr)
            {
                this->childs[this->arity - 1] = new ArrNode<T>(node_arity, this);
                this->childs[this->arity - 1]->data[0] = elem;
                this->childs[this->arity - 1]->elem_amount++;
                return this->childs[this->arity - 1];
            }
            else
            {
                return this->childs[this->arity - 1]->InsertElem(elem, node_arity);
            }
        }
    }

    ~ArrNode()
    {
        for (int ii = 0; ii < this->arity; ii++)
        {
            if (this->childs[ii] != nullptr)
            {
                delete this->childs[ii];
            }
        }
        delete[] this->data;
        delete[] this->childs;
    }

    int GetMaxArity()
    {
        return this->GetMaxArity(0);
    }

    int GetMaxArity(int max_arity)
    {
        if (this == nullptr)
        {
            return max_arity;
        }
        for (int ii = 0; ii < this->arity; ii++)
        {
            max_arity = this->childs[ii]->GetMaxArity(max_arity);
        }
        if (max_arity > this->GetArity())
        {
            return max_arity;
        }
        else
        {
            return this->GetArity();
        }
    }
};

template<class T>
std::ostream& operator << (std::ostream& stream, const ArrNode<T>& node)
{
    if (node != nullptr)
    {
        for (int ii = node.GetArity() - 1; ii >= node.GetArity() / 2; ii--)
        {
            if (node.GetChilds(ii) != nullptr)
            {
                std::cout << node.GetChilds(ii);
            }
            else
            {
                std::cout << std::setw((node.GetDepth() + 1) * 10) << "_" << std::endl;
            }
        }

        std::cout << std::setw(node.GetDepth() * 10) << node.GetData(0) << std::endl;

        for (int ii = node.GetArity() / 2 - 1; ii >= 0; ii--)
        {
            if (node.GetChilds(ii) != nullptr)
            {
                std::cout << node.GetChilds(ii);
            }
            else
            {
                std::cout << std::setw((node.GetDepth() + 1) * 10) << "_" << std::endl;
            }
        }
    }
    else
    {
        stream << "_";
    }
    return stream;
}

template<class T>
std::ostream& operator << (std::ostream& stream, ArrNode<T>* node)
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
                std::cout << std::setw((node->GetDepth() + 1) * 10) << "_" << std::endl;
            }
        }

        for (int ii = 0; ii < node->GetAmount(); ii++)
        {
            std::cout << std::setw(node->GetDepth() * 10) << node->GetData(ii) << std::endl;
        }

        for (int ii = node->GetArity() / 2 - 1; ii >= 0; ii--)
        {
            if (node->GetChilds(ii) != nullptr)
            {
                std::cout << node->GetChilds(ii);
            }
            else
            {
                std::cout << std::setw((node->GetDepth() + 1) * 10) << "_" << std::endl;
            }
        }
    }
    else
    {
        stream << "_";
    }
    stream << "\n";
    return stream;
}    

#endif