#include "QNode.h"
#include <QGraphicsScene>
#include <QPen>
#include "mainwindow.h"

void QNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  window->put(value);
  window->on_eraseButton_clicked();
}
