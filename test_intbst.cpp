#include "intbst.h"

#include <iostream>
using namespace std;

int getTest();

int main() {
    IntBST bst1;

    bst1.insert(6);
    bst1.insert(5);
    bst1.insert(1);
    bst1.insert(2);
    bst1.insert(9);
    bst1.insert(8);
    bst1.insert(10);
    
    cout << "preorder: ";
    bst1.printPreOrder();
    cout << endl;
    cout << "remove leaf" << endl;
    bst1.remove(2);
    cout << "remove node 1 child" << endl;
    bst1.remove(1);
    cout << "remove node 2 child" << endl;
    bst1.remove(9);
    cout << "preorder:";
    bst1.printPreOrder();
    cout << endl;
    cout << "done";

    return 0;
}