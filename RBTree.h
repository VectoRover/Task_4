#pragma once
using namespace std;
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
typedef enum { BLACK, RED } nodeColor;

template<class T>
class RBTree {
public:
	class CNode {
	public:
		string key;
		T data;
		nodeColor color;
		CNode* parent, * left, * right;
		CNode() { string = ""; T = T(); parent = left = right = NULL; color = RED; }
		CNode(const string& key, const T& data, typename RBTree<T>::CNode* parent) {
			this->parent = parent;
			this->data = data;
			left = right = NULL;
			red = 1;
			friend class RBTree<T>;
		}
	};
private:
	CNode* root;
public:
	RBTree() { root = NULL; }
	~RBTree() { Clean(); }
	void Clean() { while (Delete(root) == 0); }
	int Delete(typename RBTree<T>::CNode* n);
	typename RBTree<T>::CNode *findNode(const string &key);
	//typename RBTree<T>::CNode* grandparent(typename RBTree<T>::CNode* n);
	//typename RBTree<T>::CNode* uncle(typename RBTree<T>::CNode* n);
	void rotateLeft(typename RBTree<T>::CNode* x);
	void rotateRight(typename RBTree<T>::CNode* x);
    void insertFixup(typename RBTree<T>::CNode* x);
	void deleteFixup(typename RBTree<T>::CNode* x);
    typename RBTree<T>::CNode *insertNode(const string &key, const T &data);
	void deleteNode(const string& key, const T& data);


};

/*template<class T> typename RBTree<T>::CNode* RBTree<T>::grandparent(typename RBTree<T>::CNode* n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}


template<class T> typename RBTree<T>::CNode* RBTree<T>::uncle(typename RBTree<T>::CNode* n){
	typename RBTree<T>::CNode* g = grandparent(n);
	if (g == NULL)
		return NULL; // нет деда, значит нет дяди
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}*/


template<class T> void RBTree<T>::rotateLeft(typename RBTree<T>::CNode* x) {
	typename RBTree<T>::CNode* y = x->right;
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;
	if (y != NULL) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else {
		root = y;
	}
	y->left = x;
	if (x != NULL) x->parent = y;
}


template<class T> void RBTree<T>::rotateRight(typename RBTree<T>::CNode* x) {
	typename RBTree<T>::CNode* y = x->left;
	x->left = y->right;
	if (y->right != NULL) y->right->parent = x;
	if (y != NULL) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}
	y->right = x;
	if (x != NULL) x->parent = y;
}

template<class T> void RBTree<T>::insertFixup(typename RBTree<T>::CNode* x) {
	while (x != root && x->parent->color == RED) {
		/* нарушение красно- черных свойств */
		if (x->parent == x->parent->parent->left) {
			typename RBTree<T>::CNode* y = x->parent->parent->right;
			if (y->color == RED) {

				/* дядя красный */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {

				/* дядя черный */
				if (x == x->parent->right) {
					x = x->parent;
					rotateLeft(x);
				}

				/* перекраска и переворот */
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateRight(x->parent->parent);
			}
		}
		else {

			typename RBTree<T>::CNode* y = x->parent->parent->left;
			if (y->color == RED) {

				/* красный дядя */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {

				/* черный дядя */
				if (x == x->parent->left) {
					x = x->parent;
					rotateRight(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateLeft(x->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template<class T> void RBTree<T>::deleteFixup(typename RBTree<T>::CNode* x) {
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			typename RBTree<T>::CNode* w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rotateRight(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotateLeft(x->parent);
				x = root;
			}
		}
		else {
			typename RBTree<T>::CNode* w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					rotateLeft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotateRight(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

template<class T> void RBTree<T>::deleteNode(const string& key, const T& data) {
	typename RBTree<T>::CNode* x, * y;
	if (!z || z == NULL) return;
	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = z->right;
		while (y->left != NULL) y = y->left;
	}
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;
	if (y->parent)
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	else
		root = x;

	if (y != z) {
		z->key = y->key;
		z->data = y->data
	} 

	if (y->color == BLACK)
		deleteFixup(x);

	delete y;
}

template<class T> typename RBTree<T>::CNode* RBTree<T>::findNode(const string& key) {
	typename RBTree<T>::CNode* current = root;
	while (current != NULL)
		if (key == current->key)
			return (current);
		else
			current = key < current->key ?
			current->left : current->right;
	return NULL;
}


template<class T> typename RBTree<T>::CNode* RBTree<T>::insertNode(const string& key, const T& data) {
	//typename RBTree<T>::CNode* createNode
	typename RBTree<T>::CNode* current, * parent, *x;
	 /* ищем, куда вставлять */
	current = root;
	parent = 0;
	while (current != NULL) {
		if (key == current->key)) return (current);
		parent = current;
		current = key < current->key ? current->left : current->right;
	}


	if ((x = malloc(sizeof(*x))) == 0) {
		printf("Память не выделилась");
		exit(1);
	}
	//x = new typename RBTree<T>::CNode;
	x->key = key;
	x->data = data;
	x->parent = parent;
	x->left = NULL;
	x->right = NULL;
	x->color = RED;

	/* если ключ уже есть */
	if (parent) {
		if (key == parent->key)
			parent->left = x;
		else
			parent->right = x;
	}
	else {
		root = x;
	}

	insertFixup(x);
	return(x);
}

