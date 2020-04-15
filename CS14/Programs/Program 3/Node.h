#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node {
	friend class Tree;
private:
	string smallData;
	string largeData;
	Node* left;
	Node* middle;
	Node* right;
	Node* parent;
public:
	Node(const string& s) :smallData(s), largeData(""), left(0), middle(0), right(0), parent(0) {};
	bool isTwo() {return largeData == "";}
	bool isThree() { return smallData != "" && largeData != "";}
	bool isLeaf() { return !left && !middle && !right; }
};
#endif // ! NODE_H
