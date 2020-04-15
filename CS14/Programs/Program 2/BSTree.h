#ifndef BSTREE_H
#define BSTREE_H
#include "Node.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

class BSTree {
private:
	Node* root;

	void preOrder(Node*)const;
	void inOrder(Node*)const;
	void postOrder(Node*)const;
	void insert(Node*, const string&);
	bool search(Node*, const string&) const;
	void remove(Node*, const string&);
	string smallest(Node*) const;
	string largest(Node*) const;
	Node* findNode(Node*, const string&) const;
	int height(Node*) const;
public:
	BSTree();
	void insert(const string&);
	bool search(const string&) const;
	string largest() const;
	string smallest() const;
	int height(const string&) const;
	void remove(const string&);

	bool isEmpty() const { return root == nullptr; }
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
};


#endif