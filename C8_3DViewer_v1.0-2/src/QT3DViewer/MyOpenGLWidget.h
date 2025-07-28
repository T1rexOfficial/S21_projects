#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QColor>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#ifdef __cplusplus
extern "C" {
#endif
#include "viewer_back.h"
#ifdef __cplusplus
}
#endif
//#include <gl/GLU.h>
//#pragma comment(lib,"opengl32.lib")
//#pragma comment(lib,"GLU32.lib")

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
  friend class MainWindow;

 public:
  std::string path;
  MyOpenGLWidget(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void setProjection(int projection);
  void setRotate(int flagx, int flagy, int flagz, int val);
  void setScale(int new_val);
  void setMove(int flagx, int flagy, int flagz, int val);
  void updateSettings(QColor lineColor, double lineSize, int lineType,
                      QColor vertexColor, double vertexSize, int vertexType,
                      QColor backgroundColor);

  void reloadModel();
  void resetData();

 private:
  vertexes_t vv = {0};
  facets_t ff = {0};
  vertexes_t vv_copy = {0};
  facets_t ff_copy = {0};
  int projection;
  int rotateX, rotateY, rotateZ;
  int cnt_v, cnt_f;
  int scale_val;
  int moveX, moveY, moveZ;
  QColor lineColor;
  QColor vertexColor;
  double lineSize;
  double vertexSize;
  int lineType;
  int vertexType;
  QColor backgroundColor;
};

#endif  // MYOPENGLWIDGET_H
