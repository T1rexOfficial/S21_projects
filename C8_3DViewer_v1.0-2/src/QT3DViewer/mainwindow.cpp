#include "mainwindow.h"

#include <QFileDialog>
#include <QMovie>
#include <QPixmap>
#include <QScreen>
#include <QTabBar>
#include <QWidget>
#include <chrono>
#include <iostream>
#include <thread>

#include "./ui_mainwindow.h"
#include "gif.h"
#include "viewer_back.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),

      lineColor(Qt::blue),
      vertexColor(Qt::white),
      lineSize(3),
      vertexSize(10),
      lineType(0),
      vertexType(0),
      backgroundColor(Qt::green),
      settings("21School", "3dViewer") {
  ui->setupUi(this);

  QColor defaultBackgroundColor(196, 77, 77);
  QColor defaultLineColor(65, 105, 225);
  QColor defaultVertexColor(61, 130, 109);
  lineColor = settings.value("lineColor", defaultLineColor).value<QColor>();
  vertexColor =
      settings.value("vertexColor", defaultVertexColor).value<QColor>();
  lineSize = settings.value("lineSize", 3).toInt();
  vertexSize = settings.value("vertexSize", 10).toInt();
  lineType = settings.value("lineType", 0).toInt();
  vertexType = settings.value("vertexType", 0).toInt();
  backgroundColor =
      settings.value("backgroundColor", defaultBackgroundColor).value<QColor>();

  setColorForButton(ui->lineColorButton, lineColor);
  setColorForButton(ui->vertexColorButton, vertexColor);
  ui->colorWidget->setStyleSheet(
      QString("background-color: %1").arg(backgroundColor.name()));
  ui->lineSlider->setValue(lineSize);
  ui->vertexSlider->setValue(vertexSize);
  ui->lineLabel->setText(QString::number(lineSize));
  ui->vertexLabel->setText(QString::number(vertexSize));
  ui->comboBox_LineType->setCurrentIndex(lineType);
  ui->comboBox_VertexType->setCurrentIndex(vertexType);

  ui->colorWidget->installEventFilter(this);

  ui->line_scale->setText("1");

  //    mo.setFileName("/Users/vulpixta/C8_3DViewer_v1.0-2/src/QT3DViewer/catmeme.gif");
  //    mo.setScaledSize(QSize(111, 101));
  //    ui->meme->setMovie(&mo);
  //    mo.start();

  onUpModelClicked();

  ui->tabWidget->tabBar()->setDocumentMode(true);
  ui->tabWidget->tabBar()->setExpanding(true);

  ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                             vertexColor, ui->vertexSlider->value(), vertexType,
                             backgroundColor);

  connect(ui->Uplode, &QPushButton::clicked, this,
          &MainWindow::onUpModelClicked);

  connect(ui->center_radiobutton, &QRadioButton::clicked, this,
          &MainWindow::on_center_radiobutton_clicked);
  connect(ui->parallel_radiobutton, &QRadioButton::clicked, this,
          &MainWindow::on_parallel_radiobutton_clicked);

  connect(ui->save_jpeg, &QPushButton::clicked, this, &MainWindow::saveJpeg);
  connect(ui->save_bmp, &QPushButton::clicked, this, &MainWindow::saveBmp);
  connect(ui->save_png, &QPushButton::clicked, this, &MainWindow::savePng);
  connect(ui->save_image, &QPushButton::clicked, this, &MainWindow::saveImage);

  connect(ui->reset, &QPushButton::clicked, this,
          &MainWindow::on_reset_clicked);
}

MainWindow::~MainWindow() {
  settings.setValue("lineColor", lineColor);
  settings.setValue("vertexColor", vertexColor);
  settings.setValue("lineSize", lineSize);
  settings.setValue("vertexSize", vertexSize);
  settings.setValue("lineType", lineType);
  settings.setValue("vertexType", vertexType);
  settings.setValue("backgroundColor", backgroundColor);
  delete ui;
}

void MainWindow::saveJpeg() {
  ui->save_jpeg->setStyleSheet(
      "QPushButton { border: 1px solid rgb(255, 255, 255); border-radius: "
      "20px; background-color: rgb(255, 255, 255); color: black;}");  // изменяем
                                                                      // стиль
                                                                      // кнопки
  ui->save_bmp->setStyleSheet(
      "QPushButton { border-top: 1px solid white;border-bottom: 1px solid "
      "white;border-left: none;border-right: none;}");  // изменяем стиль кнопки
  ui->save_png->setStyleSheet(
      "QPushButton { border-top: 1px solid white;border-bottom: 1px solid "
      "white;border-left: none;border-right: 1px solid "
      "white;border-top-right-radius: 20px;border-bottom-right-radius: "
      "20px;}");           // изменяем стиль кнопки
  m_imageFormat = "jpeg";  // сохраняем формат изображения в переменную класса
}

void MainWindow::saveBmp() {
  ui->save_jpeg->setStyleSheet(
      "QPushButton { border-top: 1px solid white;border-bottom: 1px solid "
      "white;border-right: none;border-left: 1px solid "
      "white;border-top-left-radius: 20px;border-bottom-left-radius: "
      "20px;}");  // изменяем стиль кнопки
  ui->save_bmp->setStyleSheet(
      "QPushButton { border: 1px solid rgb(255, 255, 255); border-radius: "
      "20px; background-color: rgb(255, 255, 255); color: black;}");  // изменяем
                                                                      // стиль
                                                                      // кнопки
  ui->save_png->setStyleSheet(
      "QPushButton { border-top: 1px solid white;border-bottom: 1px solid "
      "white;border-left: none;border-right: 1px solid "
      "white;border-top-right-radius: 20px;border-bottom-right-radius: "
      "20px;}");          // изменяем стиль кнопки
  m_imageFormat = "bmp";  // сохраняем формат изображения в переменную класса
}

void MainWindow::savePng() {
  ui->save_jpeg->setStyleSheet(
      "QPushButton { border-top: 1px solid white;border-bottom: 1px solid "
      "white;border-right: none;border-left: 1px solid "
      "white;border-top-left-radius: 20px;border-bottom-left-radius: "
      "20px;}");  // изменяем стиль кнопки
  ui->save_bmp->setStyleSheet(
      "border-top: 1px solid white;border-bottom: 1px solid white;border-left: "
      "none;border-right: none;}");  // изменяем стиль кнопки
  ui->save_png->setStyleSheet(
      "QPushButton { border: 1px solid rgb(255, 255, 255); border-radius: "
      "20px;  background-color: rgb(255, 255, 255); color: black;}");  // изменяем
                                                                       // стиль
                                                                       // кнопки
  m_imageFormat = "png";  // сохраняем формат изображения в переменную класса
}

void MainWindow::saveImage() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Сохранить как"), "image." + m_imageFormat,
      tr("Файлы изображений (*.%1)").arg(m_imageFormat));
  if (!fileName.isEmpty()) {  // проверяем, что пользователь выбрал файл для
                              // сохранения
    QPixmap screenshot = QPixmap::fromImage(ui->screen->grabFramebuffer());

    screenshot.save(fileName,
                    m_imageFormat.toStdString()
                        .c_str());  // сохраняем изображение в выбранном формате
                                    // и с указанным именем файла
  }
}

void MainWindow::onUpModelClicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Выберите файл модели"), "",
                                   tr("Файлы моделей (*.obj);;Все файлы (*)"));

  if (!fileName.isEmpty()) {
    std::string inputStringStr = fileName.toStdString();
    ui->screen->path = std::move(inputStringStr);
    ui->screen->reloadModel();

    ui->label_cnt_v->setText(QString::number(ui->screen->cnt_v));
    ui->label_cnt_f->setText(QString::number(ui->screen->cnt_f));
    ui->label_name_obj->setText(QFileInfo(fileName).fileName());
  }
}

void MainWindow::on_center_radiobutton_clicked() {
  ui->screen->setProjection(1);
  //    ui->label_cnt_v->setText(QString::number(ui->screen->cnt_v));
  //    ui->label_cnt_f->setText(QString::number(ui->screen->cnt_f));
}

void MainWindow::on_parallel_radiobutton_clicked() {
  ui->screen->setProjection(0);
  //    ui->label_cnt_v->setText(QString::number(ui->screen->cnt_v));
  //    ui->label_cnt_f->setText(QString::number(ui->screen->cnt_f));
}

void MainWindow::on_dial_rotate_x_sliderMoved(int position) {
  ui->line_rotate_x->setText(QString::number(position));
  ui->screen->setRotate(1, 0, 0, position);
}

void MainWindow::on_dial_rotate_y_sliderMoved(int position) {
  ui->line_rotate_y->setText(QString::number(position));
  ui->screen->setRotate(0, 1, 0, position);
}

void MainWindow::on_dial_rotate_z_sliderMoved(int position) {
  ui->line_rotate_z->setText(QString::number(position));
  ui->screen->setRotate(0, 0, 1, position);
}

void MainWindow::on_scale_slider_sliderMoved(int position) {
  int res;
  if (position >= 0)
    res = position + 1;
  else if (position < 0)
    res = position - 1;
  else
    res = position;
  ui->line_scale->setText(QString::number(res));
  if (res == 0) res++;
  ui->screen->setScale(res);
}

void MainWindow::on_dial_move_x_sliderMoved(int position) {
  ui->line_move_x->setText(QString::number(position));
  ui->screen->setMove(1, 0, 0, position);
}

void MainWindow::on_dial_move_y_sliderMoved(int position) {
  ui->line_move_y->setText(QString::number(position));
  ui->screen->setMove(0, 1, 0, position);
}

void MainWindow::on_dial_move_z_sliderMoved(int position) {
  ui->line_move_z->setText(QString::number(position));
  ui->screen->setMove(0, 0, 1, position);
}

void MainWindow::recordGif() {
  static int count = 0;
  if (count < 50) {
    ui->screen->grabFramebuffer()
        .scaled(640, 480, Qt::IgnoreAspectRatio)
        .save("tmp/" + QString::number(count) + ".bmp", NULL, 100);
    count++;
  }
  if (count == 50) {
    timer->stop();
    count = 0;
    makeGif();
  }
}

void MainWindow::makeGif() {
  QString qpath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
  if (!qpath.isNull()) {
    std::string tmp = qpath.toStdString();
    const char *path = tmp.c_str();

    GifWriter g = {};
    GifBegin(&g, path, 640, 480, 10);
    for (int i = 0; i < 50; ++i) {
      QImage img("tmp/" + QString::number(i) + ".bmp");
      GifWriteFrame(&g,
                    img.convertToFormat(QImage::Format_RGBA8888).constBits(),
                    640, 480, 10);
    }
    GifEnd(&g);
  }

  QDir("tmp").removeRecursively();
  ui->recordButton->setDisabled(0);
  ui->recordButton->setText("RECORD");
}

void MainWindow::on_recordButton_clicked() {
  ui->recordButton->setText("REC...");
  ui->recordButton->setDisabled(1);
  QDir *pathtmp = new QDir();
  pathtmp->mkdir("tmp");
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(recordGif()));
  timer->start(100);
}

void MainWindow::on_lineColorButton_clicked() {
  QColor color = setColor(ui->lineColorButton);

  if (color.isValid()) {
    lineColor = color;
    ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                               vertexColor, ui->vertexSlider->value(),
                               vertexType, backgroundColor);
  }
}

void MainWindow::on_vertexColorButton_clicked() {
  QColor color = setColor(ui->vertexColorButton);

  if (color.isValid()) {
    vertexColor = color;
    ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                               vertexColor, ui->vertexSlider->value(),
                               vertexType, backgroundColor);
  }
}

void MainWindow::on_lineSlider_actionTriggered(int action) {
  lineSize = ui->lineSlider->value();
  ui->lineLabel->setText(QString::number(ui->lineSlider->value()));
  ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                             vertexColor, ui->vertexSlider->value(), vertexType,
                             backgroundColor);
}

void MainWindow::on_vertexSlider_actionTriggered(int action) {
  vertexSize = ui->vertexSlider->value();
  ui->vertexLabel->setText(QString::number(ui->vertexSlider->value()));
  ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                             vertexColor, ui->vertexSlider->value(), vertexType,
                             backgroundColor);
}

QColor MainWindow::setColor(QPushButton *button) {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (color.isValid()) {
    QPalette palette = button->palette();
    palette.setColor(QPalette::Button, color);
    button->setPalette(palette);
    button->setAutoFillBackground(true);
    button->setFlat(true);
  }

  return color;
}

void MainWindow::setColorForButton(QPushButton *button, QColor color) {
  button->setPalette(QPalette(color));
  button->setAutoFillBackground(true);
  button->setFlat(true);
}

void MainWindow::on_comboBox_LineType_activated(int index) {
  lineType = index;
  ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                             vertexColor, ui->vertexSlider->value(), vertexType,
                             backgroundColor);
}

void MainWindow::on_comboBox_VertexType_activated(int index) {
  vertexType = index;
  ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                             vertexColor, ui->vertexSlider->value(), vertexType,
                             backgroundColor);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->colorWidget) {
    if (event->type() == QEvent::MouseButtonPress) {
      QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
      if (color.isValid()) {
        backgroundColor = color;
        ui->colorWidget->setStyleSheet(
            QString("background-color: %1").arg(color.name()));
        ui->screen->updateSettings(lineColor, ui->lineSlider->value(), lineType,
                                   vertexColor, ui->vertexSlider->value(),
                                   vertexType, backgroundColor);
      }
    }
  }

  return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_reset_clicked() {
  ui->scale_slider->setSliderPosition(0);
  ui->line_scale->setText("1");
  ui->screen->resetData();
  ui->dial_move_x->setSliderPosition(0);
  ui->dial_move_y->setSliderPosition(0);
  ui->dial_move_z->setSliderPosition(0);
  ui->line_move_x->setText("0");
  ui->line_move_y->setText("0");
  ui->line_move_z->setText("0");
  ui->dial_rotate_x->setSliderPosition(0);
  ui->dial_rotate_y->setSliderPosition(0);
  ui->dial_rotate_z->setSliderPosition(0);
  ui->line_rotate_x->setText("0");
  ui->line_rotate_y->setText("0");
  ui->line_rotate_z->setText("0");
}
