#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node {
public:
	string data;
	int height;
	Node* left;
	Node* right;
	Node* parent;
	Node(string str) : data(str), height(0), left(0), right(0), parent(0){ };
};
#endif // !NODE_H
