#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

void run_tests() {
    cout << "Constructing BS Tree...";
    BSTree bst = BSTree();
    cout << "complete." << endl;

    int totalTests = 0, failedTests = 0;
    totalTests++;
    cout << "Test: testing largest on empty tree...";
    if (bst.largest() == "") {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    totalTests++;
    cout << "Test: testing smallest on empty tree...";
    if (bst.smallest() == "") {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    /* Test insert (assume search works) */
    totalTests++;
    cout << "Test: testing insert and search...";
    string test_input = "Hello";
    bst.insert(test_input);
    if (bst.search(test_input)) {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert second word and search first and second...";
    string test_input2 = "World";
    bst.insert(test_input2);
    if (bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert duplicate and search first (duplicate) and second...";
    string test_input_duplicate = "Hello";
    bst.insert(test_input_duplicate);
    if (bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    totalTests++;
    cout << "Test: testing remove duplicate and search first (duplicate) second...";
    bst.remove(test_input);
    if (bst.search(test_input)) {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    totalTests++;
    cout << "Test: testing remove first (now gone)...";
    bst.remove(test_input);
    if (!bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    }
    else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    // TODO: Add tests for largest and smallest on non-empty trees
    cout << bst.largest() << endl;
    cout << bst.smallest() << endl;
    // TODO: Add tests for insert and remove on larger trees
    // TODO: Add tests for height of nodes (empty and larger trees)
    // Manually inspect pre post and inorder traversals

    cout << "Passed " << totalTests - failedTests << " / " << totalTests << " tests." << endl;
}

void printOrders(BSTree* tree) {
    cout << "Preorder = ";
    tree->preOrder();
    cout << endl;
    cout << "Inorder = ";
    tree->inOrder();
    cout << endl;
    cout << "Postorder = ";
    tree->postOrder();
    cout << endl;

}

int menu() {
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout
        << "1. Insert" << endl
        << "2. Remove" << endl
        << "3. Print" << endl
        << "4. Search" << endl
        << "5. Smallest" << endl
        << "6. Largest" << endl
        << "7. Height" << endl
        << "8. Quit" << endl;
    cin >> choice;
    while (choice < 1 || choice > 8) {
        cout << "Invalid input" << endl;
        cin >> choice;
    }

    // fix buffer just in case non-numeric choice entered
    // also gets rid of newline character
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    //run_tests();  // TODO: Remove before submitting
    //return 0;

    BSTree tree;

    int choice = menu();

    string entry;

    while (choice != 8) {
        if (choice == 1) {
            cout << "Enter string to insert: "<< endl;
            getline(cin, entry);
            tree.insert(entry);
            
            //cin.ignore();
        }
        else if (choice == 2) {
            cout << "Enter string to remove: " << endl;
            getline(cin, entry);
            tree.remove(entry);
        }
        else if (choice == 3) {
            printOrders(&tree);
        }
        else if (choice == 4) {
            cout << "Enter string to search for: " << endl;
            cin >> entry;
            if (!tree.search(entry))
                cout << "Not Found" << endl;
            else
                cout << "Found" << endl;
        }
        else if (choice == 5) {
            cout << "Smallest: " << tree.smallest() << endl;
        }
        else if (choice == 6) {
            cout << "Largest: " << tree.largest() << endl;
        }
        else if (choice == 7) {
            cout << "Enter string: " << endl;
            cin >> entry;
            cout << "Height of subtree rooted at " << entry << ": " << tree.height(entry) << endl;
        }
        choice = menu(); 
    }
    return 0;
}

