#ifndef QTREE_H
#define QTREE_H

#include <QGraphicsView>
#include "Painter.h"
#include "mainwindow.h"

class QTree : public QGraphicsView {
 public:
  QTree(QWidget* parent = nullptr);
  QTree(QGraphicsScene* scene, QWidget* parent = nullptr);
  Painter* getPainter();
  void setPainter(Painter* painter);

  void draw(Node<int>* root);

  void rescale(double d);

 protected:
  virtual void wheelEvent(QWheelEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mousePressEvent(QMouseEvent* event);
  Painter* painter;
  QPoint offset, current, splash;

  double imageScale;
};

#endif  // QTREE_H
