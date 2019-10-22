#include "mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cmath>
#include "AVLTree.h"
#include "Painter.h"
#include "QNode.h"
#include "QTree.h"
#include "RBTree.h"
#include "SplayTree.h"
#include "ui_mainwindow.h"

// Actual trees
static AVLTree avl;
static RBTree red;
static SplayTree splay;

// Painter-wrappers
static QTree *avlTree, *redTree, *splayTree;

// Current tree's number
static int CURRENT_TREE = 0;

//
//  Some design contsants
//
const QString MAIN_WIDGET_STYLE =
    "background-color: white;"
    "border: 0;"
    "padding: 10px;";

QTree* make(MainWindow* window, QGraphicsScene* scene, bool drawColor = false) {
  auto view = new QTree(window);
  view->setFixedSize(window->width() * 5 / 6, 1080);
  view->setScene(scene);
  view->showMaximized();
  view->setStyleSheet(MAIN_WIDGET_STYLE);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform |
      QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);

  auto painter = new Painter(scene, window);
  painter->drawColor = drawColor;
  view->setPainter(painter);

  view->hide();
  return view;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto scene = new QGraphicsScene(this);
  this->showMaximized();

  avl = AVLTree();
  red = RBTree();
  splay = SplayTree();

  avlTree = make(this, scene);
  redTree = make(this, scene, true);
  splayTree = make(this, scene);
  avlTree->show();

  showFullScreen();
}

MainWindow::~MainWindow() {
  delete ui;
}

void draw() {
  if (CURRENT_TREE == 0)
    avlTree->draw(avl.root);
  else if (CURRENT_TREE == 1)
    redTree->draw(red.root);
  else
    splayTree->draw(splay.root);
}

void insert(int value) {
    avl.insert(value);
    red.insertValue(value);
    splay.insert(value);
}

void erase(int value) {
    avl.remove(value);
    red.deleteValue(value);
    splay.remove(value);
}

void MainWindow::on_addButton_clicked() {
  int value = ui->addBox->value();
  qDebug() << "Inserting " << value << endl;
  insert(value);
  draw();
  qDebug() << "here" << endl;
}

void MainWindow::on_eraseButton_clicked() {
  int value = ui->addBox->value();
  erase(value);
  draw();
  qDebug() << "here" << endl;
}

void MainWindow::on_orderAdd_clicked() {
  int left = ui->leftValue->value(), right = ui->rightValue->value();
  std::vector<int> vect;
  for (int i = left; i <= right; i++)
    vect.push_back(i);

  std::random_shuffle(vect.begin(), vect.end());
  for (int i : vect)
    insert(i);

  draw();
}

void MainWindow::put(int value) {
  ui->addBox->setValue(value);
}

void MainWindow::on_orderErase_clicked() {
  int left = ui->leftValue->value(), right = ui->rightValue->value();
  std::vector<int> vect;
  for (int i = left; i <= right; i++)
    vect.push_back(i);

  std::random_shuffle(vect.begin(), vect.end());
  for (int i : vect)
    erase(i);

  draw();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  CURRENT_TREE = index;
  draw();
}

void MainWindow::on_orderErase_2_clicked()
{
    close();
}

void MainWindow::on_orderErase_3_clicked() {}

/**
void MainWindow::on_orderErase_3_clicked()
{
  if (CURRENT_TREE == 0) {
    avlTree->rescale(1);
  } else if (CURRENT_TREE == 1) {
    redTree->rescale(1);
  } else {
    splayTree->rescale(1);
  }

  draw();
}**/
