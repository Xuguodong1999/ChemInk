#include "stdafx.h"
#include "mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), scribbleView(nullptr), curDocWidget(nullptr)
{
	ui.setupUi(this);

	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	setFocus();

	muldocwidget = new MulDocWidget(this);
	setCentralWidget(muldocwidget);

	progressbar = new QProgressBar(statusBar());
	progressbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	progressbar->hide();
	statusBar()->addPermanentWidget(progressbar);

	previewarea = new PreviewScrollArea(this);
	ui.dockViewWidget->setWidget(previewarea);

	filedialog = new QFileDialog(this);

	//label->setFrameStyle(QFrame::Box | QFrame::Sunken);
	setupConnection();
	newDrawDoc("δ����.xml");
	newDrawDoc("���ĵ�����.xml");
}
MainWindow::~MainWindow() {

}
void MainWindow::setupConnection() {
	cloudBtn = new QToolButton(statusBar());
	cloudBtn->setText("�����Ʒ���");
	notifyBtn = new QToolButton(statusBar());
	notifyBtn->setText("֪ͨ");
	statusBar()->addPermanentWidget(cloudBtn);
	statusBar()->addPermanentWidget(notifyBtn);
	connect(notifyBtn, &QToolButton::clicked, this, &MainWindow::showNotification);
	connect(cloudBtn, &QToolButton::clicked, this, &MainWindow::showCloudService);

	connect(ui.aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(ui.aboutMeAct, &QAction::triggered, this, &MainWindow::showAboutMe);

	connect(ui.newDrawAct, &QAction::triggered, this, [=]() {
		QString saveName = filedialog->getSaveFileName(
			nullptr, "", QApplication::applicationDirPath(), QString("*.xml")
		);
		if (QFileInfo(saveName).suffix().isEmpty()) {
			saveName += ".xml";
		}
		newDrawDoc(QFileInfo(saveName).fileName());
		}
	);
}

void MainWindow::syncStatusPos(const QPoint& _pos) {
	statusBar()->showMessage(
		QString("ģʽ��%1���������꣺(%2,%3)").arg(modeHint).arg(_pos.x()).arg(_pos.y())
	);
}

void MainWindow::showAboutMe() {
	QMessageBox messagebox(QMessageBox::NoIcon, "һ��Ŭ�����빤ҵ��׼��ѧ����Ӧ��", "���Դ�Ӧ�ü����Ž��з�������\n����ǧ�š�");
	messagebox.setModal(true);
	messagebox.exec();
}

void MainWindow::showNotification() {

}

//  ʵ�ּ������̵߳ķ��룬�����˼���ʱ��ǰ�˿�������
//  ���к�ʱ�ɸеĺ�����Ӧģ��������ʽִ��
void MainWindow::showCloudService() {
	if (locker) {
		throwErrorBox("��ͻ", "������δ���");
		return;
	}
	else
		locker = true;
	initProgressBar();
	//  ��ʱ����Ӧ�����߳�ִ��
	std::thread* threadContainer = new std::thread([=]() {
		//  ��ʱ���ؿ�ʼ
		for (int i = 0; i < 1000; i++) {
			//  Qt�Ĵ���ֻ�������̱߳�����/���£�ǿ�ưѺ��������¼�ѭ��
			//  �������̵߳��ȵ�ʱ�򣬽�����ºͼ��㽻�潫����
			QMetaObject::invokeMethod(this, "setProgressBar", Q_ARG(double, i / 10.0));
			_sleep(1);
		}
		QMetaObject::invokeMethod(this, "killProgressBar");
		//  ��ʱ���ؽ���
		}
	);
	threadContainer->detach();//ת��̨�̣߳������п⸺�����

}

void MainWindow::initProgressBar() {
	progressbar->setValue(0);
	progressbar->setFormat(QString("%1%").arg(QString::number(0, 'f', 2)));
	progressbar->show();
	statusBar()->showMessage("����");
}

void MainWindow::setProgressBar(double percentx100) {
	if (percentx100 > -1) {
		progressbar->setValue(percentx100);
		progressbar->setFormat(QString("%1%").arg(QString::number(percentx100, 'f', 2)));
	}
	else {
		progressbar->setMaximum(0);
		progressbar->setMinimum(0);
	}
}

void MainWindow::killProgressBar() {
	progressbar->setValue(100);
	progressbar->setFormat(QString("%1%").arg(QString::number(100, 'f', 2)));
	progressbar->hide();
	statusBar()->showMessage("����");
	locker = false;
}

void MainWindow::setCurDocWidget(DocWidget* window) {
	curDocWidget->setWidget(nullptr);
	curDocWidget = window;
	scribbleView->myScene = sceneMap[window->getId()];
	scribbleView->setScene(scribbleView->myScene);
	curDocWidget->setWidget(scribbleView);
}

int MainWindow::sceneId = (numeric_limits<int>::min)();

bool MainWindow::locker = false;

void MainWindow::newDrawDoc(const QString& filename) {
	if (curDocWidget != nullptr)
		curDocWidget->setWidget(nullptr);
	curDocWidget = new DocWidget(sceneId, muldocwidget);
	//  TOASK:��һ�����ĵ������ˣ��������ӻᱻ�����𣿱�˭����
	connect(curDocWidget, &DocWidget::getFocus, this, &MainWindow::setCurDocWidget);

	ScribbleScene* newScene = new ScribbleScene(this);
	sceneMap.insert(sceneId++, newScene);

	if (scribbleView == nullptr) {
		scribbleView = new ScribbleView(newScene);
		connect(scribbleView, &ScribbleView::sendMousePos, this, &MainWindow::syncStatusPos);
		connect(ui.editPelAct, &QAction::triggered, scribbleView, [=]() {
			scribbleView->setMode(ScribbleScene::Mode_Drag_Pel);
			scribbleView->setCursor(Qt::ArrowCursor);
			}
		);
		connect(ui.drawPathAct, &QAction::triggered, scribbleView, [=]() {
			scribbleView->setMode(ScribbleScene::Mode_Pen);
			scribbleView->setCursor(Qt::ArrowCursor);
			}
		);
		connect(ui.editSceneAct, &QAction::triggered, scribbleView,
			[=]() {
				scribbleView->setMode(ScribbleScene::Mode_Drag_Scene);
				scribbleView->setCursor(Qt::OpenHandCursor);
			}
		);
	}
	else {
		scribbleView->setScene(newScene);
		scribbleView->myScene = newScene;
	}
	curDocWidget->setWidget(scribbleView);
	curDocWidget->setWindowTitle(filename);
}

void MainWindow::closeEvent(QCloseEvent* event) {
	int closeBox = QMessageBox::question(
		this, "������", "��ȷ��Ҫ�˳���"
	);
	if (closeBox == QMessageBox::Yes) {
		event->accept();
	}
	else {
		event->ignore();
	}
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
	autoChangeFont();
}

void MainWindow::focusInEvent(QFocusEvent* event) {
	//setWindowOpacity(1);
	QMainWindow::focusInEvent(event);
}
void MainWindow::focusOutEvent(QFocusEvent* event) {
	//setWindowOpacity(0.9);
	QMainWindow::focusOutEvent(event);
}
void MainWindow::autoChangeFont() {
	int w = width();
	int pointSize(12);
	if (w < 200) {
		pointSize = 8;
	}
	else if (w < 400) {
		pointSize = 9;
	}
	else if (w < 600) {
		pointSize = 10;
	}
	else if (w < 800) {
		pointSize = 11;
	}
	QFont font("Arial", pointSize, QFont::Bold);
	//menuBar()->setFont(font);
	//statusBar()->setFont(font);
	//for (auto& i : actionMap) 
	//	i->setFont(font);
	qApp->setFont(font);
}