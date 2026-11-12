#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<string>
#include "Node.h"
#include "BinSearchTree.h"
#include "BasicStructures/Pair.h"

template <class T1, class T2>
class DictBinTree : public SearchTree<Pair<T1, T2>>
{
public:
	DictBinTree(bool(*Func)(const Pair<T1, T2>&, const Pair<T1, T2>&)) : SearchTree<Pair<T1, T2>>(Func) { }

	DictBinTree(Pair<T1, T2>* items, int amount, bool(*Func)(const Pair<T1, T2>&, const Pair<T1, T2>&)) :
		SearchTree<Pair<T1, T2>>(items, amount, Func) { }

	DictBinTree(Node<Pair<T1, T2>>* root, bool(*Func)(const Pair<T1, T2>&, const Pair<T1, T2>&)) :
		SearchTree<Pair<T1, T2>>(root, Func) { }

	DictBinTree(const SearchTree<Pair<T1, T2>>& other_tree) : SearchTree<Pair<T1, T2>>(other_tree) { }

	DictBinTree(SearchTree<Pair<T1, T2>>&& other_tree) : SearchTree<Pair<T1, T2>>(other_tree) { }

	DictBinTree(DictBinTree<T1, T2>* other_dict) : DictBinTree<T1, T2>(other_dict)
	{
		this->root = new Node<Pair<T1, T2>>(other_dict->root);
		this->Compare = other_dict->Compare;
	}

	~DictBinTree() {}

	T2 GetByKey(Node<Pair<T1, T2>>* node, const T1& key)
	{
        if (node == nullptr)
        {
            throw::std::invalid_argument("There is no such node in tree\n");
        }
        if (node->GetData().GetKey() == key)
        {
            return node->GetData().GetData();
        }
        else
        {
            if (Compare(node->GetData().GetKey(), key))
            {
                return GetNode(node->GetChilds(0), key);
            }
            if (Compare(key, node->GetData().GetKey()))
            {
                return GetNode(node->GetChilds(1), key);
            }
        }
	}
};

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, const DictBinTree<T1, T2>& dict)
{
	stream << dict.GetRoot() << std::endl;
	return stream;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& stream, DictBinTree<T1, T2>* dict)
{
	stream << dict->GetRoot() << std::endl;
	return stream;
}

#endif
