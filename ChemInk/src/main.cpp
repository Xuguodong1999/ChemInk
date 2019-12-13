#include "stdafx.h"
#include "scribblearea.h"
#include <QApplication>
#include <QTranslator>
using namespace std;
#pragma execution_character_set("UTF-8")

#ifdef LINK_STATIC_QT5
#include <QtCore/QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif // STATIC_BUILDBY_MSVC

int main(int argc, char* argv[]) {
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QApplication::setOrganizationName(QObject::tr("�Ͼ���ѧ�������ѧ�뼼��ϵ"));
	QApplication::setApplicationVersion(QObject::tr("2019.12.13"));
	QApplication::setApplicationName(QObject::tr("ChemInk ��ѧ��ʽ����д������Ӧ��ϵͳ"));
	QApplication app(argc, argv);
	QTranslator translator;
	if (translator.load(":/ChemInk/Resources/qt_zh_CN.qm"))
		app.installTranslator(&translator);
	else {
		return throwErrorBox("Error Message", "Fail to load(\":/ChemInk/Resources/qt_zh_CN.qm\")!");
	}
	if (-1 == _putenv(QString("BABEL_DATADIR=" + QApplication::applicationDirPath() + "/data").toStdString().c_str()))
		return throwErrorBox("Error Message", "Fail to set BABEL_DATADIR!");
	ScribbleArea w;
	w.resize(getDesktopSize() / 1.5);
	w.show();
	return app.exec();
}
