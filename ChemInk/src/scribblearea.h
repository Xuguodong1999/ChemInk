#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QPen>

#include <vector>
#include <list>

enum DrawingStyle { BLACKBOARD, WHITEBOARD, PAPER, RICEPAPER };

class Stroke :public QRect{
	std::vector<QPoint> points;
public:
    Stroke(QPoint& _p);
    ~Stroke();
    void push_back(QPoint& _p);
	void setRect();// ��һ��д���Ժ��ٵ��ã���ʱӦ��С������ʶ�������Ӱ��������
	//  void contains(QPoint& _p);
    QPoint& at(int i);
	std::vector<QPoint>* getPoints();
};

//  ά����д���û����飬ά���ʼ����ݣ�ά���ɵ������
class ScribbleArea : public QWidget {
	Q_OBJECT
private:
	std::list<Stroke>* script;// ��¼��ʷ���ݵ�ʱ��ֱ�Ӱ����ָ��Ŀռ�ת���ϲ�����߼�¼
	std::vector<QRect> rubber;
public:
	ScribbleArea(QWidget* parent = nullptr);
	~ScribbleArea();
	std::list<Stroke>* getScript();
	QPixmap* getInstBuffer();
	void clear();
signals:
	void sendStrokeData(std::list<Stroke>* _script);
	void askForRecognize();
	
public slots:
	void acceptRubber(bool _isPen);
	void cancelStroke();//  ����rubber���������бʻ���ע��list�������Ĺ���
	void undo();// ��������Ļ�ͼ�¼�
	void reloadStroke(std::list<Stroke>* _script);
	void loadStyle(DrawingStyle _drawingstyle);
	

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void paintEvent(QPaintEvent* event)override;
	void resizeEvent(QResizeEvent* event) override;

private:
	//  ���������õ������ݽṹ
	QPen pen;
	QPoint lastPos;
	bool isDragging;
	bool isPen;
	QPixmap instBuffer,procBuffer;	//  ������д���壬����ֻ����ʼ�
	QPixmap cursorPix, backPix, brushPix, rubberPix;//  ��ꡢ������Ϳѻ��ʽ
	DrawingStyle drawingstyle;
	void loadStyle();
	void drawline(const QPoint& _from, const QPoint& _to, QPaintDevice& _device);

	void repaintByBezier();
	void repaintRawScript();
};

std::vector<QPoint> bezier(std::vector<QPoint> rawpoints);
