#pragma once
#include "stdafx.h"
//  �ַ�����
#include "spellcorrector.h"
//  Ŀ����
#include "objdetector.h"
//  ��������
#include "classifier.h"
#include <QPainterPath>
#include <QList>
//  ����Qt���������ʼ�����
class RawScript :public QObject {
	Q_OBJECT
public:
	class PainterPath :public QPainterPath {
		//  TODO:��дboundingRect�Ⱥ���
	public:
		PainterPath();
		PainterPath(const QPoint& start);
	private:
	protected:
	};
	RawScript();
	~RawScript();
	void setPanel(const QWidget* _panel);
	void setImage(const QPixmap* _pixmap);
	PainterPath curStroke;
	//  ��curStroke����QList�����curStroke
	void pushStroke();
	//  ������бʻ�����ջ���
	void clear();
	//  ɾ��script�����һ��
	void popStroke();
	//  ɾ����rubberPath�ཻ�ıʻ�
	void popStroke(const QPainterPath& rubberPath);
	//  ɾ��script�а����ھ���innerPoint��scale��ĵ�
	void popStroke(const QPoint& innerPoint, QPoint scale = QPoint(5, 5));
	//  ����script�Ļ���ģ�������
	const QList<PainterPath>& getScript();
	//public slots:
		//  ʶ��ɣ�С����
	const std::vector<std::vector<std::string>>& recognize();
private:
	//  Լ������һ�㣬��result[0]����Ѵ𰸣���n������
	//  ��һ��ʶ���k���ַ���������k��QList��ÿ��QList���ki����ѡ������޸�
	std::vector<std::vector<std::string>> results;
	QList<PainterPath> script;
	SpellCorrector corrector;
	Classifier classifier;
	ObjDetector detector;
	const QSize yoloBaseSize = QSize(512, 416);
	const QSize fdeepBaseSize = QSize(32, 32);
	const double K_leak = 0.5, K_allowIn = 0.1;
	//  ����l��m��r����ʾb��a����ࡢ���������Ҳ�
	char diff(const QRectF& a, const QRectF& b);
	QWidget* panel;
	QPixmap* pixmap;
	QPixmap blankImg;
};