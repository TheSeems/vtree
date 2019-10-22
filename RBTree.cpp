#include "RBTree.h"

RBTree::RBTree() {
  root = nullptr;
}

int RBTree::getColor(Node* node) {
  if (node == nullptr)
    return BLACK;

  return node->color;
}

void RBTree::setColor(Node*& node, int color) {
  if (node == nullptr)
    return;

  node->color = color;
}

Node<int>* RBTree::insertBST(Node*& root, Node*& ptr) {
  if (root == nullptr)
    return ptr;

  if (ptr->key < root->key) {
    root->left = insertBST(root->left, ptr);
    root->left->parent = root;
  } else if (ptr->key > root->key) {
    root->right = insertBST(root->right, ptr);
    root->right->parent = root;
  }

  return root;
}

void RBTree::insertValue(int n) {
  Node* node = new Node(n);
  root = insertBST(root, node);
  fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node*& ptr) {
  if (ptr == nullptr) {
    qDebug() << "?L" << endl;
    return;
  }

  Node* right_child = ptr->right;

  if (right_child != nullptr)
    ptr->right = right_child->left;

  if (ptr->right != nullptr)
    ptr->right->parent = ptr;

  if (right_child != nullptr)
    right_child->parent = ptr->parent;

  if (ptr->parent == nullptr)
    root = right_child;
  else if (ptr->parent != nullptr && ptr == ptr->parent->left)
    ptr->parent->left = right_child;
  else if (ptr->parent != nullptr)
    ptr->parent->right = right_child;

  if (right_child != nullptr)
    right_child->left = ptr;
  ptr->parent = right_child;
}

void RBTree::rotateRight(Node*& ptr) {
  if (ptr == nullptr) {
    qDebug() << "?R" << endl;
    return;
  }

  Node* left_child = ptr->left;

  if (left_child != nullptr)
    ptr->left = left_child->right;

  if (ptr->left != nullptr)
    ptr->left->parent = ptr;

  if (left_child != nullptr)
    left_child->parent = ptr->parent;

  if (ptr->parent == nullptr)
    root = left_child;
  else if (ptr == ptr->parent->left)
    ptr->parent->left = left_child;
  else
    ptr->parent->right = left_child;

  if (left_child != nullptr)
    left_child->right = ptr;
  ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(Node*& ptr) {
  Node* parent = nullptr;
  Node* grandparent = nullptr;
  while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
    parent = ptr->parent;
    grandparent = parent->parent;
    if (parent == grandparent->left) {
      Node* uncle = grandparent->right;
      if (getColor(uncle) == RED) {
        setColor(uncle, BLACK);
        setColor(parent, BLACK);
        setColor(grandparent, RED);
        ptr = grandparent;
      } else {
        if (ptr == parent->right) {
          rotateLeft(parent);
          ptr = parent;
          parent = ptr->parent;
        }
        rotateRight(grandparent);
        std::swap(parent->color, grandparent->color);
        ptr = parent;
      }
    } else {
      Node* uncle = grandparent->left;
      if (getColor(uncle) == RED) {
        setColor(uncle, BLACK);
        setColor(parent, BLACK);
        setColor(grandparent, RED);
        ptr = grandparent;
      } else {
        if (ptr == parent->left) {
          rotateRight(parent);
          ptr = parent;
          parent = ptr->parent;
        }
        rotateLeft(grandparent);
        std::swap(parent->color, grandparent->color);
        ptr = parent;
      }
    }
  }
  setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node*& node) {
  if (node == nullptr)
    return;
  if (node == root) {
    root = node->left != nullptr ? node->left : node->right;
    return;
  }

  if (node->parent != nullptr &&
      (getColor(node) == RED || getColor(node->left) == RED ||
       getColor(node->right) == RED)) {
    Node* child = node->left != nullptr ? node->left : node->right;

    if (node == node->parent->left) {
      node->parent->left = child;
      if (child != nullptr)
        child->parent = node->parent;
      setColor(child, BLACK);
      // delete (node);
      node = nullptr;
    } else {
      node->parent->right = child;
      if (child != nullptr)
        child->parent = node->parent;
      setColor(child, BLACK);
      // delete (node);
      node = nullptr;
    }
  } else {
    Node* sibling = nullptr;
    Node* parent = nullptr;
    Node* ptr = node;
    setColor(ptr, DOUBLE_BLACK);
    while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
      parent = ptr->parent;
      if (parent == nullptr)
        break;

      if (ptr == parent->left) {
        sibling = parent->right;
        if (getColor(sibling) == RED) {
          setColor(sibling, BLACK);
          setColor(parent, RED);
          rotateLeft(parent);
        } else {
          if (sibling != nullptr && getColor(sibling->left) == BLACK &&
              getColor(sibling->right) == BLACK) {
            setColor(sibling, RED);
            if (getColor(parent) == RED)
              setColor(parent, BLACK);
            else
              setColor(parent, DOUBLE_BLACK);
            ptr = parent;
          } else {
            if (sibling != nullptr && getColor(sibling->right) == BLACK) {
              setColor(sibling->left, BLACK);
              setColor(sibling, RED);
              rotateRight(sibling);
              sibling = parent->right;
            }
            setColor(sibling, parent->color);
            setColor(parent, BLACK);
            if (sibling != nullptr)
              setColor(sibling->right, BLACK);
            rotateLeft(parent);
            break;
          }
        }
      } else {
        sibling = parent->left;
        if (getColor(sibling) == RED) {
          setColor(sibling, BLACK);
          setColor(parent, RED);
          rotateRight(parent);
        } else {
          if (sibling != nullptr && getColor(sibling->left) == BLACK &&
              getColor(sibling->right) == BLACK) {
            setColor(sibling, RED);
            if (getColor(parent) == RED)
              setColor(parent, BLACK);
            else
              setColor(parent, DOUBLE_BLACK);
            ptr = parent;
          } else {
            if (sibling != nullptr && getColor(sibling->left) == BLACK) {
              setColor(sibling->right, BLACK);
              setColor(sibling, RED);
              rotateLeft(sibling);
              sibling = parent->left;
            }
            setColor(sibling, parent->color);
            setColor(parent, BLACK);
            if (sibling != nullptr)
              setColor(sibling->left, BLACK);
            rotateRight(parent);
            break;
          }
        }
      }
    }

    if (node != nullptr && node->parent != nullptr &&
        node == node->parent->left)
      node->parent->left = nullptr;
    else if (node != nullptr && node->parent != nullptr)
      node->parent->right = nullptr;
    // delete(node);
    node = nullptr;
    setColor(root, BLACK);
  }
}

Node<int>* RBTree::deleteBST(Node*& root, int data) {
  if (root == nullptr)
    return root;

  if (data < root->key)
    return deleteBST(root->left, data);

  if (data > root->key)
    return deleteBST(root->right, data);

  if (root->left == nullptr || root->right == nullptr)
    return root;

  Node* temp = minValueNode(root->right);
  root->key = temp->key;
  return deleteBST(root->right, temp->key);
}

void RBTree::deleteValue(int data) {
  qDebug() << "Firstly..." << endl;
  Node* node = deleteBST(root, data);
  qDebug() << "Deleting itself -> nice" << endl;
  fixDeleteRBTree(node);
}

Node<int>* RBTree::minValueNode(Node*& node) {
  Node* ptr = node;

  while (ptr->left != nullptr)
    ptr = ptr->left;

  return ptr;
}

Node<int>* RBTree::maxValueNode(Node*& node) {
  Node* ptr = node;

  while (ptr->right != nullptr)
    ptr = ptr->right;

  return ptr;
}

int RBTree::getBlackHeight(Node* node) {
  int blackheight = 0;
  while (node != nullptr) {
    if (getColor(node) == BLACK)
      blackheight++;
    node = node->left;
  }
  return blackheight;
}
