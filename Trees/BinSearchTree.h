#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H

#include <iomanip>
#include "BasicStructures/FunctionsForMapReduce.h"
#include "Node.h"

template<class T>
class SearchTree {
private:
    Node<T>* root;
    bool(*Compare)(const T&, const T&);

    Node<T>* GetNode(Node<T>* node, const T& value)
    {
        if (node == nullptr)
        {
            throw::std::invalid_argument("There is no such node in tree\n");
        }
        if (node->GetData() == value)
        {
            return node;
        }
        else
        {
            if (Compare(node->GetData(), value))
            {
                return GetNode(node->GetChilds(0), value);
            }
            if (Compare(value, node->GetData()))
            {
                return GetNode(node->GetChilds(1), value);
            }
        }
    }

    bool FindNode(Node<T>* node, const T& value)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->GetData() == value)
        {
            return 1;
        }
        else
        {
            if (Compare(node->GetData(), value))
            {
                return FindNode(node->GetChilds(0), value);
            }
            if (Compare(value, node->GetData()))
            {
                return FindNode(node->GetChilds(1), value);
            }
        }
    }

    Node<T>* GetMinNode(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node<T>* min_node = node;
        if (node->GetChilds(0) != nullptr)
        {
            if (min_node->GetData() > node->GetChilds(0)->GetData())
            {
                min_node = node->GetChilds(0);
            }
        }
        if (node->GetChilds(1) != nullptr)
        {
            if (min_node->GetData() > node->GetChilds(1)->GetData())
            {
                min_node = node->GetChilds(1);
            }
        }
        if (min_node == node)
        {
            return node;
        }
        return GetMinNode(min_node);
    }

    Node<T>* GetMaxNode(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node<T>* max_node = node;
        if (node->GetChilds(0) != nullptr)
        {
            if (max_node->GetData() < node->GetChilds(0)->GetData())
            {
                max_node = node->GetChilds(0);
            }
        }
        if (node->GetChilds(1) != nullptr)
        {
            if (max_node->GetData() < node->GetChilds(1)->GetData())
            {
                max_node = node->GetChilds(1);
            }
        }
        if (max_node == node)
        {
            return node;
        }
        return GetMaxNode(max_node);
    }

    template <class T>
    bool CompareNodes(Node<T>* node1, Node<T>* node2)
    {
        if (node1 == nullptr)
        {
            if (node2 == nullptr)
            {
                return 1;
            }
            return 0;
        }
        if (node2 == nullptr)
        {
            return 0;
        }
        if (node1->GetData() != node2->GetData())
        {
            return 0;
        }
        if (CompareNodes(node1->GetChilds(0), node2->GetChilds(0)) == false)
        {
            return 0;
        }
        if (CompareNodes(node1->GetChilds(1), node2->GetChilds(1)) == false)
        {
            return 0;
        }
        return 1;
    }

    SearchTree<T>* GetSubTree(Node<T>* node, SearchTree<T>* SubTree)
    {
        if (node == nullptr || SubTree->root == nullptr)
        {
            throw::std::invalid_argument("There is no such subtree in tree\n");
        }
        if (CompareNodes(node, SubTree->root))
        {
            return new SearchTree<T>(node);
        }
        else
        {
            if (Compare(node->GetData(), SubTree->root->GetData()))
            {
                return GetSubTree(node->GetChilds(0), SubTree);
            }
            if (Compare(SubTree->root->GetData(), node->GetData()))
            {
                return GetSubTree(node->GetChilds(1), SubTree);
            }
        }
        throw::std::invalid_argument("There is no such subtree in tree\n");
    }

    bool FindSubTree(Node<T>* node, SearchTree<T>* SubTree)
    {
        if (node == nullptr || SubTree->root == nullptr)
        {
            return 0;
        }
        if (CompareNodes(node, SubTree->root))
        {
            return 1;
        }
        else
        {
            if (Compare(node->GetData(), SubTree->root->GetData()))
            {
                return FindSubTree(node->GetChilds(0), SubTree);
            }
            if (Compare(SubTree->root->GetData(), node->GetData()))
            {
                return FindSubTree(node->GetChilds(1), SubTree);
            }
        }
        return 0;
    }

    SearchTree* InsertNode(Node<T>* current, Node<T>* parent, const T& value)
    {
        if (current == nullptr)
        {
            current = new Node<T>(value, 2);
            if (parent != nullptr)
            {
                current->SetParent(parent);
                current->SetDepth(parent->GetDepth() + 1);
                if (Compare(current->GetParent()->GetData(), value))
                {
                    current->GetParent()->SetChilds(current, 0);
                }
                if (Compare(value, current->GetParent()->GetData()))
                {
                    current->GetParent()->SetChilds(current, 1);
                }
            }
            return this;
        }
        else
        {
            if (Compare(current->GetData(), value))
            {
                return InsertNode(current->GetChilds(0), current, value);
            }
            if (Compare(value, current->GetData()))
            {
                return InsertNode(current->GetChilds(1), current, value);
            }
            /*if (current->GetData() == value)
            {
                throw::std::invalid_argument("This node is already in tree\n");
            }*/
        }
    }
    
    SearchTree<T>* DeleteNode(Node<T>* node, const T& value)
    {
        if (node->GetData() != value)
        {
            node = GetNode(node, value);
        }
        if (node == nullptr)
        {
            throw::std::invalid_argument("There is no such node in tree\n");
        }
        if (node->GetChilds(0) != nullptr)
        {
            Node<T>* temp = GetMaxNode(node->GetChilds(0));
            node->SetData(temp->GetData());
            DeleteNode(temp, temp->GetData());
            return this;
        }
        if (node->GetChilds(1) != nullptr)
        {
            Node<T>* temp = GetMinNode(node->GetChilds(1));
            node->SetData(temp->GetData());
            DeleteNode(temp, temp->GetData());
            return this;
        }

        Node<T>* temp = node;
        if (Compare(node->GetParent()->GetData(), temp->GetData()))
        {
            node->GetParent()->SetChilds(nullptr, 0);
        }
        if (Compare(temp->GetData(), node->GetParent()->GetData()))
        {
            node->GetParent()->SetChilds(nullptr, 1);
        }
        if (node->GetParent()->GetData() == temp->GetData())
        {
            node->GetParent()->SetChilds(nullptr, 0);
            node->GetParent()->SetChilds(nullptr, 1);
        }
        delete temp;
        return this;
    }

    Node<T>* MapNode(Node<T>* node, T(*func)(const T&, int), int operand)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node<T>* new_node = new Node<T>(func(node->GetData(), operand), 2);
        new_node->SetChilds(MapNode(node->GetChilds(0), func, operand), 0);
        new_node->SetChilds(MapNode(node->GetChilds(1), func, operand), 1);
        if (new_node->GetChilds(0) != nullptr)
        {
            new_node->GetChilds(0)->SetParent(new_node);
        }
        if (new_node->GetChilds(1) != nullptr)
        {
            new_node->GetChilds(1)->SetParent(new_node);
        }
        return new_node;
    }

    int FindMaxDepth(Node<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int max_path = 0;
        if (max_path < FindMaxDepth(node->GetChilds(0)) + 1)
        {
            max_path = FindMaxDepth(node->GetChilds(0)) + 1;
        }
        if (max_path < FindMaxDepth(node->GetChilds(1)) + 1)
        {
            max_path = FindMaxDepth(node->GetChilds(1)) + 1;
        }
        return max_path;
    }

    Node<T>* GetNodeByPath(Node<T>* node, int* path, int path_length, int depth)
    {
        if (node == nullptr)
        {
            throw::std::invalid_argument("There is no such node in tree\n");
        }
        if (depth == path_length)
        {
            return node;
        }
        if (path[depth] < 0 || path[depth] > 1)
        {
            throw::std::invalid_argument("Wrong path\n");
        }
        Node<T>* next_node = node->GetChilds(path[depth]);
        depth++;
        return GetNodeByPath(next_node, path, path_length, depth);
    }

    SearchTree<T>* WhereTree(Node<T>* node, bool (*func)(const T&))
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        WhereTree(node->GetChilds(0), func);
        WhereTree(node->GetChilds(1), func);
        if (func(node->GetData()) == false)
        {
            this->DeleteNode(node->GetData());
        }
        return this;
    }

public:

    SearchTree(bool(*Func)(const T&, const T&))
    {
        root = nullptr;
        Compare = Func;
    }

    SearchTree(T* items, int amount, bool(*Func)(const T&, const T&))
    {
        root = new Node<T>(items[0], 2);
        Compare = Func;
        for (int ii = 1; ii < amount; ii++)
        {
            InsertNode(root, root, items[ii]);
        }
        root->SetDepth(0);
    }

    SearchTree(Node<T>* root, bool(*Func)(const T&, const T&))
    {
        root = root;
        Compare = Func;
    }

    SearchTree(SearchTree<T>* other_tree)
    {
        root = new Node<T>(other_tree->root);
        Compare = other_tree->Compare;
    }

    SearchTree(SearchTree<T>&& other_tree)
    {
        root = other_tree->Root;
        Compare = other_tree->Compare;
        other_tree->Root = nullptr;
        other_tree->Compare = nullptr;
    }

    SearchTree operator = (const SearchTree<T>& other_tree)
    {
        delete root;
        root = new Node<T>(other_tree->Root);
        Compare = other_tree->Compare;
    }

    SearchTree& operator = (SearchTree<T>&& other_tree)
    {
        delete root;
        root = other_tree->Root;
        Compare = other_tree->Compare;
        other_tree->Root = nullptr;
        other_tree->Compare = nullptr;
    }

    ~SearchTree()
    {
        delete root;
    }

    Node<T>* GetRoot()
    {
        return root;
    }

    SearchTree<T>* SetRoot(Node<T>* new_root)
    {
        root = new_root;
        return this;
    }

    SearchTree<T>* SetCompareFunction(bool(*NewCompare)(const T&, const T&))
    {
        Compare = NewCompare;
        return this;
    }

    SearchTree* InsertNode(const T& value)
    {
        if (this->root == nullptr)
        {
            this->root = new Node<T>(value, 2);
            return this;
        }
        else
        {
            return InsertNode(this->root, this->root, value);
        }
    }

    template <class T>
    bool CompareTrees(SearchTree<T>* other_tree)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return CompareNodes(this->root, other_tree->root);
    }

    Node<T>* GetNode(const T& value)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return GetNode(this->root, value);
    }

    bool FindNode(const T& value)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return FindNode(this->root, value);
    }

    SearchTree<T>* GetSubTree(SearchTree<T>* SubTree)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return GetSubTree(this->root, SubTree);
    }

    bool FindSubTree(SearchTree<T>* SubTree)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return FindSubTree(this->root, SubTree);
    }

    Node<T>* GetMinNode()
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return GetMinNode(this->root);
    }

    Node<T>* GetMaxNode()
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return GetMaxNode(this->root);
    }

    SearchTree<T>* DeleteNode(const T& value)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return DeleteNode(this->root, value);
    }

    SearchTree<T>* MapTree(T(*func)(const T&, int), int operand)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        Node<T>* new_node = MapNode(this->root, func, operand);
        if (new_node == nullptr)
        {
            return nullptr;
        }
        delete root;
        new_node->SetDepth(0);
        this->root = new_node;
        return this;
    }

    SearchTree<T>* WhereTree(bool (*func)(const T&))
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return WhereTree(this->root, func);
    }

    int FindMaxDepth()
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return FindMaxDepth(this->root);
    }

    Node<T>* GetNodeByPath(int* path, int path_length)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        return GetNodeByPath(this->root, path, path_length, 0);
    }

    SearchTree<T>* MergeTree(SearchTree<T>* Tree2)
    {
        if (this->root == nullptr || this == nullptr)
        {
            throw::std::invalid_argument("Tree is empty\n");
        }
        if (Tree2->root == nullptr || Tree2 == nullptr)
        {
            throw::std::invalid_argument("Second tree is empty\n");
        }
        if (Compare(this->GetMinNode()->GetData(), Tree2->GetMaxNode()->GetData()))
        {
            SearchTree<T>* new_Tree = new SearchTree<T>(this);
            Node<T>* added_Node = new Node<T>(Tree2->root);
            new_Tree->GetMinNode()->SetChilds(added_Node, 0);
            new_Tree->root->SetDepth(0);
            return new_Tree;
        }
        if (Compare(Tree2->GetMinNode()->GetData(), this->GetMaxNode()->GetData()))
        {
            return Tree2->MergeTree(this);
        }
        else
        {
            throw::std::invalid_argument("One tree isn't smaller than other\n");
        }
    }
};

template<class T>
ArraySequenceMut<T>* GetLeaves(Node<T>* node, ArraySequenceMut<T>* leaves_seq)
{
    if (node != nullptr)
    {
        bool is_leaf = 1;
        for (int ii = 0; ii < node->GetArity(); ii++)
        {
            if (node->GetChilds(ii) != nullptr)
            {
                is_leaf = 0;
            }
        }
        if (is_leaf == 1)
        {
            leaves_seq->Append(node->GetData());
        }
        else
        {
            for (int ii = 0; ii < node->GetArity(); ii++)
            {
                GetLeaves(node->GetChilds(ii), leaves_seq);
            }
        }
    }
    return leaves_seq;
}

template<class T>
ArraySequenceMut<T>* GetLeaves(SearchTree<T>* tree)
{
    ArraySequenceMut<T>* leaves_seq = new ArraySequenceMut<T>();
    return GetLeaves(tree->GetRoot(), leaves_seq);
}

template<class T>
std::ostream& operator << (std::ostream& stream, SearchTree<T>* Tree)
{
    stream << Tree->GetRoot() << std::endl;
    return stream;
}

#endif