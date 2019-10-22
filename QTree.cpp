#include "QTree.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QWheelEvent>
#include "Painter.h"

QTree::QTree(QWidget* parent) : QGraphicsView(parent), imageScale(1) {}

QTree::QTree(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), imageScale(1) {}

void QTree::setPainter(Painter* painter) {
  this->painter = painter;
}

Painter* QTree::getPainter() {
  return this->painter;
}

void QTree::draw(Node<int>* root) {
  getPainter()->buildTree(root);
  for (auto i : this->items())
    i->moveBy(current.x(), current.y());
}

void QTree::rescale(double d) {
  if (d > 3.5 || d < 0.1)
    return;
  scale(d / imageScale, d / imageScale);
  imageScale = d;
}

void QTree::wheelEvent(QWheelEvent* event) {
  if (event->delta() > 0) {  
    if (imageScale * 1.05 > 3.5)
        return;
    scale(1.05, 1.05);
    imageScale *= 1.05;
  } else {
    if (imageScale * 0.95 < 0.1)
       return;
    scale(0.95, 0.95);
    imageScale *= 0.95;
  }
}

void QTree::mousePressEvent(QMouseEvent* event) {
  offset = event->pos();
}

void QTree::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    auto dot = event->pos() - offset;
    dot /= imageScale;
    for (auto i : this->items())
      i->moveBy(dot.x(), dot.y());

    current += dot;
    offset = event->pos();
  }
}
