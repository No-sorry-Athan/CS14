#include "arithmeticExpression.h"
#include <stack>
#include <fstream>
#include <sstream>

bool isOperand(const char c) {
	return (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')');
}

arithmeticExpression::arithmeticExpression(const string& exp) {
	infixExpression = exp;
	root = nullptr;
}

void arithmeticExpression::buildTree() {
	string postfixString = infix_to_postfix();
	stack<TreeNode*> stack;
	char c;
	char currentKey = 'a';

	for (size_t i = 0; i < postfixString.size(); i++) {
		c = postfixString.at(i);
		if (c != '*' && c != '/' && c != '+' && c != '-' && c != '(' && c != ')') {
			stack.push(new TreeNode(c, currentKey));
			currentKey++;
		}
		else if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')') {
			TreeNode* right = stack.top();
			stack.pop();
			TreeNode* left = stack.top();
			stack.pop();
			TreeNode* newNode = new TreeNode(c, currentKey);
			currentKey++;
			newNode->left = left;
			newNode->right = right;
			stack.push(newNode);
		}
	}
	TreeNode* currentTop = stack.top();
	root = currentTop;
	stack.pop();

}

void arithmeticExpression::infix() {
	infix(root);
}

void arithmeticExpression::prefix() {
	prefix(root);
}

void arithmeticExpression::postfix() {
	postfix(root);
}

void arithmeticExpression::visualizeTree(const string& outputFilename) {
	ofstream outFS(outputFilename.c_str());
	if (!outFS.is_open()) {
		cout << "Error opening " << outputFilename << endl;
		return;
	}
	outFS << "digraph G {" << endl;
	visualizeTree(outFS, root);
	outFS << "}";
	outFS.close();
	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
	//system(command.c_str());
}

// private helpers

bool arithmeticExpression::isLeaf(TreeNode* node) {
	return (node && node->left == nullptr && node->right == nullptr);
}

int arithmeticExpression::priority(char op) {
	int priority = 0;
	if (op == '(') {
		priority = 3;
	}
	else if (op == '*' || op == '/') {
		priority = 2;
	}
	else if (op == '+' || op == '-') {
		priority = 1;
	}
	return priority;
}

string arithmeticExpression::infix_to_postfix() {
	stack<char> s;
	ostringstream oss;
	char c;
	
	for (unsigned i = 0; i < infixExpression.size(); ++i) {
		c = infixExpression.at(i);
		if (c == ' ') {
			continue;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
			if (c == '(') {
				s.push(c);
			}
			else if (c == ')') {
				while (s.top() != '(') {
					oss << s.top();
					s.pop();
				}
				s.pop();
			}
			else {
				while (!s.empty() && priority(c) <= priority(s.top())) {
					if (s.top() == '(') {
						break;
					}
					oss << s.top();
					s.pop();
				}
				s.push(c);
			}
		}
		else { //c is an operand
			oss << c;
		}
	}
	while (!s.empty()) {
		oss << s.top();
		s.pop();
	}
	return oss.str();
}



void arithmeticExpression::infix(TreeNode* node) {
	if (node == nullptr) {
		return;
	}
	if (isLeaf(node)) {
		cout << node->data;
	}
	else {
		cout << "(";
		infix(node->left);
		cout << node->data;
		infix(node->right);
		cout << ")";
	}
}

void arithmeticExpression::prefix(TreeNode* node) {
	if (node == nullptr) {
		return;
	}
	cout << node->data;
	prefix(node->left);
	prefix(node->right);
}

void arithmeticExpression::postfix(TreeNode* node) {
	if (node == nullptr) {
		return;
	}
	postfix(node->left);
	postfix(node->right);
	cout << node->data;
}

void arithmeticExpression::visualizeTree(ofstream& ofs, TreeNode* node) {
	if (node == nullptr)
		return;
	if (isLeaf(node)) {
		ofs << node->data << endl;
		return;
	}
	else {
		if (node->left) {
			if (isOperand(node->data)) {
				ofs << "\"" << node->data << "\"" << "->"; 
			}
			else {
				ofs << node->data << "->";
			}
			if (isOperand(node->left->data)) {
				ofs << "\"" << node->left->data << "\"" << endl;
			}
			else {
				ofs << node->left->data << endl;
			}
		}
		if (node->right) {
			if (isOperand(node->data)) {
				ofs << "\"" << node->data << "\"" << "->";
			}
			else {
				ofs << node->data << "->";
			}
			if (isOperand(node->right->data)) {
				ofs << "\"" << node->right->data << "\"" << endl;
			}
			else {
				ofs << node->right->data << endl;
			}
		}
		visualizeTree(ofs, node->left);
		visualizeTree(ofs, node->right);
	}

}