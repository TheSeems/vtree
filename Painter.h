#ifndef PAINTER_H
#define PAINTER_H

#include "Node.h"
#include "QNode.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>

#include "mainwindow.h"

class Painter {
  QGraphicsScene* scene;
  MainWindow* window;
  using node = Node<int>;

  const int VISITED = 1;
  const int LEFT_VISITED = 2;
  const int RIGHT_VISITED = 3;

 public:
  int amplify_y = 81, amplify_x = 81;
  int node_radius = 80;
  bool drawColor = false;

 public:
  Painter(QGraphicsScene* scene, MainWindow* window)
      : scene(scene), window(window) {}

  /**
   * Initial traversal with mods
   * @brief dfs
   * @param root
   * @param hei
   */
  void initial(node* root, int hei = 0) {
    int *mods = new int[hei + 10], * next = new int[hei + 10];
    for (int i = 0; i < hei + 10; i++) {
      mods[i] = 0;
      next[i] = 1;
    }

    node* cur = root;
    cur->status = VISITED;
    while (cur != nullptr) {
      if (cur->status == 1) {
        cur->status = LEFT_VISITED;
        if (cur->left != nullptr) {
          cur = cur->left;
          cur->status = VISITED;
        }
      } else if (cur->status == 2) {
        cur->status = RIGHT_VISITED;
        if (cur->right != nullptr) {
          cur = cur->right;
          cur->status = VISITED;
        }
      } else {
        int h = cur->y;
        int pos;
        bool leaf = cur->left == nullptr && cur->right == nullptr;
        if (leaf)
          pos = next[h];
        else if (cur->left == nullptr)
          pos = cur->right->x - 1;
        else if (cur->right == nullptr)
          pos = cur->left->x + 1;
        else
          pos = (cur->left->x + cur->right->x) / 2;
        mods[h] = std::max(mods[h], next[h] - pos);
        if (leaf)
          cur->x = pos;
        else
          cur->x = pos + mods[h];
        next[h] = cur->x + 2;
        cur->mod = mods[h];
        cur = cur->parent;
      }
    }
  }

  /**
   * Sumarizing up previous traversal
   * @brief dfs_second
   * @param cur
   */
  void sumarize(node* cur) {
    if (cur == nullptr)
      return;

    cur->status = VISITED;
    int64_t sum = 0;
    while (cur != nullptr) {
      if (cur->status == VISITED) {
        cur->x += sum;
        sum += cur->mod;
        cur->status = LEFT_VISITED;
        if (cur->left != nullptr) {
          cur = cur->left;
          cur->status = VISITED;
        }
      } else if (cur->status == LEFT_VISITED) {
        cur->status = RIGHT_VISITED;
        if (cur->right != nullptr) {
          cur = cur->right;
          cur->status = VISITED;
        }
      } else {
        sum -= cur->mod;
        cur = cur->parent;
      }
    }
  }

  /**
   * Putting level depend Y-coordinate
   * @brief putY
   * @param root
   * @param level
   */
  void putY(node* root, int level) {
    if (root != nullptr) {
      putY(root->right, level + 1);
      putY(root->left, level + 1);
      root->y = level;
    }
  }

  /**
   * Getting height of the tree
   * @brief getHeight
   * @param root
   * @return
   */
  int getHeight(node* root) {
    if (root == nullptr)
      return 0;
    int max_left = getHeight(root->left) + 1;
    int max_right = getHeight(root->right) + 1;
    return std::max(max_left, max_right);
  }

  /**
   * Layouting all the tree
   * @brief layoutTree
   * @param root
   */
  void layoutTree(node*& root) {
    if (root == nullptr)
      return;

    putY(root, 0);
    initial(root, getHeight(root));
    sumarize(root);
  }

  void drawNode(node* root) {
    if (root == nullptr)
      return;

    double x = root->x * amplify_x, y = root->y * amplify_x;

    // Drawing this node (circle for it)
    auto parent = new QGraphicsEllipseItem();
    QNode* circle = new QNode(parent, window, root->key);
    circle->setRect(x, y, node_radius, node_radius);
    scene->addItem(circle);

    if (drawColor && root->color == RED)
      circle->setPen(QPen(QColor(50, 212, 44), 1, Qt::SolidLine, Qt::RoundCap,
                          Qt::RoundJoin));
    else
      circle->setPen(
          QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    circle->setBrush(Qt::white);

    // Putting text there
    QString value = QString::number(root->key);
    auto text = scene->addText(value, QFont("Andale Mono", 12));

    if (drawColor && root->color == RED)
      text->setDefaultTextColor(QColor::fromRgb(96, 169, 23));

    text->setX(x + node_radius / 2.4 - value.length() * node_radius / 16.0);
    text->setY(y + node_radius / 3);
  }

  /**
   * Drawing tree using QT
   * @brief drawTree
   * @param root
   */
  void drawTree(node* root) {
    if (root == nullptr)
      return;
    // Scaling coordinates of current node
    double x = root->x * amplify_x;
    double y = root->y * amplify_y;

    // Drawing children
    if (root->left != nullptr) {
      drawTree(root->left);
      double left_x = root->left->x * amplify_x,
             left_y = root->left->y * amplify_y;
      scene->addLine(x + node_radius / 2, y + node_radius / 2,
                     left_x + node_radius / 2, left_y + node_radius / 2);
      drawNode(root->left);
    }
    if (root->right != nullptr) {
      drawTree(root->right);
      double right_x = root->right->x * amplify_x,
             right_y = root->right->y * amplify_y;
      scene->addLine(x + node_radius / 2, y + node_radius / 2,
                     right_x + node_radius / 2, right_y + node_radius / 2);
      drawNode(root->right);
    }
  }

  /**
   * Cleaning up scene, layouting out AVL-tree's root and displaying it
   */
  void buildTree(node* root) {
    scene->clear();
    layoutTree(root);

    // Drawing main part of the tree
    drawTree(root);

    // Drawing the root
    drawNode(root);
  }
};

#endif  // PAINTER_H
