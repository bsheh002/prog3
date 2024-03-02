#ifndef TREE_H
#define TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  Tree(Tree &);

  ~Tree( );

  void insert(const string &);
//types of print order
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  void destructorHelper(Node*);
  void copyHelper(Node* currNode);
  Node* searchHelper (const string &key, Node* curr) const;
  void split(const string &key, Node* curr);
  void preOrderHelper(Node* curr) const;
  void inOrderHelper(Node* curr) const;
  void postOrderHelper(Node* curr) const;
};

#endif
