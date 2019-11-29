#pragma once
#include "stdafx.h"
#include "scribblescene.h"

//  ʵ��΢��PPT���Ԥ����Ŀ��Ч��
//  QScrollAreaֻ�ܹ���һ������������������ɶ�����ܸ�
//  ��Ҫ�Լ������ֹ������źŹ������Ӵ������
//  ��Ҫ�Ľӿڣ�
//  1�����źţ�����һ�������ָ�룬�洢���ڲ������µ��Ӵ��壬����Ԥ��ͼ��
//  ����һ���źţ����������壬��������źţ�ָʾ���ĵ�������ĸ��ĵ��������
//  2�������źţ�����һ�������ָ�룬�����洢�����ҵ���ѡ��������ظ�û�ҵ�
//  3����дresize�¼�������������������ʱ��Ԥ��ͼ����Ӧ����
//  4���Ӵ������ж��ĵ��������ṩ��������ͬʱ����ɾ��������
class PreviewScrollArea :public QScrollArea {
	Q_OBJECT
public:
	PreviewScrollArea(QWidget* parent = nullptr);
	void setSceneMapPointer(QMap<int, ScribbleScene*>* _sceneMapPointer);
protected:
	void resizeEvent(QResizeEvent* event)override;

private:
	QMap<int, ScribbleScene*>* sceneMapPointer;
	QMap<int, QLabel*> previewMap;
public slots:
	void updatePreview(const std::vector<int>& modifiedViewIds);
};