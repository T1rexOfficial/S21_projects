#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_mod, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_sqrt, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_sin, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_asin, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_cos, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_acos, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_tan, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_atan, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_ln, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_log, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_leftBracket, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_rightBracket, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_pow, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_point, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_plus, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_minus, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_mul, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_div, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  connect(ui->pushButton_x, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num0, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num1, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num2, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num3, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num4, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num5, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num6, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num7, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num8, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);
  connect(ui->pushButton_num9, &QPushButton::clicked, this,
          &MainWindow::pushButton_addText);

  ui->graphField->xAxis->setLabel("x");
  ui->graphField->yAxis->setLabel("y");
  ui->graphField->xAxis->setRange(-25, 25);
  ui->graphField->yAxis->setRange(-25, 25);
  ui->graphField->setInteraction(QCP::iRangeDrag);
  ui->graphField->setInteraction(QCP::iRangeZoom);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::pushButton_addText() {
  if (ui->label->text() == "ERROR!") {
    ui->label->setText("");
  }
  QString text = static_cast<QPushButton*>(sender())->text();
  ui->label->setText(ui->label->text() + text);
}

void MainWindow::on_pushButton_AC_clicked() { ui->label->clear(); }
#include <iostream>
void MainWindow::on_pushButton_eq_clicked() {
  QString sus = ui->label->text();
  QByteArray amogus = sus.toLocal8Bit();
  char* stringExpr = amogus.data();
  double answer = 0;
  s21_bool error = s21_false;
  double x_val = 0;
  QString x_val_str = ui->lineEdit_fieldForX->text();
  if (x_val_str != "") x_val = x_val_str.toDouble();
  if (sus != "") calc(stringExpr, &answer, &error, x_val);
  if (!error)
    ui->label->setText(QString::number(answer, 'f', 10));
  else
    ui->label->setText("ERROR!");
}

void MainWindow::on_pushButton_getGraph_clicked() {
  ui->graphField->replot();
  h = 0.01;
  xStart = -15;
  xFinish = 15;
  yStart = -15;
  yFinish = 15;

  if (ui->lineEdit_xmin->text() != "")
    xStart = ui->lineEdit_xmin->text().toDouble();
  if (ui->lineEdit_xmax->text() != "")
    xFinish = ui->lineEdit_xmax->text().toDouble();
  if (ui->lineEdit_ymin->text() != "")
    yStart = ui->lineEdit_ymin->text().toDouble();
  if (ui->lineEdit_ymax->text() != "")
    yFinish = ui->lineEdit_ymax->text().toDouble();

  xFinish += h;

  X = xStart;
  N = (xFinish - xStart) / h + 2;

  QString sus;
  QByteArray amogus;
  char* stringExpr;

  double answer = 0;
  s21_bool error = s21_false;

  for (X = xStart; X <= xFinish; X += h) {
    sus = ui->label->text();
    amogus = sus.toLocal8Bit();
    stringExpr = amogus.data();
    answer = 0;
    error = s21_false;
    if (sus != "") calc(stringExpr, &answer, &error, X);
    //        std :: cout << stringExpr << ' ' << X << ' ' << answer << ' ' <<
    //        error << std :: endl;
    x.push_back(X);
    if (answer > yFinish || answer < yStart || error) {
      y.push_back(qQNaN());
    } else {
      y.push_back(answer);
    }
  }

  //    std:: cout << x.size() << ' ' << y.size() << std:: endl;

  ui->graphField->addGraph();
  ui->graphField->graph(0)->setData(x, y);
  ui->graphField->replot();

  x.clear();
  y.clear();
}
