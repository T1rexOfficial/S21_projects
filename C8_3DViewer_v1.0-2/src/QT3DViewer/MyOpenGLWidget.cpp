#include "MyOpenGLWidget.h"

#include <iostream>

#include "viewer_back.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  projection = 1;
  rotateX = rotateY = rotateZ = 0;
  scale_val = 1;
  moveX = moveY = moveZ = 0;
  read_obj(path.c_str(), &vv, &ff);
  read_obj(path.c_str(), &vv_copy, &ff_copy);
  cnt_v = vv.sz;
  cnt_f = ff.sz;
}

void MyOpenGLWidget::reloadModel() {
  clear_vertex(&vv);
  clear_facets(&ff);
  clear_vertex(&vv_copy);
  clear_facets(&ff_copy);

  read_obj(path.c_str(), &vv, &ff);
  read_obj(path.c_str(), &vv_copy, &ff_copy);
  cnt_v = vv.sz;
  cnt_f = ff.sz;
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClear(GL_COLOR_BUFFER_BIT);

  glClearColor(0.77f, 0.30f, 0.30f, 1.0f);
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  int side = qMin(w, h);
  glViewport((w - side) / 2, (h - side) / 2, side, side);
}

void MyOpenGLWidget::paintGL() {
  float red = backgroundColor.redF();
  float green = backgroundColor.greenF();
  float blue = backgroundColor.blueF();
  glClearColor(red, green, blue, 1.0f);  // Установка нового цвета фона

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  for (int i = 0; i < (vv.sz); ++i) {
    vv.v[i].x = vv_copy.v[i].x;
    vv.v[i].y = vv_copy.v[i].y;
    vv.v[i].z = vv_copy.v[i].z;
  }

  cnt_v = vv.sz;
  cnt_f = ff.sz;

  p3f center = calc_center(&vv);

  int MaxLength = vv.max_len;
  //    int ratioW = 1, ratioH = 1;

  GLfloat h = this->height();
  GLfloat w = this->width();
  GLfloat ratioW = (w > h) ? w / h : 1;
  GLfloat ratioH = (w > h) ? 1 : h / w;

  if (projection == 0)
    glOrtho(-2 * MaxLength * ratioW, 2 * MaxLength * ratioW,
            -3 * MaxLength * ratioH, 3 * MaxLength * ratioH, -4 * MaxLength,
            2 * MaxLength);
  else
    glFrustum(-MaxLength * ratioW, MaxLength * ratioW, -MaxLength * ratioH,
              MaxLength * ratioH, 0.8 * MaxLength, 10 * MaxLength);

  scale(&vv, ((scale_val >= 1) ? scale_val : (-1.0 / scale_val)));

  rotate(&vv, 'x', 1.0 * rotateX * (M_PI / 180.0));
  rotate(&vv, 'y', 1.0 * rotateY * (M_PI / 180.0));
  rotate(&vv, 'z', 1.0 * rotateZ * (M_PI / 180.0));

  float new_result_x = ((moveX != 0) ? ((moveX / 100.0) * MaxLength) * 2 : 0);
  float new_result_y = ((moveY != 0) ? ((moveY / 100.0) * MaxLength) * 2 : 0);
  float new_result_z = ((moveZ != 0) ? ((moveZ / 100.0) * MaxLength) * 2 : 0);

  shift(&vv, new_result_x, new_result_y, new_result_z);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glLineWidth(lineSize);  // Ширина линии
  glColor3ub(lineColor.red(), lineColor.green(),
             lineColor.blue());  // Цвет линии

  if (lineType == 1) {
    glEnable(GL_LINE_STIPPLE);  // Пунктирная линия
    glLineStipple(1, 0x00ff);   // Пунктирная линия
  }

  glBegin(GL_LINES);

  for (int i = 0; i < ff.sz; ++i) {
    unsigned int i1 = ff.f[i].first, i2 = ff.f[i].second;
    glVertex3f((vv.v[i1 - 1].x), (vv.v[i1 - 1].y),
               (vv.v[i1 - 1].z) - 2 * MaxLength * projection);
    glVertex3f((vv.v[i2 - 1].x), (vv.v[i2 - 1].y),
               (vv.v[i2 - 1].z) - 2 * MaxLength * projection);
  }

  glEnd();

  if (lineType == 1) {
    glDisable(GL_LINE_STIPPLE);
  }

  glPointSize(vertexSize);  // Размер точек
  glColor3ub(vertexColor.red(), vertexColor.green(),
             vertexColor.blue());  // Цвет точек

  if (vertexType == 1) {
    glEnable(GL_POINT_SMOOTH);  // Круглые точки
  }

  if (vertexType != 2) {
    glEnable(GL_BLEND);
    glBegin(GL_POINTS);

    for (int i = 0; i < ff.sz; ++i) {
      unsigned int i1 = ff.f[i].first, i2 = ff.f[i].second;
      glVertex3f((vv.v[i1 - 1].x), (vv.v[i1 - 1].y),
                 (vv.v[i1 - 1].z) - 2 * MaxLength * projection);
      glVertex3f((vv.v[i2 - 1].x), (vv.v[i2 - 1].y),
                 (vv.v[i2 - 1].z) - 2 * MaxLength * projection);
    }

    glEnd();
  }

  if (vertexType == 1) {
    glDisable(GL_POINT_SMOOTH);
  }

  glFlush();
}

void MyOpenGLWidget::setProjection(int projection) {
  this->projection = projection;
  repaint();
}

void MyOpenGLWidget::setRotate(int flagx, int flagy, int flagz, int val) {
  if (flagx == 1) this->rotateX = val;
  if (flagy == 1) this->rotateY = val;
  if (flagz == 1) this->rotateZ = val;
  repaint();
}

void MyOpenGLWidget::setMove(int flagx, int flagy, int flagz, int val) {
  if (flagx == 1) this->moveX = val;
  if (flagy == 1) this->moveY = val;
  if (flagz == 1) this->moveZ = val;
  repaint();
}

void MyOpenGLWidget::setScale(int new_scale) {
  this->scale_val = new_scale;
  repaint();
}

void MyOpenGLWidget::updateSettings(QColor lineColor, double lineSize,
                                    int lineType, QColor vertexColor,
                                    double vertexSize, int vertexType,
                                    QColor backgroundColor) {
  this->lineColor = lineColor;
  this->lineSize = lineSize;
  this->lineType = lineType;
  this->vertexColor = vertexColor;
  this->vertexSize = vertexSize;
  this->vertexType = vertexType;
  this->backgroundColor = backgroundColor;
  repaint();
}

void MyOpenGLWidget::resetData() {
  rotateX = rotateY = rotateZ = 0;
  scale_val = 1;
  moveX = moveY = moveZ = 0;
  repaint();
}
