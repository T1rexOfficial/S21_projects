#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_SmartCalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void pushButton_addText();

  void on_pushButton_AC_clicked();

  void on_pushButton_eq_clicked();

  void on_pushButton_getGraph_clicked();

 private:
  Ui::MainWindow *ui;
  double xStart, xFinish, yStart, yFinish, h, X;
  int N;

  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
