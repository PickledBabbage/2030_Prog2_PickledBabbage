//Ben Wabschall
//COSC 2300
//Program 2
//Section 11

//avl tree from tutorialspoint.com

#include "WordTree.h"
#include<iostream>
#include<algorithm> //for max()
using namespace::std;

//Default constructor
template<class T>
WordTree<T>::WordTree()
{
	for (int i = 0; i <= 26; i++)
	{
		root[i] = nullptr;
	}
}

//deletes entire tree provided a node
template<class T>
void WordTree<T>::burnTree(Node<T>* Nroot)
{	
	if (Nroot != nullptr)
	{
		burnTree(Nroot->left);
		burnTree(Nroot->right);
		delete Nroot;
	}
}

//destructor
template<class T>
WordTree<T>::~WordTree()
{
	for (int i = 0; i <= 26; i++)
	{
		burnTree(root[i]);
	}
}

template<class T>
bool WordTree<T>::remove(T d, Node<T>* n)
{
	//item not found
	if (d == nullptr)
	{
		return false;
	}

	WordTree* oldNode;

	//has right child/no child
	if (n->left == nullptr)
	{
		oldNode = n;
		n = n->right;
		delete oldNode;
		return true;
	}

	//has left child/no child
	else if (n->right == nullptr)
	{
		oldNode = n;
		n = n->left;
		delete oldNode;
		return true;
	}

	//has two children
	oldNode = findMin(n->right);
	n->data = oldNode->data;
	remove(n->data, n->right);
	return true;

}

template<class T>
void WordTree<T>::callInsert(T d)
{
	int z = int(d[0]);
	insert(d, root[z - int('a')]);
}

//TODO maybe increment height here?
template<class T>
void WordTree<T>::insert(T d, Node<T>*& tree)
{
	if (tree == nullptr)
	{
		tree = new Node<T>(d);
	}
	else if (d < tree->data)
	{
		insert(d, tree->left);
		tree = balance(tree);
	}
	else if (d > tree->data)
	{
		insert(d, tree->right);
		tree = balance(tree);
	}
}

template<class T>
bool WordTree<T>::callFind(T d, int& comparisons)
{
	int z = int(d[0]);
	if (find(d, root[z - int('a')], comparisons) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
Node<T>* WordTree<T>::find(T d, Node<T>* n, int& comparisons)
{
	if (n == nullptr)
	{
		return nullptr;
	}
	else if (d < n->data)
	{
		comparisons++;
		return find(d, n->left, comparisons);
	}
	else if (n->data < d)
	{
		comparisons++;
		return find(d, n->right, comparisons);
	}
	else
	{
		comparisons++;
		return n;
	}
}

template<class T>
Node<T>* WordTree<T>::findMin(Node<T>* n)
{
	if (n == nullptr)
	{
		return nullptr;
	}
	else if (n->left == nullptr)
	{
		return n;
	}

	return findMin(n->left);

}

template<class T>
Node<T>* WordTree<T>::findMax(Node<T>* n)
{
	if (n == nullptr)
	{
		return nullptr;
	}
	else if (n->right == nullptr)
	{
		return n;
	}
	return findMax(n->right);

}

template<class T>
int WordTree<T>::height(Node<T>* treeH)
{
	int h = 0;
	if (treeH != nullptr)
	{
		int l_height = height(treeH->left);
		int r_height = height(treeH->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

template<class T>
int WordTree<T>::difference(Node<T>* treeD)
{
	int l_height = height(treeD->left);
	int r_height = height(treeD->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

//right-right rotation
template<class T>
Node<T>* WordTree<T>::rr_rotate(Node<T>* parent)
{
	Node<T>* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	return t;
}

//left-left rotation
template<class T>
Node<T>* WordTree<T>::ll_rotate(Node<T>* parent)
{
	Node<T>* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	return t;
}

//left-right rotation
template<class T>
Node<T>* WordTree<T>::lr_rotate(Node<T>* parent)
{
	Node<T>* t;
	t = parent->left;
	parent->left = rr_rotate(t);
	return ll_rotate(parent);
}

//right-left rotation
template<class T>
Node<T>* WordTree<T>::rl_rotate(Node<T>* parent)
{
	Node<T>* t;
	t = parent->right;
	parent->right = ll_rotate(t);
	return rr_rotate(parent);
}

//use rotations to balance tree
template<class T>
Node<T>* WordTree<T>::balance(Node<T>* treeN)
{
	int bal_factor = difference(treeN);
	if (bal_factor > 1)
	{
		if (difference(treeN->left) > 0)
		{
			treeN = ll_rotate(treeN);
		}
		else
		{
			treeN = lr_rotate(treeN);
		}
	}
	else if (bal_factor < -1)
	{
		if (difference(treeN->right) > 0)
		{
			treeN = rl_rotate(treeN);
		}
		else
		{
			treeN = rr_rotate(treeN);
		}
	}
	return treeN;
}
