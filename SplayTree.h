#ifndef SPLAYTTREEHEADER
#define SPLAYTREEHEADER
#include "Node.h"

class SplayTree {
  using node = Node<int>;
  bool isEmpty();
  bool search_if_not_empty(int element);
  bool remove_if_not_empty(int elem);
  void get_biggest(node*& actualnode);
  bool remove_node(node*& actualnode);
  bool insert_if_empty(int element);
  bool insert_if_not_empty(int element);
  bool study_right_son(node*& actualnode, int element);
  bool study_left_son(node*& actualnode, int element);
  void insert_to_right_son(node*& actualnode, int element);
  void insert_to_left_son(node*& actualnode, int element);
  void updateParents(node*& n, node*& aux);
  void updateGrandpa(node*& n, node*& aux);
  void left_rotate(node* n);
  void right_rotate(node* n);
  bool rotate_if_father(node*& actualnode);
  void rotate_if_grandpa(node*& actualnode);
  void floation(node* n);

 public:
  node* root;
  SplayTree();
  bool remove(int elem);
  bool search(int elem);
  bool insert(int element);
};

#endif
