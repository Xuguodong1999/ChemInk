/*  ���Ӳ���˵����
��Ŀ¼ͨ��VS��GUI����ֱ�ӱ༭vcxproj������
Ҫ���ӵľ�̬����stdafx.cpp�ļ���#pragma comment(lib,"xxx.lib")����
*/

//  ����openbabel-2.4.1��̬��
#define LINK_BABEL2

//  ����opencv4.1.1��̬��
#define LINK_CV411

//  ����Qt5��̬��
//  #define LINK_STATIC_QT5

#include <QSize>

int throwErrorBox(const char* windowTitle, const char* message);

QSize getDesktopSize();

int loadBabelPlugin();
