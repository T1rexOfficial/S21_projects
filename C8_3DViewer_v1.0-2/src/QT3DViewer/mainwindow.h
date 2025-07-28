#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QDoubleSpinBox>
#include <QErrorMessage>
#include <QFileDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QMovie>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QScreen>
#include <QSettings>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <algorithm>

#include "MyOpenGLWidget.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "viewer_back.h"
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

  void on_center_radiobutton_clicked();
  void on_parallel_radiobutton_clicked();

  void on_dial_rotate_x_sliderMoved(int position);
  void on_dial_rotate_y_sliderMoved(int position);
  void on_dial_rotate_z_sliderMoved(int position);

  void on_scale_slider_sliderMoved(int position);

  void on_dial_move_x_sliderMoved(int position);
  void on_dial_move_y_sliderMoved(int position);
  void on_dial_move_z_sliderMoved(int position);

  void onUpModelClicked();

  void recordGif();
  void makeGif();

  void on_recordButton_clicked();

  void on_lineColorButton_clicked();
  void on_vertexColorButton_clicked();

  void on_lineSlider_actionTriggered(int action);
  void on_vertexSlider_actionTriggered(int action);

  void saveJpeg();
  void saveBmp();
  void savePng();
  void saveImage();

  QColor setColor(QPushButton *button);
  void setColorForButton(QPushButton *button, QColor color);

  bool eventFilter(QObject *obj, QEvent *event);

  void on_comboBox_LineType_activated(int index);

  void on_comboBox_VertexType_activated(int index);

  void on_reset_clicked();

 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *gl;
  QTimer *timer;
  QMovie mo;
  QString m_imageFormat = "jpeg";
  QString selectedFormat;
  QColor lineColor;
  QColor vertexColor;
  int lineSize;
  int vertexSize;
  int lineType;
  int vertexType;
  QColor backgroundColor;
  QSettings settings;
};

#endif  // MAINWINDOW_H
