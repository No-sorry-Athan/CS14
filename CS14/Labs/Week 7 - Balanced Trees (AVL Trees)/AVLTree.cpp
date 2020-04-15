#include "AVLTree.h"

AVLTree::AVLTree() {
    root = nullptr;
}

Node* AVLTree::findUnbalancedNode(Node* node) {
    if (node == nullptr)
        return nullptr;

    int balFac = balanceFactor(node);
    if (balFac == 2 || balFac == -2) {
        return node;
    }
    return findUnbalancedNode(node->parent);
}

void AVLTree::rotate(Node* node) {
    int bFactor = balanceFactor(node);
    int bFactorL = balanceFactor(node->left);
    int bFactorR = balanceFactor(node->right);
    //cout << bFactor << " " << bFactorL << " " << bFactorR << endl;
    if (bFactor == 2) {
        if (bFactorL == 1 || bFactorR == 1) {
            rotateRight(node);
        }
        else if (bFactorL == 2 || bFactorR == 2) {
            rotateLeft(node->left);
        }
        else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else {
        if (bFactorL == -1 || bFactorR == -1) {
            rotateLeft(node);
        }
        else if (bFactorL == -2 || bFactorR == -2) {
            rotateRight(node->right);
        }
        else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}

void AVLTree::updateHeight(Node* node) {

    int leftHeight = -1;
    if (node->left != nullptr)
        leftHeight = node->left->height;
    int rightHeight = -1;
    if (node->right != nullptr)
        rightHeight = node->right->height;

    node->height = 1 + max(leftHeight, rightHeight);
}

bool AVLTree::setChild(Node* parent, string whichChild, Node* child) {
    if (!parent)
        return false;
    if (whichChild != "left" && whichChild != "right")
        return false;
    if (whichChild == "left") {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    if (child != nullptr) {
        if (child->parent) {
            if (child->parent->left == child)
                child->parent->left = nullptr;
        }
        else if (child->parent) {
            if (child->parent->right == child)
                child->parent->right = nullptr;
        }
        child->parent = parent;
    }
    updateHeight(parent);
    return true;
}

bool AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent->left == currentChild)
        return setChild(parent, "left", newChild);
    else if (parent->right == currentChild)
        return setChild(parent, "right", newChild);
    return false;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* rightLeftChild = nullptr;
    if (node->right) {
        rightLeftChild = node->right->left;
    }
    if (node->parent != nullptr) {
        if (node->right == nullptr) {
            Node* succ = node->left;
            while (succ->right != nullptr)
                succ = succ->right;
            replaceChild(node->parent, node, succ);

            succ->right = node;
            node->parent = succ;
            succ->left = node->left;
            node->left = nullptr;
            return succ;
        }
        else replaceChild(node->parent, node, node->right);
    }
    else {
        root = node->right;
        root->parent = nullptr;
    }
    setChild(node->right, "left", node);
    if (node->right == node->parent)
        node->right = nullptr;
    setChild(node, "right", rightLeftChild);
    return node;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* leftNode = node->left;
    Node* leftRightChild = nullptr;
    if (node->left) {
        leftRightChild = node->left->right;
    }
    if (node->parent != nullptr)
    {
        if (node->left == nullptr) {
            Node* succ = node->right;
            while (succ->left != nullptr)
                succ = succ->left;
            replaceChild(node->parent, node, succ);


            succ->left = node;
            node->parent = succ;
            succ->right = node->right;
            node->right = nullptr;
            return succ;
        }
        else replaceChild(node->parent, node, node->left);
    }
    else {
        root = node->left;
        root->parent = nullptr;
    }

    setChild(leftNode, "right", node);
    node->parent->right = node;
    setChild(node, "left", leftRightChild);
    return node;
}


void AVLTree::insert(const string& str) {
    if (root == nullptr) {
        root = new Node(str);
    }
    else {
        insert(root, str);
    }
}

void AVLTree::insert(Node* node, const string& str) {
    if (str == node->data) {
        return;
    }
    else if (str < node->data) {
        if (node->left == nullptr) {
            Node* bread = new Node(str);
            node->left = bread;
            bread->parent = node;

            Node* maccaroni = bread;
            Node* n = findUnbalancedNode(maccaroni);
            if (n != nullptr)
                rotate(n);

            return;
        }
        insert(node->left, str);
    }
    else {
        if (node->right == nullptr) {
            Node* bread = new Node(str);
            node->right = bread;
            bread->parent = node;

            Node* maccaroni = bread;
            Node* n = findUnbalancedNode(maccaroni);
            if (n != nullptr)
                rotate(n);

            return;
        }
        insert(node->right, str);
    }
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* node) {
    if (node == nullptr) {
        return;
    }
    else {
        printBalanceFactors(node->left);
        cout << node->data << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->right);
    }

}

int AVLTree::height(Node* n) {
    if (n == nullptr)
        return -1;
    int leftHeight = height(n->left);
    int rightHeight = height(n->right);
    return 1 + max(leftHeight, rightHeight);
}

Node* AVLTree::findNode(Node* n, const string& str) const {
    if (n == nullptr)
        return nullptr;
    if (n->data == str)
        return n;
    else if (str < n->data) {
        return findNode(n->left, str);
    }
    else {
        return findNode(n->right, str);
    }
}

int AVLTree::balanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    else {
        updateHeight(node);
        return height(node->left) - height(node->right);
    }
}

void AVLTree::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
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

void AVLTree::visualizeTree(ofstream& outFS, Node* n) {
    if (n) {
        if (n->left) {
            visualizeTree(outFS, n->left);
            outFS << n->data << " -> " << n->left->data << ";" << endl;
        }

        if (n->right) {
            visualizeTree(outFS, n->right);
            outFS << n->data << " -> " << n->right->data << ";" << endl;
        }
    }
}