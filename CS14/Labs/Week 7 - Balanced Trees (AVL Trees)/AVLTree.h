#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class AVLTree {
private:
	Node* root;

	void insert(Node*, const string&);
	Node* findUnbalancedNode(Node*);
	void rotate(Node*);
	Node* rotateLeft(Node*);
	Node* rotateRight(Node*);
	void printBalanceFactors(Node*);
	void visualizeTree(ofstream&, Node*);
	int height(Node*) ;
	Node* findNode(Node*, const string&) const;
	void updateHeight(Node* node);
	bool setChild(Node* parent, string whichChild, Node* child);
	bool replaceChild(Node* parent, Node* currentChild, Node* newChild);
public:
	AVLTree();
	void insert(const string&);
	int balanceFactor(Node*);
	void printBalanceFactors();
	void visualizeTree(const string&);
};

#endif // !AVLTREE_H
