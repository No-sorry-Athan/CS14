#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "Node.h"
using namespace std;

class Tree {
private:
	Node* root;
	void preOrder(Node*) const;
	void inOrder(Node*) const;
	void postOrder(Node*) const;
	
	void split(Node*, const string&);

	void insert(Node*, const string&);
	void fix(Node*, Node*);
	Node* search(Node*, const string&);
	Node* findSucc(Node*, const string&);

	bool validNode(Node*);
public:
	Tree();
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;

	void insert(const string&);
	void remove(const string&);
	bool search(const string&);
};

#endif // !TREE_H
