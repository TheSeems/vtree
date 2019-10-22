#include <bits/stdc++.h>
#include "rbtree.h"
using namespace std;

int main() {
  RBTree tree;
  tree.insertValue(10);
  tree.insertValue(0), tree.insertValue(1), tree.insertValue(2);
  tree.inorder();
  return 0;
}
