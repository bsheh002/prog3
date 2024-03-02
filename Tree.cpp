#include "Tree.h"
#include  <iostream>
#include <algorithm>
using namespace std;

Tree::Tree() { //constructor for a 2-3 tree
    root = nullptr;
}
Tree::Tree(Tree &treeCopy) { //calls a helper function to recursively copy tree
    root = nullptr;
    copyHelper(treeCopy.root);
    cout << endl;
}
void Tree::copyHelper(Node* currNode) { //recursively goes through tree and prints the tree
    if (currNode) { //checks if a currNode is available
        if (currNode->counterForData() == 1) { //checks if small is not empty string
            copyHelper(currNode->left);
            insert(currNode->smallNode);
            copyHelper(currNode->middle);
        }
        else {
            copyHelper(currNode->left);
            insert(currNode->smallNode);
            copyHelper(currNode->middle);
            insert(currNode->largeNode);
            copyHelper(currNode->right);
        }
    }
}
Tree::~Tree() { //destructor
    destructorHelper(root);
}

void Tree::destructorHelper(Node* currNode) { //recursively goes through tree to delete it
    if(currNode){ //checks if a currNode exists
        destructorHelper(currNode->left);
        destructorHelper(currNode->middle);
        destructorHelper(currNode->right);

        delete currNode;
    }
}
void Tree::insert(const string &stringOfData) { //insert function
    if (root == nullptr) { //checks to see if root is empty
        root = new Node(stringOfData);
        return;
    }
    Node* currNode = root;
    while (currNode != nullptr) { //checks to see if node is not empty
        if (stringOfData < currNode->smallNode) {  //compares data to small node
            if (currNode->left) {
                currNode = currNode->left;
            }
            else if (currNode->counterForData() == 1) { //checks if left doesnt exist
                if (stringOfData > currNode->smallNode) {
                    currNode->largeNode = stringOfData;
                }
                else {
                    currNode->largeNode = currNode->smallNode;
                    currNode->smallNode = stringOfData;
                }
                currNode = nullptr;
            }
            else if (currNode->counterForData() == 2) { //calls split if this case is reached
                split(stringOfData, currNode);
                currNode = nullptr;
            } 
        }
        else if(currNode->counterForData() == 1 || (stringOfData > currNode->smallNode && stringOfData < currNode->largeNode)) {
            if(currNode->middle) {
                currNode = currNode->middle;
            }
            else if (currNode->counterForData() == 1) { //insert data without a split
                if (stringOfData < currNode->smallNode) {
                    currNode->largeNode = currNode->smallNode;
                    currNode->smallNode = stringOfData;
                }
                else {
                    currNode->largeNode = stringOfData;
                }
                currNode = nullptr;
            }
            else if (currNode->counterForData() == 2) { //splits data since there are 2 datas in node
                split(stringOfData, currNode);
                currNode = nullptr;
            }
        }
        else { 
            if(currNode->right) { 
                currNode = currNode->right;
            }
            else if (currNode->counterForData() == 1) { 
                if (stringOfData > currNode->smallNode) {
                    currNode->largeNode = stringOfData;
                }
                else {
                    currNode->largeNode = currNode->smallNode;
                    currNode->smallNode = stringOfData;
                }
                currNode = nullptr;
            }
            else if (currNode->counterForData() == 2) {
                split(stringOfData, currNode);
                currNode = nullptr;
            }
        }
    }
}
bool Tree::search (const string &stringOfData) const { //search function to find data in tree
    if (searchHelper(stringOfData, root)) { //calls helper function
        return true;
    }
    return false;
}
Node* Tree::searchHelper (const string &stringOfData, Node* currNode) const {
    if (currNode == nullptr) { //base case
        return currNode;
    }
    if (currNode->smallNode == stringOfData || currNode->largeNode == stringOfData) { //if data is found, return node
        return currNode;
    }
    if (stringOfData < currNode->smallNode) { //goes through the left side
        return searchHelper(stringOfData, currNode->left);
    }
    else if (currNode->counterForData() == 1 || (stringOfData > currNode->smallNode && stringOfData < currNode->largeNode)) {
        return searchHelper(stringOfData, currNode->middle);
    }
    else if (stringOfData > currNode->largeNode) { //searches right node if data is larger
        return searchHelper(stringOfData, currNode->right);
    }

    return currNode;
}
void Tree::split(const string &stringOfData, Node* currNode) { //split function
    string median;
    if (stringOfData < currNode->smallNode) { //checks if data is smaller
            median = currNode->smallNode;
            currNode->smallNode = stringOfData;
    }
    else if (stringOfData > currNode->smallNode && stringOfData < currNode->largeNode) { //checks if data is in the middle
        median = stringOfData;
    }
    else { 
        median = currNode->largeNode;
        currNode->largeNode = stringOfData;
    }
    if (currNode == root) { //checks if node is root
        currNode->left = new Node(currNode->smallNode);
        currNode->left->parent = root; 
        currNode->middle = new Node(currNode->largeNode); 
        currNode->middle->parent = root;
        currNode->smallNode = median;
        currNode->largeNode = "";
    }
    else {
        currNode->parent->largeNode = median;
        currNode->parent->right = new Node(stringOfData);
        currNode->largeNode = "";
    }
}
void Tree::remove(const string &stringOfData) { //remove function
    if (root == nullptr) { //checks if tree is empty
        return;
    }
    else if (search(stringOfData)) {
        Node* searchHelperNode = searchHelper(stringOfData, root);
        if(searchHelperNode->counterForData() == 1) { 
            if (searchHelperNode == root) {
                if (root->left == nullptr && root->middle == nullptr) { //checks if root is a leaf in order to delete it
                    delete searchHelperNode;
                    root = nullptr;
                    return;
                }
                else {
                    root->smallNode = root->left->smallNode;
                    root->largeNode = root->middle->smallNode;
                    delete root->middle;
                    root->middle = nullptr;
                    delete root->left;
                    root->left = nullptr;
                    return;
                }
            }
            else {
                Node* searchHelperNodeParent = searchHelperNode->parent;
                if (searchHelperNode == searchHelperNodeParent->left) { //checks if node is the left one
                    if (searchHelperNodeParent->middle->smallNode > root->smallNode) {
                        root->largeNode = searchHelperNodeParent->middle->smallNode;
                    }
                    else {
                        string temp = root->smallNode;
                        root->smallNode = searchHelperNodeParent->middle->smallNode;
                        root->largeNode = temp;
                    }
                    delete searchHelperNode;
                    searchHelperNodeParent->left = nullptr;
                    delete searchHelperNodeParent->middle;
                    searchHelperNodeParent->middle = nullptr;
                    return;
                }
                else if (searchHelperNode == searchHelperNodeParent->middle) { //checks if node is the middle one
                    if (searchHelperNodeParent->left->smallNode > root->smallNode) {
                        root->largeNode = searchHelperNode->left->smallNode;
                    }
                    else {
                        string temp = root->smallNode;
                        root->smallNode = searchHelperNodeParent->left->smallNode;
                        root->largeNode = temp;
                    }
                    delete searchHelperNode;
                    searchHelperNodeParent->middle = nullptr;
                    delete searchHelperNodeParent->left;
                    searchHelperNodeParent->left = nullptr;
                    return;
                }
            }
        }
        else if (searchHelperNode->counterForData() == 2) { //removes one of the datas if two are found
            if (searchHelperNode->smallNode == stringOfData) {
                searchHelperNode->smallNode = searchHelperNode->largeNode;
                searchHelperNode->largeNode = "";
            }
            else if (searchHelperNode->largeNode == stringOfData) {
                searchHelperNode->largeNode = "";
            }
        }
    }
}
void Tree::preOrder() const { //preorder function that uses helper function
    preOrderHelper(root);
    cout << endl;
}

void Tree::preOrderHelper(Node* currNode) const { //recursively prints tree in preOrder
    if (currNode) { //checks if a node exists
        if (currNode->counterForData() == 1) { //traverse normally if only one data is found
            cout << currNode->smallNode << ", ";
            preOrderHelper(currNode->left);
            preOrderHelper(currNode->middle);
        }
        else {
            cout << currNode->smallNode << ", ";
            preOrderHelper(currNode->left);
            cout << currNode->largeNode << ", ";
            preOrderHelper(currNode->middle);
            preOrderHelper(currNode->right);
        }
    }
}
void Tree::inOrder() const { //in order function, uses helper function
    inOrderHelper(root);
    cout << endl;
}

void Tree::inOrderHelper(Node* currNode) const { //recursively goes through tree and prints it in inOrder
    if (currNode) { //checks if node is not empty
        if (currNode->counterForData() == 1) { //goes through normally if only 1 data is found
            inOrderHelper(currNode->left);
            cout << currNode->smallNode << ", ";
            inOrderHelper(currNode->middle);
        }
        else {
            inOrderHelper(currNode->left);
            cout << currNode->smallNode << ", ";
            inOrderHelper(currNode->middle);
            cout << currNode->largeNode << ", ";
            inOrderHelper(currNode->right);
        }
    }
}
void Tree::postOrder() const { //post order function, uses helper function
    postOrderHelper(root);
    cout << endl;
}
void Tree::postOrderHelper(Node* currNode) const { //recursively prints tree in postOrder
    if (currNode) {  //checks if node is not empty
        if (currNode->counterForData() == 1) { //goes through tree normally if only one data is found
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->smallNode << ", ";
        }
        else {
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->smallNode << ", ";
            postOrderHelper(currNode->right);
            cout << currNode->largeNode << ", ";
        }
    }
}
