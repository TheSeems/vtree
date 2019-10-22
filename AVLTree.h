#ifndef AVLTREE_H
#define AVLTREE_H
#include <QByteArray>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QProcess>
#include <QTextStream>
#include <algorithm>
#include <iostream>
#include "Node.h"
using namespace std;

using node = Node<int>;
class AVLTree {
 public:
  node* root;
  AVLTree() : root(nullptr) {}

  void insert(int stuff) {
    if (search(stuff) != nullptr)
      return;

    if (root == nullptr) {
      root = new node();
      root->key = stuff;
      root->balance = 0;
      root->parent = nullptr;
    } else {
      auto linker = root;
      node* newnode = new node();
      newnode->key = stuff;

      while (linker != nullptr) {
        if (linker->key > stuff) {
          if (linker->left == nullptr) {
            linker->left = newnode;
            newnode->balance = 0;
            newnode->parent = linker;
            break;
          } else {
            linker = linker->left;
          }
        } else {
          if (linker->right == nullptr) {
            linker->right = newnode;
            newnode->balance = 0;
            newnode->parent = linker;
            break;
          } else {
            linker = linker->right;
          }
        }
      }
      balance(newnode);
    }
  }

  int height(node* temp) { return ((temp == nullptr) ? -1 : temp->balance); }

  int factor(node* temp) {
    return (height(temp->right) - height(temp->left));
  }

  void height_balance(node* temp) {
    int l = -1, r = -1;
    if (temp->left) {
      l = temp->left->balance;
    }
    if (temp->right) {
      r = temp->right->balance;
    }
    temp->balance = max(l, r) + 1;
  }

  void fix(node* temp) {
    if (factor(temp) == 2) {
      if (factor(temp->right) < 0) {
        right_rotate(temp->right);
      }
      left_rotate(temp);
      height_balance(temp);
    } else if (factor(temp) == -2) {
      if (factor(temp->left) > 0) {
        left_rotate(temp->left);
      }
      right_rotate(temp);
      height_balance(temp);
    }
  }

  void balance(node* temp) {
    if (temp == root) {
      fix(root);
    } else {
      while (temp != nullptr) {
        height_balance(temp);
        temp = temp->parent;
        if (temp) {
          fix(temp);
        }
      }
    }
  }

  void left_rotate(node* x) {
    node* nw_node = new node();
    if (x->right->left) {
      nw_node->right = x->right->left;
    }
    nw_node->left = x->left;
    nw_node->key = x->key;
    x->key = x->right->key;

    x->left = nw_node;
    if (nw_node->left) {
      nw_node->left->parent = nw_node;
    }
    if (nw_node->right) {
      nw_node->right->parent = nw_node;
    }
    nw_node->parent = x;

    if (x->right->right) {
      x->right = x->right->right;
    } else {
      x->right = nullptr;
    }

    if (x->right) {
      x->right->parent = x;
    }

    height_balance(x->left);
    if (x->right) {
      height_balance(x->right);
    }
    height_balance(x);
  }

  void right_rotate(node* x) {
    node* nw_node = new node();
    if (x->left->right) {
      nw_node->left = x->left->right;
    }
    nw_node->right = x->right;
    nw_node->key = x->key;
    x->key = x->left->key;

    x->right = nw_node;
    if (nw_node->left) {
      nw_node->left->parent = nw_node;
    }
    if (nw_node->right) {
      nw_node->right->parent = nw_node;
    }
    nw_node->parent = x;

    if (x->left->left) {
      x->left = x->left->left;
    } else {
      x->left = nullptr;
    }

    if (x->left) {
      x->left->parent = x;
    }

    height_balance(x->right);
    if (x->left) {
      height_balance(x->left);
    }
    height_balance(x);
  }

  node* search(int stuff) {
    auto temp = root;
    if (temp == nullptr) {
      return nullptr;
    }

    while (temp) {
      if (stuff == temp->key) {
        return temp;
      } else if (stuff < temp->key) {
        temp = temp->left;
      } else {
        temp = temp->right;
      }
    }
    return nullptr;
  }

  void removeNode(node* Parent, node* curr, int stuff) {
    if (curr == nullptr) {
      return;
    }
    if (curr->key == stuff) {
      // CASE -- 1
      if (curr->left == nullptr && curr->right == nullptr) {
        if (Parent->key == curr->key) {
          root = nullptr;
        } else if (Parent->right == curr) {
          Parent->right = nullptr;
        } else {
          Parent->left = nullptr;
        }
        balance(Parent);
      }
      // CASE -- 2
      else if (curr->left != nullptr && curr->right == nullptr) {
        int sp = curr->key;
        curr->key = curr->left->key;
        curr->left->key = sp;
        removeNode(curr, curr->left, stuff);
      } else if (curr->left == nullptr && curr->right != nullptr) {
        int sp = curr->key;
        curr->key = curr->right->key;
        curr->right->key = sp;
        removeNode(curr, curr->right, stuff);
      }
      // CASE -- 3
      else {
        node* temp = curr->right;
        int flag = 0;
        while (temp->left) {
          flag = 1;
          Parent = temp;
          temp = temp->left;
        }
        if (!flag) {
          Parent = curr;
        }
        int sp = curr->key;
        curr->key = temp->key;
        temp->key = sp;
        removeNode(Parent, temp, temp->key);
      }
    }
  }

  void remove(int stuff) {
    auto temp = root;
    auto Parent = temp;
    bool flag = false;
    if (temp == nullptr) {
      removeNode(nullptr, nullptr, stuff);
    }

    while (temp) {
      if (stuff == temp->key) {
        flag = true;
        removeNode(Parent, temp, stuff);
        break;
      } else if (stuff < temp->key) {
        Parent = temp;
        temp = temp->left;
      } else {
        Parent = temp;
        temp = temp->right;
      }
    }

    if (!flag) {
      cout << "Element doesn't exist in the table\n";
    } else {
      cout << "Element removed.\n";
    }
  }
};

#endif  // AVLTREE_H
