#pragma once
#include <QPainterPath>
#include <QString>
#include <QRect>
#include <QPoint>
#include <vector>
#include <map>
using namespace std;

//  ��ʸ����ʽ����ش���ַ�����

class CharInfo {
public:
	CharInfo();
	QPainterPath path;	//  ·�����꣬д��󲻵ø���
	int w, h;
	QRect boundingRect;	//  �߿����꣬����������Ϣ����
	QPoint blockPos;	//  ���ַ����е�λ�ã������ַ����ʱ�����
	QPoint imgPos;		//  �ڻ����ϵ�λ�ã�д���ַ����ʱ��ʹ��
	qreal k;			//  ����ϵ���������Ͻ�Ϊ�������ţ�д�뻷��ʹ��
	QString label;		//  ��ǩ
	void set(const vector<vector<pair<int, int>>>& script,string& _label);
	void collectRect();
};

/*
�������̣�
�ַ�-(����̮����ƴ��)->
�ַ���-(�ڻ���������ײ���)->
д�뻭��-(�ﵽһ����������)->���� or ����
*/

class CharBlock {
public:
	QList<CharInfo> b;
	QPoint imgPos;		//  �ַ����ڻ����ϵ�λ��
	void setImgPos(const QPoint&p);
	QRect boundingRect;	//  �ַ������С�߿�
	void append(const CharInfo& newChar);
};