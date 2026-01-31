// intbst.cpp
// Implements class IntBST
// Dylan Lee, 1/29/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n){
        clear(n -> left);
        clear(n -> right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root){
        Node* temp = new Node();
        temp -> info = value;
        root = temp;
        return true;
    }

    else{
        return insert(value, root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n-> info){
        return false;
    }

    if (value < n -> info){
        if (n -> left == nullptr){
            Node* temp = new Node();
            temp -> info = value;
            temp -> parent = n;
            n -> left = temp;
            return true;
        }

        else{
            return insert(value, n -> left);
        }
    }

    else{
        if (n -> right == nullptr){
            Node* temp = new Node();
            temp -> info = value;
            temp -> parent = n;
            n -> right = temp;
            return true;
        }

        else{
            return insert(value, n -> right);
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n){
        cout << n -> info << " ";
        printPreOrder(n -> left);
        printPreOrder(n -> right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n){
        printInOrder(n -> left);
        cout << n -> info << " ";
        printInOrder(n -> right);
    }
}
// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n){
        printPostOrder(n -> left);
        printPostOrder(n -> right);
        cout << n -> info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr){
        return 0;
    }

    else{
        return n -> info + sum(n -> left) + sum(n -> right);
    }
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr){
        return 0;
    }

    else{
        return 1 + count(n -> left) + count(n -> right);
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n){
        return nullptr;
    }

    if (n -> info == value){
        return n;
    }

    else if (value < n -> info){
        return getNodeFor(value, n -> left);
    }

    else{
        return getNodeFor(value, n -> right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
   return getNodeFor(value, root) != nullptr;
}


// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* current = getNodeFor(value, root);

    if (!current){
        return nullptr;
    }

    Node* predecessor = current->left;
    Node* parent = current->parent;

    if (!predecessor){ 
        while (parent){ 
            if (parent -> info < current -> info) {
                return parent;
            }
            parent = parent -> parent;
        }

        return nullptr; 
    }

    while (predecessor -> right){
        predecessor = predecessor -> right;
    }

    return predecessor;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if (getPredecessorNode(value)){
        return getPredecessorNode(value) -> info;
    }

    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* current = getNodeFor(value, root);

    if (!current) return nullptr;
        Node* successor = current -> right;
        Node* temp = current;

    if (!successor){
        while (temp -> parent){
            if (temp -> parent -> info < current -> info){
                return temp -> parent;
            }
            temp = temp -> parent;
        }
        return nullptr;
    } 

    while (successor -> left){
        successor = successor -> left;
    }

    return successor;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* successor = getSuccessorNode(value);
    if (successor){
        return successor -> info;
    }
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
// after deletion has to have valid bst properties
bool IntBST::remove(int value){
    Node* toDelete = getNodeFor(value, root);

    if (!toDelete){
        return false;
    }

    if (!toDelete -> left && !toDelete -> right){
        if (!toDelete -> parent){
            root = nullptr;
        } 

        else if (toDelete == toDelete -> parent -> left){
            toDelete -> parent -> left = nullptr;
        } 

        else{
            toDelete -> parent -> right = nullptr;
        }

        delete toDelete;
    }

    else if (!toDelete -> left || !toDelete -> right){
        Node* temp;

        if (!toDelete -> left){
            temp = toDelete -> right;
        } 

        else{
            temp = toDelete -> left;
        }
        
        if (!toDelete -> parent){
            root = temp;

            if (temp){
                temp -> parent = nullptr;
            }
        } 

        else if (toDelete == toDelete -> parent -> left){
            toDelete -> parent -> left = temp;

            if (temp){
                temp -> parent = toDelete -> parent;
            } 
        }

        else{
            toDelete -> parent -> right = temp;

            if (temp){
                temp -> parent = toDelete -> parent;
            }
        }

        delete toDelete;
    }

    else {
        Node* successor = toDelete -> right;

        while (successor -> left){
            successor = successor->left;
        }

        toDelete -> info = successor -> info;
        
        if (successor -> right){
            if (successor == toDelete -> right){
                toDelete -> right = successor -> right;
                successor -> right -> parent = toDelete;
            } 

            else{
                successor -> parent -> left = successor -> right;

                if (successor -> right){
                    successor -> right -> parent = successor -> parent;
                }
            }
        } 
        
        else{
            if (successor == toDelete -> right){
                toDelete -> right = nullptr;
            }

            else{
                successor -> parent -> left = nullptr;
            }
        }
        delete successor;
    }

    return true;
}
