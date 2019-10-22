#ifndef NODE_H
#define NODE_H
#include <QDebug>

const int RED = 0, BLACK = 1, DOUBLE_BLACK = 2;

template <class T>
struct Node {
 public:
  T key{0};
  int balance{0};
  Node *parent{nullptr}, *left{nullptr}, *right{nullptr};
  int x{0}, y{0}, mod{0}, status{0}, color{0};

  Node(T k, Node* p)
      : key(k),
        balance(0),
        parent(p),
        left(nullptr),
        right(nullptr),
        x(0),
        y(0),
        mod(0),
        status(0),
        color(0) {}
  Node() : Node(0, nullptr) {}
  Node(T value) : Node(value, nullptr) {}
  Node(T value, int color) : Node(value, nullptr) { this->color = color; }

  ~Node() {
    // delete left;
    // delete right;
  }
};
#endif  // NODE_H
