#ifndef QNODE_H
#define QNODE_H

#include <QDebug>
#include <QGraphicsEllipseItem>
#include "mainwindow.h"

class QNode : public QGraphicsEllipseItem {
 protected:
  int value;
  MainWindow* window;

 public:
  QNode(QGraphicsEllipseItem* parent, MainWindow* window, int value)
      : QGraphicsEllipseItem(parent), value(value), window(window) {}
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif  // QNODE_H
