#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

private:
  string smallNode;
  string largeNode;

public:
  Node();
  Node(const string&);

  Node(Node*);

  ~Node();

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  int counterForData() const;

};

#endif
