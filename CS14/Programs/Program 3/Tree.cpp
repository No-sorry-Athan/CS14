#include "Tree.h"

Tree::Tree() {
	root = nullptr;
}

void Tree::insert(const string& str) {
	if (root == nullptr) { //empty
		root = new Node(str);
	}
	else {
		insert(root, str);
	}
}

void Tree::split(Node* n, const string& str) {
	if (n->parent == nullptr) { // splitting at root
		if (str > n->smallData&& str < n->largeData) {
			Node* middle = new Node(str);
			Node* left = new Node(n->smallData);
			Node* right = new Node(n->largeData);
			middle->left = left;
			middle->right = right;
			left->parent = middle;
			right->parent = middle;
			left->left = n->left;
			right->right = n->right;
			delete n;
			root = middle;
		}
		else if (str < n->smallData) {
			Node* middle = new Node(n->smallData);
			Node* left = new Node(str);
			Node* right = new Node(n->largeData);
			middle->left = left;
			middle->right = right;
			left->parent = middle;
			right->parent = middle;
			left->left = n->left;
			right->right = n->right;
			delete n;
			root = middle;
		}
		else if (str > n->largeData) {
			Node* middle = new Node(n->largeData);
			Node* left = new Node(n->smallData);
			Node* right = new Node(str);
			middle->left = left;
			middle->right = right;
			left->parent = middle;
			right->parent = middle;
			left->left = n->left;
			right->right = n->right;
			delete n;
			root = middle;
		}
	}
	else {
		if (str > n->smallData&& str < n->largeData) {	// str mid		
			if (n->largeData == "") {
				if (n->parent->smallData < str)
					n->parent->largeData = str;
				else {
					n->parent->largeData = n->parent->smallData;
					n->parent->smallData = str;
				}
				Node* mid = new Node(n->smallData);
				n->parent->middle = mid;
				mid->parent = n->parent;
				n->smallData = n->largeData;
				n->largeData = "";
			}
			else {
				Node* newPar = new Node(str);
				newPar->parent = n->parent->parent;
				Node* parLeft = new Node(n->parent->smallData);
				parLeft->left = n->parent->left;
				if (n->parent->left) {
					n->parent->left->parent = parLeft;
				}
				Node* tempRight = new Node(n->smallData);
				parLeft->right = tempRight;
				tempRight->parent = parLeft;


				Node* parRight = new Node(n->parent->largeData);
				parRight->right = n->parent->right;
				if (n->parent->right) {
					n->parent->right->parent = parRight;
				}
				Node* tempLeft = new Node(n->largeData);
				parRight->left = tempLeft;
				tempLeft->parent = parRight;



				if (newPar->parent == nullptr)
					root = newPar;
				newPar->left = parLeft;
				newPar->right = parRight;
				parLeft->parent = newPar;
				parRight->parent = newPar;
			}

		}
		else if (str < n->smallData) { // small mid
			if (n->largeData == "") {
				if (n->parent->smallData < n->smallData)
					n->parent->largeData = n->smallData;
				else {
					n->parent->largeData = n->parent->smallData;
					n->parent->smallData = n->smallData;
				}
				Node* mid = new Node(str);
				n->parent->middle = mid;
				mid->parent = n->parent;
				n->smallData = n->largeData;
				n->largeData = "";
			}
			else {
				Node* newPar = new Node(n->smallData);
				newPar->parent = n->parent->parent;
				Node* parLeft = new Node(n->parent->smallData);
				parLeft->left = n->parent->left;
				if (n->parent->left) {
					n->parent->left->parent = parLeft;
				}
				Node* tempRight = new Node(str);
				parLeft->right = tempRight;
				tempRight->parent = parLeft;
				bool flag = false;
				if (n->parent->middle != n && tempRight->smallData > tempRight->parent->smallData) {
					parLeft->right = nullptr;
					flag = true;
				}


				Node* parRight = new Node(n->parent->largeData);
				parRight->right = n->parent->right;
				if (n->parent->right) {
					n->parent->right->parent = parRight;
				}
				Node* tempLeft = new Node(n->largeData);
				parRight->left = tempLeft;
				tempLeft->parent = parRight;
				if (n->parent->middle != n && flag) {
					parRight->right->smallData = str;
				}

				if (newPar->parent == nullptr)
					root = newPar;
				newPar->left = parLeft;
				newPar->right = parRight;
				parLeft->parent = newPar;
				parRight->parent = newPar;

			}
		}
		else if (str > n->largeData) { // large mid
			if (n->largeData == "") {
				if (n->parent->smallData < n->largeData)
					n->parent->largeData = n->largeData;
				else {
					n->parent->largeData = n->parent->smallData;
					n->parent->smallData = n->largeData;
				}
				Node* mid = new Node(n->smallData);
				n->parent->middle = mid;
				mid->parent = n->parent;
				n->smallData = str;
				n->largeData = "";
			}
			else {
				if (n->parent->right != n) {
					Node* newPar = new Node(n->largeData);
					newPar->parent = n->parent->parent;
					Node* parLeft = new Node(n->parent->smallData);
					parLeft->left = n->parent->left;
					if (n->parent->left) {
						n->parent->left->parent = parLeft;
					}

					Node* tempRight = new Node(n->smallData);
					parLeft->right = tempRight;
					tempRight->parent = parLeft;
					if (n->parent->middle) {
						if (n != n->parent->middle) {
							parLeft->right = new Node(n->parent->middle->smallData);
						}
					}


					Node* parRight = new Node(n->parent->largeData);
					parRight->right = n->parent->right;
					if (n->parent->right) {
						n->parent->right->parent = parRight;
					}
					Node* tempLeft = new Node(str);
					parRight->left = tempLeft;
					tempLeft->parent = parRight;

					if (newPar->parent == nullptr)
						root = newPar;
					newPar->left = parLeft;
					newPar->right = parRight;
					parLeft->parent = newPar;
					parRight->parent = newPar;
					if (n->parent->parent->parent) {
						if (n->parent->parent->parent->right->largeData == n->parent->smallData) {
							n->parent->parent->parent->right = newPar;
						}
					}
					if (n->parent == n->parent->parent->left) {
						n->parent->parent->left = newPar;
					}
				}
				else {
					Node* newParent = new Node(n->parent->largeData);
					newParent->parent = n->parent->parent;
					Node* left = new Node(n->parent->smallData);
					left->left = n->parent->left;
					if (n->parent->left) {
						left->left->parent = left;
						if (n->parent->middle) {
							Node* sPRight = new Node(n->parent->middle->smallData);
							left->right = sPRight;
							sPRight->parent = left;
						}
					}
					Node* right = new Node(n->largeData);
					newParent->right = right;
					Node* nL = new Node(n->smallData);
					right->left = nL;
					Node* nR = new Node(str);
					right->right = nR;
					nR->parent = right;
					nL->parent = right;
					newParent->left = left;
					if (newParent->parent == nullptr) {
						root = newParent;
					}
					else {
						newParent->parent->right = newParent;
					}
					right->parent = newParent;
					left->parent = newParent;
					n->parent = newParent;

				}
			}

		}
	}
}

void Tree::insert(Node* n, const string& str) {
	if (n == nullptr) {
		return;
	}
	if (str == n->smallData || str == n->largeData)
		return;
	if (n->isLeaf()) {
		if (n->largeData == "") {
			if (str > n->smallData)
				n->largeData = str;
			else {
				n->largeData = n->smallData;
				n->smallData = str;
			}
			return;
		}
		else if (n->parent && n->parent->largeData == "") {
			if (str > n->largeData) {
				if (n->parent->left != n) {
					if (n->largeData > n->parent->smallData) {
						n->parent->largeData = n->largeData;
					}
					else {
						n->parent->largeData = n->parent->smallData;
						n->parent->smallData = n->largeData;
					}

					if (n->parent->middle) {
						if (n->parent->middle->largeData == "") {
							if (n->parent->middle->smallData < n->smallData) {
								n->parent->middle->largeData = n->smallData;
							}
							else {
								n->parent->middle->largeData = n->parent->middle->smallData;
								n->parent->middle->smallData = n->smallData;
							}
						}
					}
					else {
						Node* newN = new Node(n->smallData);
						n->parent->middle = newN;
						newN->parent = n->parent;
						n->smallData = str;
					n->largeData = "";
					}
				}
				else {
					if (n->largeData > n->parent->smallData) {
						n->parent->largeData = n->largeData;
					}
					else {
						n->parent->largeData = n->parent->smallData;
						n->parent->smallData = n->largeData;
					}

					if (n->parent->middle) {
						if (n->parent->middle->largeData == "") {
							if (n->parent->middle->smallData < str) {
								n->parent->middle->largeData = str;
							}
							else {
								n->parent->middle->largeData = n->parent->middle->smallData;
								n->parent->middle->smallData = str;
							}
						}
					}
					else {
						Node* newN = new Node(str);
						n->parent->middle = newN;
						newN->parent = n->parent;
						n->largeData = "";
					}
				}
				//newN->left = n->parent->middle;
				
			}
			else if (str < n->smallData) {
				if (n == n->parent->left) {
					if (n->smallData > n->parent->smallData) {
						n->parent->largeData = n->smallData;
					}
					else {
						n->parent->largeData = n->parent->smallData;
						n->parent->smallData = n->smallData;
					}
					if (n->parent->middle) {
						if (n->parent->middle->largeData == "") {
							if (n->parent->middle->smallData < n->largeData) {
								n->parent->middle->largeData = n->largeData;
							}
							else {
								n->parent->middle->largeData = n->parent->middle->smallData;
								n->parent->middle->smallData = n->largeData;
							}
						}
					}
					else {
						Node* newN = new Node(n->largeData);
						n->parent->middle = newN;
						newN->parent = n->parent;
					}
					n->smallData = str;
					n->largeData = "";
				}
				else if (n == n->parent->right) {
					if (n->smallData > n->parent->smallData) {
						n->parent->largeData = n->smallData;
					}
					else {
						n->parent->largeData = n->parent->smallData;
						n->parent->smallData = n->smallData;
					}
					if (n->parent->middle) {
						if (n->parent->middle->largeData == "") {
							if (n->parent->middle->smallData < str) {
								n->parent->middle->largeData = str;
							}
							else {
								n->parent->middle->largeData = n->parent->middle->smallData;
								n->parent->middle->smallData = str;
							}
						}
					}
					else {
						Node* newN = new Node(str);
						n->parent->middle = newN;
						newN->parent = n->parent;
					}
					n->smallData = n->largeData;
					n->largeData = "";
				}
				//Node* newMid = new Node(n->largeData);
				/*if (n->parent->parent->left == n->parent) {
					n->parent->parent->left = newMid;
					newMid->parent = n->parent->parent;
				}*/

				/*Node* newLeft = new Node(n->parent->smallData);
				newLeft->left = n;
				Node* newRight = new Node(n->parent->largeData);
				newRight->right = n->parent->right;
				newRight->right->parent = newRight;
				newMid->left = newLeft;
				newMid->right = newRight;
				n->parent = newLeft;
				newLeft->parent = newMid;
				newRight->parent = newMid;*/


			}
			else if (str > n->smallData&& str < n->largeData) {
				if (str > n->parent->smallData) {
					n->parent->largeData = str;
				}
				else {
					n->parent->largeData = n->parent->smallData;
					n->parent->smallData = str;
				}
				//Node* newMid = new Node(str);

				if (n->parent->middle) {
					if (n->parent->middle->largeData == "") {
						if (n->parent->middle->smallData < n->largeData) {
							n->parent->middle->largeData = n->largeData;
						}
						else {
							n->parent->middle->largeData = n->parent->middle->smallData;
							n->parent->middle->smallData = n->largeData;
						}
					}
				}
				else {
					Node* newN = new Node(n->largeData);
					n->parent->middle = newN;
					newN->parent = n->parent;
				}
				/*if (n->parent->parent->right == n->parent) {
					n->parent->parent->right = newMid;
					newMid->parent = n->parent->parent;
				}*/
				n->largeData = "";
				/*Node* newLeft = new Node(n->parent->smallData);
				newLeft->left = n;
				Node* newRight = new Node(n->parent->largeData);
				newRight->right = n->parent->right;
				newRight->right->parent = newRight;
				newMid->left = newLeft;
				newMid->right = newRight;
				n->parent = newLeft;
				newLeft->parent = newMid;
				newRight->parent = newMid;*/

			}
			return;
		}
		else {
			split(n, str);
			return;
		}
	}
	if (n->isThree()) {
		if (str < n->smallData) {
			if (n->left)
				insert(n->left, str);
		}
		else if (str > n->largeData) {
			if (n->right)
				insert(n->right, str);
		}
		else if (str > n->smallData&& str < n->largeData) {
			if (n->middle)
				insert(n->middle, str);
			else {
				Node* newN = new Node(str);
				n->middle = newN;
				newN->parent = n;
			}
		}
	}
	else if (n->isTwo()) {
		if (str < n->smallData) {
			if (n->left)
				insert(n->left, str);
			else {
				if (n->largeData == "") {
					n->largeData = n->smallData;
					n->smallData = str;
				}
			}
		}
		else if (str > n->smallData) {
			if (n->right)
				insert(n->right, str);
			else {
				if (n->largeData == "")
					n->largeData = str;
			}
		}
	}
}

Node* Tree::findSucc(Node* node, const string& str) {
	Node* succ = node;
	if (node->middle && node->smallData == str) {
		succ = succ->middle;
	}
	else if (node->left) {
		succ = succ->left;
	}
	while (succ->right)
		succ = succ->right;

	return succ;
}

void Tree::remove(const string& str) {
	Node* curr = search(root, str);
	if (!curr) 
		return;
	Node* leaf = nullptr;
	if (curr) {
		if (!curr->isLeaf()) {
			Node* succ = findSucc(curr, str);
			if (curr->smallData == str) {
				swap(curr->smallData, succ->smallData);
			}
			else if (curr->largeData == str){
				swap(curr->largeData, succ->largeData);
			}
			leaf = succ;
		}
		else {
			leaf = curr;
		}

		if (str == leaf->largeData) {
			leaf->largeData = "";
		}
		else if (str == leaf->smallData) {
			leaf->smallData = leaf->largeData;
			leaf->largeData = "";
		}
		if (leaf->smallData == "") {
			fix(leaf, 0);
		}
	}
}

bool Tree::validNode(Node* n) {
	return n != nullptr;
}

void Tree::fix(Node* n, Node* bread)
{
	if (!validNode(n))
		return;
	if (n == root) {
		if (!n->isLeaf()) {
			root = bread;
		}
		else {
			root = nullptr;
		}
		return;
	}
	if (n->parent->left->isTwo() && n->parent->middle->isTwo() && n->parent->right->isTwo()) {
		if (n->parent->left == n) {
			Node* nP = n->parent;
			n->smallData = nP->smallData;
			if (nP->largeData == "") {
				n->largeData = nP->right->smallData;
				nP->smallData = "";
				if (validNode(bread)) {
					n->left = bread;
					bread->parent = n;
					n->middle = nP->right->left;
					n->middle->parent = n;
					n->right = nP->right->right;
					n->right->parent = n;
				}
				nP->right = nullptr;
				nP->largeData = "";
				fix(nP, n);
			}
			else {
				n->largeData = nP->middle->smallData;
				nP->smallData = nP->largeData;
				nP->largeData = "";
				if (validNode(bread)) {
					n->left = bread;
					bread->parent = n;
					n->middle = nP->middle->left;
					n->middle->parent = n;
					n->right = nP->middle->right;
					n->right->parent = n;
				}
				nP->middle = nullptr;
			}
		}
		else if (n->parent->right == n) {
			Node* nP = n->parent;
			if (n->parent->largeData == "") {
				nP->left->largeData = nP->smallData;
				nP->smallData = "";
				nP->right = nullptr;
				if (validNode(bread)) {
					nP->left->middle = nP->left->right;
					nP->left->middle->parent = nP->left->right;
					nP->left->right = bread;
					bread->parent = nP->left;
				}
				fix(nP, nP->left);
			}
			else {
				n->largeData = nP->largeData;
				nP->largeData = "";
				n->smallData = nP->middle->smallData;
				if (validNode(bread)) {
					n->right = bread;
					bread->parent = n;
					n->middle = nP->middle->right;
					n->middle->parent = n;
					n->left = nP->middle->left;
					n->left->parent = n;
				}
				nP->middle = nullptr;
			}
		}
		else if (n->parent->middle == n) {
			Node* nP = n->parent;
			nP->left->largeData = nP->smallData;
			nP->smallData = nP->largeData;
			nP->largeData = "";
			if (validNode(bread)) {
				nP->left->middle = nP->left->right;
				nP->left->middle->parent = nP->left;
				nP->left->right = bread;
				bread->parent = nP->left;
			}
			nP->middle = nullptr;
		}
		return;
	}
	else if (n->parent->left->isThree() || n->parent->middle->isThree() || n->parent->right->isThree()) {
		if (n->parent->left == n) {
			Node* nP = n->parent;
			n->smallData = nP->smallData;
			if (nP->largeData == "") {
				nP->smallData = nP->right->smallData;
				nP->right->smallData = nP->right->largeData;
				nP->right->largeData = "";
				if (validNode(bread)) {
					n->left = bread;
					bread->parent = n;
					n->right = nP->right->left;
					n->right->parent = n;
					nP->right->left = nP->right->middle;
					nP->right->left->parent = nP->right;
					nP->right->middle = nullptr;
				}
				nP->right = nullptr;
				fix(nP, n);
			}
			else if (nP->largeData != ""){
				nP->smallData = nP->middle->smallData;
				if (nP->middle->largeData == "")
				{
					nP->middle->smallData = nP->largeData;
					nP->largeData = nP->right->smallData;
					nP->right->smallData = nP->right->largeData;
					nP->right->largeData = "";
					if (validNode(bread))
					{
						n->left = bread;
						bread->parent = n;
						n->right = nP->middle->left;
						n->right->parent = n;
						nP->middle->left = nP->middle->right;
						nP->middle->left->parent = nP->middle;
						nP->middle->right = nP->right->left;
						nP->middle->right->parent = nP->middle;
						nP->right->left = nP->right->middle;
						nP->right->left->parent = nP->right;
						nP->right->middle = nullptr;
					}
				}
				else if (nP->middle->largeData != "")
				{
					nP->middle->smallData = nP->middle->largeData;
					nP->middle->largeData = "";
					if (validNode(bread))
					{
						n->left = bread;
						bread->parent = n;
						n->right = nP->middle->left;
						n->right->parent = n;
						nP->middle->left = nP->middle->right;
						nP->middle->left->parent = nP->middle;
						nP->middle->right = nP->right->left;
						nP->middle->right->parent = nP->middle;
						nP->right->left = nP->right->middle;
						nP->right->left->parent = nP->right;
						nP->right->middle = nullptr;
					}
				}
			}
		}
	else if (n->parent->right == n) {
			Node* nP = n->parent;
			if (nP->largeData == "") {
				nP->left->largeData = nP->smallData;
				nP->smallData = "";
				nP->right = nullptr;
				if (validNode(bread)) {
					nP->left->middle = nP->left->right;
					nP->left->middle->parent = nP->left;
					nP->left->right = bread;
					bread->parent = nP->left;
				}
				fix(nP, nP->left);
			}
			else if (nP->largeData != ""){
				nP->right->smallData = nP->largeData;
				if (nP->middle->largeData == "")
				{
					nP->largeData = nP->middle->smallData;
					nP->middle->smallData = nP->smallData;
					nP->smallData = nP->left->largeData;
					nP->left->largeData = "";
					if (validNode(bread))
					{
						n->right = bread;
						bread->parent = n;
						n->left = nP->middle->right;
						n->left->parent = n->right;
						nP->middle->right = nP->middle->left;
						nP->middle->right->parent = nP->middle;
						nP->middle->left = nP->left->right;
						nP->middle->left->parent = nP->middle;
						nP->left->right = nP->left->middle;
						nP->left->right->parent = nP->left;
						nP->left->middle = nullptr;
					}
				}
				else if (nP->middle->largeData != "")
				{
					nP->largeData = nP->middle->largeData;
					nP->middle->largeData = "";
					if (validNode(bread))
					{
						n->right = bread;
						bread->parent = n;
						n->left = nP->middle->right;
						n->left->parent = n;
						nP->middle->right = nP->middle->middle;
						nP->middle->right->parent = nP->middle;
						nP->middle->middle = nullptr;
					}
				}
			}
		}
	else {
		Node* nP = n->parent;
		if (nP->right->largeData == "")
		{
			nP->middle->smallData = nP->smallData;
			nP->smallData = nP->left->largeData;
			nP->left->largeData = "";
			if (validNode(bread)) {
				n->right = bread;
				bread->parent = n;
				n->left = nP->left->right;
				n->left->parent = n;
				nP->left->right = nP->left->middle;
				nP->left->right->parent = nP->left;
				nP->left->middle = nullptr;
			}
		}
		else if (nP->right->largeData != "")
		{
			n->smallData = nP->largeData;
			nP->largeData = nP->right->smallData;
			nP->right->smallData = nP->right->largeData;
			nP->right->largeData = "";
			if (validNode(bread))
			{
				n->left = bread;
				bread->parent = n;
				n->right = nP->right->left;
				n->right->parent = n;
				nP->right->left = nP->right->middle;
				nP->right->left->parent = nP->right;
				nP->right->middle = nullptr;
			}
		}
	}
		return;
}
	else {
		if (n->parent->left->isLeaf()) {
			if (n->parent->left == n) {
				n->parent->left = nullptr;
				n->parent->left = new Node(n->parent->smallData);
				n->parent->left->parent = n->parent;
				n->parent->smallData = n->parent->largeData;
				n->parent->largeData = "";
			}
		}
		else if (n->parent->right->isLeaf()) {
			if (n->parent->right == n) {
				n->parent->right = nullptr;
				n->parent->right = new Node(n->parent->largeData);
				n->parent->right->parent = n->parent;
				n->parent->largeData = "";
			}
		}
		else if (n->parent->isThree()) {
			if (n->parent->middle->isLeaf()) {
				if (n->parent->middle == n) {
					if (n->parent->right->largeData == "") {
						n->parent->right->largeData = n->parent->largeData;
						n->parent->largeData = "";
						n->parent->middle = nullptr;
					}
					else if (n->parent->left->largeData == "") {
						n->parent->left->largeData = n->parent->smallData;
						n->parent->smallData = n->parent->largeData;
						n->parent->largeData = "";
						n->parent->middle = nullptr;
					}
				}
			}
		}
	}
}

bool Tree::search(const string& str) {
	return search(root, str);
}

Node* Tree::search(Node* n, const string& str) {
	if (!n)
		return nullptr;
	else {
		if (n->smallData == str || n->largeData == str) {
			return n;
		}
		else if (str < n->smallData && n->left) {
			return search(n->left, str);
		}
		else if (str > n->largeData&& n->right) {
			return search(n->right, str);
		}
		else if (str > n->smallData&& str < n->largeData && n->middle) {
			return search(n->middle, str);
		}
	}
	return nullptr;
}

void Tree::preOrder() const {
	preOrder(root);
	cout << endl;
}

void Tree::preOrder(Node* n) const {
	if (!n)
		return;
	else {
		if (n->isTwo()) {
			cout << n->smallData << ", ";
			preOrder(n->left);
			preOrder(n->right);
		}
		else if (n->isThree()) {
			cout << n->smallData << ", ";
			preOrder(n->left);
			cout << n->largeData << ", ";
			preOrder(n->middle);
			preOrder(n->right);
		}
	}
}

void Tree::inOrder() const {
	inOrder(root);
	cout << endl;
}

void Tree::inOrder(Node* n) const {
	if (!n)
		return;
	else {
		if (n->isTwo()) {
			inOrder(n->left);
			cout << n->smallData << ", ";
			inOrder(n->right);
		}
		else if (n->isThree()) {
			inOrder(n->left);
			cout << n->smallData << ", ";
			inOrder(n->middle);
			cout << n->largeData << ", ";
			inOrder(n->right);
		}
	}
}

void Tree::postOrder() const {
	postOrder(root);
	cout << endl;
}

void Tree::postOrder(Node* n) const {
	if (!n)
		return;
	else {
		if (n->isTwo()) {
			postOrder(n->left);
			postOrder(n->right);
			cout << n->smallData << ", ";
		}
		else if (n->isThree()) {
			postOrder(n->left);
			postOrder(n->middle);
			cout << n->smallData << ", ";
			postOrder(n->right);
			cout << n->largeData << ", ";
		}
	}
}