#pragma once
#include <QPainterPath>
#include <QImage>
#include <QPainter>
#include <chrono>
#include <iostream>
#include <QDebug>
#include <QList>
#include <QPair>
#include <vector>
#include <cassert>
#include <random>
#include <map>

using namespace std;

#define CHARINFO QPair<QPainterPath>

class Generator {
public:
	Generator();
	~Generator();
	/*�����Ѿ���ɹ�һ����ԭʼ���ݣ����ر�ʾ�����ַ���QPainterPath*/
	static QPainterPath getPath(const vector<vector<pair<int, int>>>& script);
	/*����������painterpath��painterpathд������Ϊwidth��channels��QImage������*/
	static QImage getSingleImage(const QPainterPath& script, int width = 64, int channels = 3);
	/*��script��ʾ���ַ�Ƕ��src���ռ䲻���򷵻�false*/
	static bool addToImage(QImage& src, const QPainterPath& script);

	/*�����������ݼ��ϵ���Ӳ���*/
	static void merge(
		const vector<vector<vector<pair<int, int>>>>& _imgs,
		const vector<int>& _intLabels,
		const char* dir = "E:/test/"
	);

	static int
		charCounter,				//  ��ǰ��ȡ���ַ�����
		fileCounter,				//  �����ɵ��ļ�����
		blockCharCounter,			//  ���ַ����е��ַ�����
		maxRandBlockCharCounter,	//  ������ַ����У��ַ���������
		maxRandCounter;				//  ���������ޣ�������maxCounter

	static const int
		maxCounter,					//  һ��ͼ�����ô���ַ�
		maxBlockCharCounter;				//  һ���������ô���ַ�

	static const QRect baseOutline;		//  ��߿�

	static QList<QRect> existedRects;	//  ���в�����ײ���ı߿�

	static bool IsValidNewRect(const QRect& newRect);

	static bool isIn(const QRect& big, const QRect& small);

	static QRect refRect;//  ��Բ�����һ���±߿�Ĳο�λ�ã�һ�������±߿���������λ��
	static bool IsLower;



	static bool randGenStart(const QSize& fixedSize, QPoint& startPos, const int maxTry = 100);
};