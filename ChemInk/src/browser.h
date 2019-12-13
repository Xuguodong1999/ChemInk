#pragma once

#include "glumolwindow.h"
#include "chembalancer.h"
#include "spellcorrector.h"
#include "alkanetopo.h"		//  ���������ǹ�ѧͬ���칹�����������
#include "forcefield.h"		//  ��������
#include <QMap>
#include <QList>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QResizeEvent>
#include <QCloseEvent>

class LabelButton :public QLabel {
	Q_OBJECT
public:
	LabelButton(QWidget* parent = nullptr);
signals:
	void btnClicked(LabelButton* address);
public:
	QString plainText, htmlText;
	int prefix;
protected:
	void mousePressEvent(QMouseEvent* event)override;
};
class Browser :public QWidget {
	Q_OBJECT
public:
	Browser(QWidget* parent = nullptr);
	/*Ϊ���а�������ı�ǩԪ�ش����źźͲ�*/
	void setEleBox(const std::vector<std::vector<std::string>>& _elements);
signals:
	void iAmClosed();
private:
	QGridLayout* mainLayout;
	QHBoxLayout* eleBoxLayout;
	GluMolWindow* molWindow;
	QToolButton* leftBtn, * rightBtn;
	QList<QPair<QString, LabelButton*>> elements;
	std::vector<std::vector<std::string>>* eledata;
	ChemBalancer chembalancer;
	Molecule mol;
	ForceField forcefield;
	AlkaneTopo alkanetopo;
	QMap<LabelButton*, std::vector<std::string>> smilesDatas;
	std::vector<std::string>::iterator smilesIter;
	LabelButton* clickedBtn;
	void updatelabelText();
	QLabel* screen;
private slots:
	void updateMolWindow(const char* smiles);
	void handleBtnClickEvent(LabelButton* address);
protected:
	void closeEvent(QCloseEvent* event)override;
	void resizeEvent(QResizeEvent* event)override;
};
