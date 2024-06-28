#include "RBTree.h"
#include <iostream>
#include <cassert>

using namespace std;

void testInsertion(RBTree &tree) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    assert(tree.search(10) != nullptr);
    assert(tree.search(20) != nullptr);
    assert(tree.search(30) != nullptr);
    assert(tree.search(15) != nullptr);
    assert(tree.search(25) != nullptr);
    cout << "Insertion tests passed." << endl;
}

void testDeletion(RBTree &tree) {
    tree.remove(10);
    tree.remove(20);
    tree.remove(30);
    assert(tree.search(10) == nullptr);
    assert(tree.search(20) == nullptr);
    assert(tree.search(30) == nullptr);
    cout << "Deletion tests passed." << endl;
}

void testSearch(RBTree &tree) {
    assert(tree.search(15) != nullptr);
    assert(tree.search(25) != nullptr);
    assert(tree.search(100) == nullptr);
    cout << "Search tests passed." << endl;
}

void testTraversal(RBTree &tree) {
    tree.inorder();
}

void testMinMax(RBTree &tree) {
    assert(tree.findMin() == 10);
    assert(tree.findMax() == 30);
    cout << "Min/Max tests passed." << endl;
}

void testHeight(RBTree &tree) {
    assert(tree.getHeight() > 0);
    cout << "Height test passed." << endl;
}

void testValidation(RBTree &tree) {
    assert(tree.validate() == true);
    cout << "Validation test passed." << endl;
}

int main() {
    RBTree tree;
    testInsertion(tree);
    testMinMax(tree); 
    testSearch(tree);
    testTraversal(tree);
    testHeight(tree);
    testValidation(tree);
    testDeletion(tree);
    return 0;
}
