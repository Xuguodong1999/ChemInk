#include "stdafx.h"
#include "mainwindow.h"
#include "forcefield.h"
#include "molecule.h"
#include "glumolwindow.h"
#include "scribblearea.h"
using namespace std;
/*
Ӧ�ÿ�������¼��
1����openbabel��opencv����������ԭ��
2�����ػ��������eigen������е�������
3�����ñ�׼����ñ�׼�⣬���о���Qt�⣬�ٲ��в��õ�������
4��UI��������һ��(qwidget)���ƶ���һ��(qml)�ķ���������Ӧ�ÿ��Ǵ���������������
5��UI��ƶԱ�2019���word��ppt
6����ѧרҵ�Ա�openchemistryȫ��Ͱ
7������Ա�����
8����˼�������ع���һ�����ع��ı�Ҫ�������ع�����Ҫ��
*/
#ifdef LINK_STATIC_QT
#include <QtCore/QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif // STATIC_BUILDBY_MSVC

//  #define TEST_BABEL
//  #define TEST_GL
//  #define TEST_APP
#define TEST_SCRIPT
//  #define TEST_YOLO
//  #define TEST_VBO //  ����vboģʽ fail
//  #define TEST_EIGEN
//  #define TEST_QCOMPRESS //����qt�Դ���ѹ��

int main(int argc, char* argv[]) {
	//qDebug() << QStyleFactory::keys();
	//QApplication::setStyle(QStyleFactory::create("windowsvista"));
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QApplication::setOrganizationName(QObject::tr("�Ͼ���ѧ�������ѧ�뼼��ϵ"));
	QApplication::setApplicationVersion(QObject::tr("�汾-2019��11��"));
	QApplication::setApplicationName(QObject::tr("ChemInk ��ѧ��ʽ����д������Ӧ��ϵͳ"));
	QApplication app(argc, argv);
	QTranslator translator;
	if (translator.load(":/Resources/qt_zh_CN.qm"))
		app.installTranslator(&translator);
	else {
		return throwErrorBox("Error Message", "Fail to load(\":/Resources/qt_zh_CN.qm\")!");
	}
	if (-1 == _putenv(QString("BABEL_DATADIR=" + QApplication::applicationDirPath() + "/data").toStdString().c_str()))
		return throwErrorBox("Error Message", "Fail to set BABEL_DATADIR!");

#ifdef TEST_SCRIPT
	ScribbleArea w;
	w.resize(getDesktopSize() / 1.5);
	w.show();
#endif // TEST_SCRIPT
#ifdef TEST_APP
	MainWindow w;
	w.resize(getDesktopSize() / 1.5);
	w.show();
#elif defined(TEST_BABEL)
#pragma execution_character_set("GB2312")
	string input;
	string coor;
	ForceField ff;
	cout << "���룺";
	while (cin >> input) {
		coor = ff.getCoordinate(input.c_str(), "smiles", "pdb");
		cout << "���꣺\n" << coor << endl;
		cout << "������" << ff.getEnergy(coor.c_str(), "pdb") << endl;
		cout << "���룺";
	}
#elif defined(TEST_GL)
#pragma execution_character_set("GB2312")
	string input;
	string coor;
	ForceField ff;
	Molecule mol;
	char* format = "MOL2";
	input = "CC";
	cout << "����SMILES�ַ�����"; getline(cin, input);
	coor = ff.getCoordinate(input.c_str(), "SMILES", format);
	std::cout << "���꣺\n" << coor << endl;
	mol.load(coor.c_str(), format);
	mol.display();
	std::cout << "mol.atoms.size()=" << mol.getAtomSize() << endl;
	std::cout << "mol.bonds.size()=" << mol.getBondSize() << endl;
	std::cout << "������" << ff.getEnergy(coor.c_str(), format) << endl;
	GluMolWindow w;
	w.createMol3d(mol);
	w.resize(getDesktopSize() / 2.5);
	w.show();
	std::cout << "�����¼�ѭ��..." << endl;
	//}
#elif defined(TEST_VBO)
	//#pragma execution_character_set("GB2312")
	std::cout << "Hello, vbo!" << endl;


	std::cout << "Bye, vbo!" << endl;
#elif defined(TEST_EIGEN)
	Eigen::Vector3d v1(10, 0, 0), v2(0, 10, 0), v3(10, 10, 0);
	cout << v1.cross(v2);
	cout << v2.cross(v1) << endl;
	cout << sqrt(v3.dot(v3)) / sqrt(2) << endl;
	cout << v3.norm() / sqrt(2);
#endif
#ifdef TEST_QCOMPRESS
	QFile file("E:/chardetector-yolov3-tiny_226000.weights");
	if (file.exists()) {
		qDebug() << "ѹ��ǰ�ļ���С:" << file.size();
		bool ok = file.open(QIODevice::ReadOnly);
		if (ok) {
			QByteArray buffer = file.readAll();
			//ѹ��
			buffer = qCompress(buffer, 2);//ʹ��Ĭ�ϵ�zlibѹ��
			qDebug() << "ѹ�����ֽڴ�С:" << buffer.size();
			QFile writeFile("E:/TMP.zip");
			ok = writeFile.open(QIODevice::WriteOnly);
			if (ok) {
				//��ѹ��
				//buffer = qUncompress(buffer);
				qDebug() << "��ѹ�����ֽڴ�С:" << buffer.size();
				writeFile.write(buffer);
				qDebug() << "ѹ�����ļ���С:" << writeFile.size();
			}
		}
	}
	return 0;
#endif // TEST_QCOMPRESS
	return app.exec();
}
