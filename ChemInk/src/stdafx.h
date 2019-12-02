#include <map>
#include <list>
#include <tuple>
#include <string>
#include <vector>
#include <thread>

#include <cmath>
#include <cstdio>
#include <climits>

#include <sstream>
#include <iostream>
#include <memory>
#include <algorithm>

/*
��Ҫʹ��cout���ļ���Ҫ�� #pragma execution_character_set("GB2312") ���utf-8����
*/
#pragma execution_character_set("UTF-8")

/*  ���Ӳ���˵����
��Ŀ¼ͨ��VS��GUI����ֱ�ӱ༭vcxproj������
Ҫ���ӵľ�̬����stdafx.cpp�ļ���#pragma comment(lib,"xxx.lib")����
*/

/*��������ͷ�ļ��������ԣ�
ͨ��VS��GUI����ֱ�ӱ༭vcxproj������
<IncludePath>
$(SolutionDir)ChemInk/third_party/eigen3.3.7;$(SolutionDir)ChemInk/third_party/json/include;$(SolutionDir)ChemInk/third_party/FunctionalPlus/include;$(SolutionDir)ChemInk/third_party/frugally-deep/include;$(SolutionDir)ChemInk/third_party/opencv-4.1.1/include;$(SolutionDir)ChemInk/third_party/opencv-4.1.1/include/opencv2;$(SolutionDir)ChemInk/third_party/openbabel-2.4.1/openbabel/include/openbabel-2.0;
</IncludePath>
*/

//  ����Eigen3ͷ�ļ�ȫ��Ͱ
#define INCLUDE_EIGEN3

//  ����QT5ͷ�ļ�ȫ��Ͱ
#define INCLUDE_QT5

//  ����openbabel-2.4.1��̬��
#define LINK_BABEL2

//  ����opencv4.1.1��̬��
#define LINK_CV411

//  ����Qt5��̬��
//#define LINK_STATIC_QT5

//  ���밲׿Ȩ��
//  #define ANDROID_BUILDBY_WIN_QMAKE

#ifdef INCLUDE_EIGEN3
//  ����һ��Eigenȫ��Ͱ
#include <Eigen/Cholesky>
//#include <Eigen/QR>
//#include <Eigen/QtAlignedMalloc>
#include <Eigen/Sparse>
#include <Eigen/Core>
//#include <Eigen/SparseCholesky>
#include <Eigen/Dense>
//#include <Eigen/SparseCore>
//#include <Eigen/Eigen>
//#include <Eigen/SparseLU>
//#include <Eigen/Eigenvalues>
//#include <Eigen/SparseQR>
//#include <Eigen/Geometry>
//#include <Eigen/Householder>
//#include <Eigen/StdDeque>
//#include <Eigen/IterativeLinearSolvers>
#include <Eigen/StdList>
//#include <Eigen/Jacobi>
#include <Eigen/StdVector>
//#include <Eigen/LU>
//#include <Eigen/SVD>
//#include <Eigen/OrderingMethods>

//  �����ͷ�ļ�û�б�Ҫ����
//#include <Eigen/PaStiXSupport>
//#include <Eigen/CholmodSupport>
//#include <Eigen/SPQRSupport>
//#include <Eigen/SuperLUSupport>
//#include <Eigen/MetisSupport>
//#include <Eigen/PardisoSupport>
#endif // INCLUDE_EIGEN3

#ifdef INCLUDE_QT5
//  ���ƶ�������ʹ��gl��
#ifndef ANDROID_BUILDBY_WIN_QMAKE
//  ��Ҫֱ�Ӱ���windows.h
//  �����и�min�ĺ궨��
//  ����std::numeric<?>::min()ʧЧ
#define WINGDIAPI __declspec(dllimport)
#define APIENTRY _stdcall
#define CALLBACK _stdcall
//  #include <Windows.h>
//#include <gl/GL.h>
#include <gl/GLU.h>
#include <QGLWidget>
#endif // !ANDROID_BUILDBY_WIN_QMAKE

//  ����һ��Qtͷ�ļ�
#include <QStyleFactory>
#include <QVector>
#include <QString>
#include <QList>
#include <QHash>
#include <QMap>

#include <QSize>
#include <QPointer>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QMessageBox>
#include <QErrorMessage>

#include <QProgressBar>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>

#include <QOpenGLWindow>
#include <QMatrix4x4>
#include <QVector3D>
#include <QImage>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>
#include <QPropertyAnimation>
#include <QPauseAnimation>
#include <QSurfaceFormat>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QStyle>
#include <QIcon>
#include <QToolButton>
#include <QLabel>
#include <QMenu>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QDialog>
#include <QMdiSubWindow>

#include <QScrollArea>
#include <QWidget>
#include <QDockWidget>
#include <QMdiArea>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QTranslator>
#include <QApplication>
#include <QDesktopWidget>

#include <QLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#endif // INCLUDE_QT5

#ifdef ANDROID_BUILDBY_WIN_QMAKE
bool requestPermission(QString moduleName);
#endif // ANDROID_BUILDBY_WIN_QMAKE

int throwErrorBox(const char* windowTitle, const char* message);

QSize getDesktopSize();

int loadBabelPlugin();
