#ifndef ARRAYTREE_H
#define ARRAYTREE_H

#include<string>
#include "Node.h"
#include "ArrayNode.h"
#include "DictionaryTree.h"
#include "Interfaces/ToString.h"

template <class T1, class T2>
class DictArrTree : public ArrNode<Pair<T1, T2>*>
{
private:
	ArrNode<Pair<T1, T2>*>* root;

public:
	DictArrTree()
	{
		root = new ArrNode<Pair<T1, T2>*>();
	}

	DictArrTree(int ar)
	{
		root = new ArrNode<Pair<T1, T2>*>(ar);
	}

    DictArrTree(int ar, ArrNode<Pair<T1, T2>*>* parent_node)
    {
		root = new ArrNode<Pair<T1, T2>*>(ar, parent_node);
    }

	DictArrTree(Pair<T1, T2>** item, int amount, int ar)
	{
		root = new ArrNode<Pair<T1, T2>*>(item, amount, ar);
	}

	DictArrTree(ArrNode<Pair<T1, T2>*>* other_node)
	{
		root = new ArrNode<Pair<T1, T2>*>(other_node);
	}

	DictArrTree(const ArrNode<Pair<T1, T2>*>& other_node)
	{
		root = new ArrNode<Pair<T1, T2>>(other_node);
	}

	DictArrTree(ArrNode<Pair<T1, T2>*>* other_node, ArrNode<Pair<T1, T2>*>* parent_node)
	{
		root = new ArrNode<Pair<T1, T2>*>(other_node, parent_node);
	}

	DictArrTree(DictArrTree<T1, T2>&& other_tree)
	{
		root = other_tree.root;
		other_tree.root = nullptr;
	}

	DictArrTree(DictArrTree<T1, T2>* other_tree)
	{
		root = new ArrNode<Pair<T1, T2>*>(other_tree.root);
	}

	DictArrTree(const DictArrTree<T1, T2>& other_tree)
	{
		root = new ArrNode<Pair<T1, T2>*>(other_tree.root);
	}

	~DictArrTree()
	{
		delete root;
	}

	ArrNode<Pair<T1, T2>*>* GetRoot()
	{
		return root;
	}

	DictArrTree<T1, T2>* SetRoot(ArrNode<Pair<T1, T2>*>* new_root)
	{
		root = new_root;
		return this;
	}

	DictArrTree<T1, T2>* InsertElem(Pair<T1, T2>* elem, int node_arity)
	{
		root->InsertElem(elem, node_arity);
		return this;
	}

	T2 GetByKey(ArrNode<Pair<T1, T2>*>* node, const T1& key)
	{
		if (node == nullptr)
		{
			throw::std::invalid_argument("There is no such node in tree\n");
		}
		for (int ii = 0; ii < node->GetArity(); ii++)
		{
			if (ii >= node->GetAmount())
			{
				throw::std::invalid_argument("There is no such node in tree\n");
			}
			if (node->GetData(ii).GetKey() == key)
			{
				return node->GetData(ii).GetData();
			}
			if (node->GetData(ii).GetKey() > key)
			{
				return GetByKey(node->GetChilds(ii), key);
			}
		}
	}
};

template<class T>
ArraySequenceMut<T>* GetLeaves(ArrNode<T>* node, ArraySequenceMut<T>* leaves_seq)
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
			for (int ii = 0; ii < node->GetAmount(); ii++)
			{
				leaves_seq->Append(node->GetData(ii));
			}
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

template<class T1, class T2>
ArraySequenceMut<Pair<T1, T2>*>* GetLeaves(DictArrTree<T1, T2>* tree)
{
	ArraySequenceMut<Pair<T1, T2>*>* leaves_seq = new ArraySequenceMut<Pair<T1, T2>*>();
	if (tree != nullptr)
	{
		return GetLeaves(tree->GetRoot(), leaves_seq);
	}
	else 
	{
		return leaves_seq;
	}
}

template<class T1, class T2>
std::ostream& operator << (std::ostream& stream, DictArrTree<T1, T2>* dict)
{
	if (dict != nullptr)
	{
		stream << dict->GetRoot();
	}
	else
	{
		stream << "_\n";
	}
	return stream;
};

#endif