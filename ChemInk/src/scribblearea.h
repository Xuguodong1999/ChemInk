#pragma once
//  ��дʶ��ӿ�
#include "rawscript.h"
//  Ӧ�ýӿ�
#include "chembalancer.h"	//  ��ѧ����ʽ��ƽ����ѧ���Ž���
//  ����������ƶ���ͷ�ļ�"browser.h"��
//#include "alkanetopo.h"		//  ���������ǹ�ѧͬ���칹�����������
//#include "forcefield.h"		//  ��������
//  Ӧ�ý������
#include "browser.h"

#include <QWidget>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMoveEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QPen>

// ScribbleArea��ά�����ػ��壬���ṩ�κ�ʸ���������ܣ����ṩ��������Ƥ�ͱ�֮����κλ��幤�ߣ����ṩundo��redo����
class ScribbleArea : public QWidget {
	//  ScribbleArea��Ƴ�����ķ��
	Q_OBJECT
public:
	ScribbleArea(QWidget* parent = nullptr);

signals:
	void updateInScribbleArea();
protected:
	//  ������ʺ���Ƥ
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	//  ���͸�������
	void mouseReleaseEvent(QMouseEvent* event) override;
	//  ����ctrl+�������¼�
	void wheelEvent(QWheelEvent* event)override;

	//  ���������
	void paintEvent(QPaintEvent* event)override;
	//  ���������ŵر���Ч����С
	//  ֧���Զ��Ŵ󣬲��ԣ�������Ե�ƶ����ұ߿����󲻻ᳬ����Ļ��Χ����������ƶ�����������д����
	void resizeEvent(QResizeEvent* event) override;
	void moveEvent(QMoveEvent* event)override;
	void closeEvent(QCloseEvent* event)override;
private:
	//  �ṩ��̬���ֹ���
	int scaleK;
	QToolButton* rubberBtn, * pencilBtn, * setBtn, * clsBtn;
	QLabel* screenLabel;
	void updateLayout();

	//  �ṩ��Ƥ����
	QPen pen, rubber;
	bool isPen, justResized;
	QPainterPath rubberPath;
	void repaintRawScript();

	//  �ʼ������ṩʶ��ӿ�
	RawScript rs;

	//  ��ͼ����
	QPixmap* instBuffer;

	//  �ṩ����onenote��дʶ�����Զ��Ŵ���
	QPoint lastPos, curPos;
	QRect upBorder, downBorder, leftBorder, rightBorder;
	void autoResize();

	ChemBalancer chembalancer;

	Browser browser;

	//  �򵥵��߳�ͬ��
	int countCall;
	bool allowIn;
};
