#include "stdafx.h"
#include "docwidget.h"
using namespace std;
DocWidget::DocWidget(int _id, QWidget* parent)
	:QMdiSubWindow(parent)
{
	//setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	showMaximized();
	setAttribute(Qt::WA_DeleteOnClose);
	id = _id;
}
int DocWidget::getId()const {
	return id;
}

void DocWidget::closeEvent(QCloseEvent* event) {
	int closeBox = QMessageBox::question(
		this, "�ĵ��Ӵ���", "��ȷ��Ҫ�˳���"
	);
	if (closeBox == QMessageBox::Yes) {
		event->accept();
	}
	else {
		event->ignore();
	}
}
void DocWidget::changeEvent(QEvent* event) {
	//qDebug() << "DocWidget::changeEvent";
	QMdiSubWindow::changeEvent(event);
}
void DocWidget::resizeEvent(QResizeEvent* event) {
	//qDebug() << "DocWidget::resizeEvent";
	QMdiSubWindow::resizeEvent(event);
}
void DocWidget::focusInEvent(QFocusEvent* event) {
	emit getFocus(this);
	//qDebug() << getId() << ": getFocus,this="<<this;
	QMdiSubWindow::focusInEvent(event);
}
void DocWidget::focusOutEvent(QFocusEvent* event) {
	QMdiSubWindow::focusOutEvent(event);
}
