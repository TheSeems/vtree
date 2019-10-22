#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void buildTree();

  void put(int value);

 public slots:
  void on_addButton_clicked();

  void on_eraseButton_clicked();

  void on_orderAdd_clicked();

  void on_orderErase_clicked();

  void on_comboBox_currentIndexChanged(int index);

private slots:
  void on_orderErase_2_clicked();

  void on_orderErase_3_clicked();

private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
