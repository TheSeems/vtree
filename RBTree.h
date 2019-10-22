#ifndef REBTREE_H
#define REBTREE_H

#include <iostream>
#include "Node.h"

class RBTree {
  using Node = Node<int>;

 protected:
  void rotateLeft(Node*&);
  void rotateRight(Node*&);
  void fixInsertRBTree(Node*&);
  void fixDeleteRBTree(Node*&);
  int getColor(Node*);
  void setColor(Node*&, int);
  Node* minValueNode(Node*&);
  Node* maxValueNode(Node*&);
  Node* insertBST(Node*&, Node*&);
  Node* deleteBST(Node*&, int);
  int getBlackHeight(Node*);

 public:
  Node* root;
  RBTree();
  void insertValue(int);
  void deleteValue(int);
};

#endif
