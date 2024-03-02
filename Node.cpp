#include "Node.h"

Node::Node() { //node with no key given
    smallNode = "";
    largeNode = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
}
Node::Node(const string& key) { //node with key given
    smallNode = key;
    largeNode = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::Node(Node* copy) { //copy of node
    smallNode = copy->smallNode;
    largeNode = copy->largeNode;
    left = copy->left;
    middle = copy->middle;
    right = copy->right;
    parent = copy->parent;
}

Node::~Node() //destructor
{
}

int Node::counterForData() const { //detects size of node and returns a number corresponding to it
    if ( largeNode != "" ) {
        return 2;
    }
    else if ( smallNode != "" ) {
        return 1;
    }
    else {
        return 0;
    }
}
