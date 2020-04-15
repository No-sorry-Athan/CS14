#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node {
private:
	Node* left;
	Node* right;
	Node* parent;
	string data;
	int count;
public:
	Node(string s) :left(0), right(0),parent(0), data(s), count(1) {};
	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	Node* getParent() { return parent; }
	void incrementCount() { count++; }
	void decrementCount() { count--; }
	void setLeft(Node* n) { left = n; }
	void setRight(Node* n) { right = n; }
	void setParent(Node* n) { parent = n; }
	bool hasLeft() { return left != nullptr; }
	bool hasRight() { return right != nullptr; }
	bool hasChildren() { return (left != nullptr) || (right != nullptr); }
	bool hasParent() { return parent != nullptr; }
	string getData() { return data; }
	int getCount() { return count; }
};

#endif