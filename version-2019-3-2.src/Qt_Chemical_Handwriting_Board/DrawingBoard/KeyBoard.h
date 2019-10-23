﻿#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>
#include "ui_KeyBoard.h"
#include <QString>
class KeyBoard : public QWidget
{
	Q_OBJECT
public:
	KeyBoard(QWidget *parent = Q_NULLPTR);
	~KeyBoard();
private:
	Ui::KeyBoard ui;
signals:
	void sendCloseSignalforKeyBoard();
	void sendData(QString _data);
private slots:
	void returnDrawingBoard();
	void h();
	void he();
	void li();
	void be();
	void b();
	void c();
	void n();
	void o();
	void f();
	void ne();
	void na();
	void mg();
	void al();
	void si();
	void p();
	void s();
	void cl();
	void ar();
	void k();
	void ca();
	void sc();
	void ti();
	void v();
	void cr();
	void mn();
	void fe();
	void co();
	void ni();
	void cu();
	void zn();
	void ga();
	void ge();
	void as();
	void se();
	void br();
	void kr();
	void rb();
	void sr();
	void y();
	void zr();
	void nb();
	void mo();
	void tc();
	void ru();
	void rh();
	void pd();
	void ag();
	void cd();
	void in();
	void sn();
	void sb();
	void te();
	void i();
	void xe();
	void cs();
	void ba();
	void la();
	void ce();
	void pr();
	void nd();
	void pm();
	void sm();
	void eu();
	void gd();
	void tb();
	void dy();
	void ho();
	void er();
	void tm();
	void yb();
	void lu();
	void hf();
	void ta();
	void w();
	void re();
	void os();
	void ir();
	void pt();
	void au();
	void hg();
	void tl();
	void pb();
	void bi();
	void po();
	void at();
	void rn();
	void fr();
	void ra();
	void ac();
	void th();
	void pa();
	void u();
	void np();
	void pu();
	void am();
	void cm();
	void bk();
	void cf();
	void es();
	void fm();
	void md();
	void no();
	void lr();
	void rf();
	void db();
	void sg();
	void bh();
	void hs();
	void mt();
	void ds();
	void rg();
	void add();
	void equals();
	void backspace();
	void bracketLeft();
	void bracketRight();
	void positive();
	void negative();
	void with();
	void zero();
	void one();
	void two();
	void three();
	void four();
	void five();
	void six();
	void seven();
	void eight();
	void nine();
};
#endif 
