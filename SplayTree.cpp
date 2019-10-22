#include "SplayTree.h"

SplayTree::SplayTree() {
  root = nullptr;
}

bool SplayTree::insert(int element) {
  if (isEmpty())
    return insert_if_empty(element);
  return insert_if_not_empty(element);
}

bool SplayTree::search(int elem) {
  if (isEmpty())
    return false;
  return search_if_not_empty(elem);
}

bool SplayTree::remove(int elem) {
  if (isEmpty())
    return false;
  return remove_if_not_empty(elem);
}

bool SplayTree::isEmpty() {
  return root == nullptr;
}

void SplayTree::get_biggest(node*& actualNode) {
  actualNode = root->left;

  while (actualNode->right != nullptr) {
    actualNode = actualNode->right;
  }
}

bool SplayTree::study_right_son(node*& actualNode, int element) {
  if (actualNode->right == nullptr) {
    insert_to_right_son(actualNode, element);
    return true;
  }

  actualNode = actualNode->right;
  return false;
}

bool SplayTree::study_left_son(node*& actualNode, int element) {
  if (actualNode->left == nullptr) {
    insert_to_left_son(actualNode, element);
    return true;
  }

  actualNode = actualNode->left;
  return false;
}

void SplayTree::insert_to_right_son(node*& actualNode, int element) {
  actualNode->right = new node;
  actualNode->right->right = nullptr;
  actualNode->right->left = nullptr;
  actualNode->right->parent = actualNode;
  actualNode->right->key = element;

  floation(actualNode->right);
}

void SplayTree::insert_to_left_son(node*& actualNode, int element) {
  actualNode->left = new node;
  actualNode->left->right = nullptr;
  actualNode->left->left = nullptr;
  actualNode->left->parent = actualNode;
  actualNode->left->key = element;

  floation(actualNode->left);
}

void SplayTree::updateParents(node*& n, node*& aux) {
  aux = n->parent;
  n->parent = n->parent->parent;
  aux->parent = n;
}

void SplayTree::updateGrandpa(node*& n, node*& aux) {
  if (n->parent != nullptr) {
    if (n->parent->right == aux) {
      n->parent->right = n;
    } else {
      n->parent->left = n;
    }
  }
}

void SplayTree::left_rotate(node* n) {
  node* aux;
  updateParents(n, aux);
  aux->right = n->left;
  if (n->left != nullptr) {
    aux->right->parent = aux;
  }
  n->left = aux;
  updateGrandpa(n, aux);
}

void SplayTree::right_rotate(node* n) {
  node* aux;
  updateParents(n, aux);
  aux->left = n->right;
  if (aux->left != nullptr) {
    aux->left->parent = aux;
  }
  n->right = aux;
  updateGrandpa(n, aux);
}

bool SplayTree::remove_node(node*& actualNode) {
  floation(actualNode);
  if (root->left == nullptr) {
    if (root->right != nullptr)
      root->right->parent = nullptr;
    root = root->right;
    return true;
  }

  get_biggest(actualNode);

  if (root->right != nullptr) {
    actualNode->right = root->right;
    root->right->parent = actualNode;
  }

  root = root->left;
  root->parent = nullptr;
  return true;
}

bool SplayTree::insert_if_empty(int element) {
  root = new node;
  root->right = nullptr;
  root->left = nullptr;
  root->parent = nullptr;
  root->key = element;
  return true;
}

bool SplayTree::insert_if_not_empty(int element) {
  node* actualNode;
  actualNode = root;
  while (true) {
    if (actualNode->key == element) {
      floation(actualNode);
      return false;
    } else if (actualNode->key < element) {
      if (study_right_son(actualNode, element))
        return true;
    } else {
      if (study_left_son(actualNode, element))
        return true;
    }
  }
}

bool SplayTree::rotate_if_father(node*& actualNode) {
  if (actualNode->parent->right == actualNode) {
    left_rotate(actualNode);
    root = actualNode;
    return true;
  } else if (actualNode->parent->left == actualNode) {
    right_rotate(actualNode);
    root = actualNode;
    return true;
  }

  return false;
}

void SplayTree::rotate_if_grandpa(node*& actualNode) {
  bool entered = false;
  if (actualNode->parent->parent->left != nullptr) {
    if (actualNode->parent->parent->left->left == actualNode) {
      right_rotate(actualNode->parent);
      right_rotate(actualNode);
      entered = true;
    } else if (actualNode->parent->parent->left->right == actualNode) {
      left_rotate(actualNode);
      right_rotate(actualNode);
      entered = true;
    }
  }
  if (!entered && actualNode->parent->parent->right != nullptr) {
    if (actualNode->parent->parent->right->right == actualNode) {
      left_rotate(actualNode->parent);
      left_rotate(actualNode);
    } else if (actualNode->parent->parent->right->left == actualNode) {
      right_rotate(actualNode);
      left_rotate(actualNode);
    }
  }
}

void SplayTree::floation(node* n) {
  node* actualNode = n;
  while (true) {
    if (actualNode->parent != nullptr &&
        actualNode->parent->parent != nullptr) {
      rotate_if_grandpa(actualNode);
    } else if (actualNode->parent != nullptr) {
      if (rotate_if_father(actualNode))
        break;
    } else {
      root = actualNode;
      break;
    }
  }
}

bool SplayTree::remove_if_not_empty(int elem) {
  node* actualNode = root;
  while (true) {
    if (actualNode->key == elem) {
      return remove_node(actualNode);
    } else if (actualNode->key < elem) {
      if (actualNode->right == nullptr) {
        floation(actualNode);
        return false;
      } else {
        actualNode = actualNode->right;
      }
    } else {
      if (actualNode->left == nullptr) {
        floation(actualNode);
        return false;
      } else {
        actualNode = actualNode->left;
      }
    }
  }
}

bool SplayTree::search_if_not_empty(int elem) {
  node* actualNode = root;
  while (true) {
    if (actualNode->key == elem) {
      floation(actualNode);
      return true;
    } else if (actualNode->key < elem) {
      if (actualNode->right == nullptr) {
        floation(actualNode);
        return false;
      } else {
        actualNode = actualNode->right;
      }
    } else {
      if (actualNode->left == nullptr) {
        floation(actualNode);
        return false;
      } else {
        actualNode = actualNode->left;
      }
    }
  }
}
