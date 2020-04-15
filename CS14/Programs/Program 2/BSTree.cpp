#include "BSTree.h"

BSTree::BSTree() {
	root = nullptr;
}

void BSTree::insert(const string& str) {
	if (isEmpty()) {
		Node* node = new Node(str);
		root = node;
	}
	else {
		insert(root, str);
	}
}

void BSTree::insert(Node* node, const string& str) {
	if (str == node->getData()) {
		node->incrementCount();
		return;
	}
	else if (str < node->getData()) {
		if (node->getLeft() == nullptr) {
			Node* bread = new Node(str);
			node->setLeft(bread);
			bread->setParent(node);
			return;
		}
		insert(node->getLeft(), str);
	}
	else {
		if (node->getRight() == nullptr) {
			Node* bread = new Node(str);
			node->setRight(bread);
			bread->setParent(node);
			return;
		}
		insert(node->getRight(), str);
	}
}

bool BSTree::search(const string& str) const {
	if (isEmpty())
		return false;
	else {
		return search(root, str);
	}
}

bool BSTree::search(Node* node, const string& str) const {
	if (node == nullptr)
		return false;
	else {
		if (node->getData() == str)
			return true;
		else if (str < node->getData()) {
			return search(node->getLeft(), str);
		}
		else {
			return search(node->getRight(), str);
		}
	}
}

string BSTree::smallest() const {
	if (isEmpty()) {
		//throw underflow_error("Smallest() called on empty tree");
		return "";
	}
	return smallest(root);
}

string BSTree::smallest(Node* node) const {
	if (node == nullptr) {
		return "";
	}
	else if (node->getLeft() != nullptr) {
		return smallest(node->getLeft());
	}
	else if (node->getLeft() == nullptr)
		return node->getData();
	else
		return "";
}

string BSTree::largest() const {
	if (isEmpty()) {
		//throw underflow_error("Largest() called on empty tree");
		return "";
	}
	return largest(root);
}

string BSTree::largest(Node* node) const {
	if (node == nullptr) {
		return "";
	}
	else if (node->getRight() != nullptr) {
		return largest(node->getRight());
	}
	else if (node->getRight() == nullptr)
		return node->getData();
	else
		return "";
}

int BSTree::height(const string& str) const {
	return height(findNode(root, str));
}

int BSTree::height(Node* n) const{
	if (n == nullptr)
		return -1;
	int leftHeight = height(n->getLeft());
	int rightHeight = height(n->getRight());
	return 1 + max(leftHeight, rightHeight);
}

Node* BSTree::findNode(Node* n, const string& str) const{
	if (n == nullptr)
		return nullptr;
	if (n->getData() == str)
		return n;
	else if (str < n->getData()) {
		return findNode(n->getLeft(), str);
	}
	else {
		return findNode(n->getRight(), str);
	}
}

void BSTree::remove(const string& str) {
	if (isEmpty()) {
		//throw underflow_error("remove() called on empty tree");
		return;
	}
	else {
		remove(root, str);
	}
}

void BSTree::remove(Node* node, const string& str) {
	if (node == nullptr)
		return;
	else {
		if (node->getData() == str) {
			if (!node->hasChildren()) { //leaf node
				if (!node->hasParent()) { // root node
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						delete root;
						root = nullptr;
					}

					return;
				}
				else if (node->getParent()->getLeft() == node) {
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						node->getParent()->setLeft(nullptr);
						delete node;
					}

					return;
				}
				else {
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getParent();
						n->setRight(nullptr);
						node->setParent(nullptr);
						delete node;
						
					}
					return;
				}
			}
			else if (node->hasLeft() && !node->hasRight()) { // has only left
				if (!node->hasParent()) { //root
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getLeft();
						delete root;
						root = n;
						n->setParent(nullptr);
					}

					return;
				}
				else if (node->getParent()->getLeft() == node){
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getLeft();
						node->getParent()->setLeft(n);
						n->setParent(node->getParent());
						delete node;
					}

					return;
				}
				else {
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getRight();
						node->getParent()->setRight(n);
						n->setParent(node->getParent());
						delete node;
					}
					return;
				}
			}
			else if (!node->hasLeft() && node->hasRight()) { // has only right
				if (!node->hasParent()) { // root
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getRight();
						delete root;
						root = n;
						n->setParent(nullptr);
					}
					return;
				}
				else if (node->getParent()->getLeft() == node) {
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getRight();
						if (n->hasLeft()) {
							Node* sled = n;
							bool thing = false;
							while (n->hasLeft()) {
								n = n->getLeft();

								if (!thing && n->getLeft() && n->getLeft()->getLeft() == nullptr) {
									sled = n; thing = true;
								}
							}
							node->getParent()->setLeft(n);
							sled->setLeft(n->getRight());
							n->getRight()->setParent(sled);
							n->setRight(sled);
							sled->setParent(n);
							n->setParent(node->getParent());
							
							delete node;
						}
						else {
							node->getParent()->setLeft(n);
							n->setParent(node->getParent());
							delete node;
						}
					}
					return;
				}
				else {
					if (node->getCount() > 1) {
						node->decrementCount();
					}
					else {
						Node* n = node->getRight(); 
						while (n->hasLeft())
							n = n->getLeft();
						node->getParent()->setRight(n);
						n->setParent(node->getParent());
						delete node;
					}

					return;
				}
			}
			else { // has both children
				if (node->getCount() > 1) {
					node->decrementCount();
				}
				else {
					Node* succ = node->getLeft();
					while (succ->hasRight()) {
						succ = succ->getRight();
					}
					if (node->getParent() == nullptr) {
						
						node->getLeft()->setParent(succ);
						if (node->getLeft() != succ)
							succ->setLeft(node->getLeft());
						else {
							if (succ->hasChildren()) {
								Node* bread = node;
								while (bread->hasLeft())
									bread = bread->getLeft();
								while (bread->hasRight())
									bread = bread->getRight();
								Node* bP = bread->getParent();
								bP->setRight(0);
								bread->setParent(0);
								bread->setLeft(succ->getLeft());
								bread->setParent(succ);
								succ->setLeft(bread);
							}
						}
						succ->setRight(node->getRight());
						delete root;
						root = succ;
						succ->setParent(nullptr);

						return;
					}
					else {
						if (node->getParent()->getLeft() == node) {
							node->getParent()->setLeft(succ);
						}
						else if (node->getParent()->getRight() == node) {
							node->getParent()->setRight(succ);
						}
						if (succ->getParent()->getLeft() == succ) {
							Node* n = succ;
							succ->getParent()->setLeft(n->getLeft());
						}
						else if (succ->getParent()->getRight() == succ) {
							Node* n = succ;
							succ->getParent()->setRight(n->getRight());
						}
						succ->setRight(node->getRight());
						succ->setLeft(node->getLeft());
						
						succ->setParent(node->getParent());
						delete node;
					}
				}
			}
			return;
		}
		else if (str < node->getData()) {
			remove(node->getLeft(), str);
		}
		else {
			remove(node->getRight(), str);
		}
	}
}

void BSTree::preOrder() const {
	preOrder(root);
}

void BSTree::preOrder(Node* node) const{
	if (node == nullptr)
		return;
	else {
		cout << node->getData() << "(" << node->getCount() << ")" << ", ";
		preOrder(node->getLeft());
		preOrder(node->getRight());
	}
}

void BSTree::inOrder() const{
	inOrder(root);
}

void BSTree::inOrder(Node* node) const {
	if (node == nullptr)
		return;
	else if (!node->hasChildren()) {
		cout << node->getData() << "(" << node->getCount() << ")" << ", ";
	}
	else {
		inOrder(node->getLeft());
		cout << node->getData() << "(" << node->getCount() << ")" << ", ";
		inOrder(node->getRight());
	}
}

void BSTree::postOrder() const {
	postOrder(root);
}

void BSTree::postOrder(Node* node) const {
	if (node == nullptr)
		return;
	else {
		postOrder(node->getLeft());
		postOrder(node->getRight());
		cout << node->getData() << "(" << node->getCount() << ")" << ", ";
	}
}



