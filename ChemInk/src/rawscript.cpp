#include "stdafx.h"
#include "rawscript.h"
using namespace std;
RawScript::RawScript() :panel(nullptr) {
	classifier.load(
		(QApplication::applicationDirPath() +
			"/data/densenet-chdsbw.json").toStdString().c_str(), 78);
	detector.load(
		(QApplication::applicationDirPath() +
			"/data/chardetector-yolov3-tiny.weights").toStdString().c_str(),
			(QApplication::applicationDirPath() +
				"/data/chardetector-yolov3-tiny.cfg").toStdString().c_str());
	//  opencv4.1.1��dnn������ػ��������أ����ڵ�һ�����е�ʱ�����
	detector.predictSingle(QImage(yoloBaseSize, QImage::Format::Format_RGB888));

}

RawScript::~RawScript() {

}
void  RawScript::setPanel(const QWidget* _panel) {
	panel = const_cast<QWidget*>(_panel);
}
void RawScript::setImage(const QPixmap* _pixmap) {
	pixmap = const_cast<QPixmap*>(_pixmap);
}
void RawScript::clear() {
	curStroke = PainterPath();
	script.clear();
}
void RawScript::pushStroke() {
	script.push_back(curStroke);
}
void RawScript::popStroke() {
	if (script.isEmpty())
		return;
	script.pop_back();
}
void RawScript::popStroke(const QPainterPath& rubberPath) {
	for (int i = 0; i < script.size(); i++) {
		if (script[i].intersects(rubberPath)) {
			script.removeAt(i);
			i--;
		}
	}
}
void RawScript::popStroke(const QPoint& innerPoint, QPoint scale) {
	for (int i = 0; i < script.size(); i++) {
		if (script[i].intersects(QRect(innerPoint - scale, innerPoint + scale))) {
			script.removeAt(i);
			i--;
		}
	}
}
const QList<RawScript::PainterPath>& RawScript::getScript() {
	return script;
}

RawScript::PainterPath::PainterPath() {

}
RawScript::PainterPath::PainterPath(const QPoint& start) :QPainterPath(start) {

}

static QImage yoloImg;
static vector<QImage> fdeepImgs;
static vector<vector<string>> srcWords;

//  ����l��m��r����ʾb��a����ࡢ���������Ҳ�
//  δ���/��ʱ����
char RawScript::diff(const QRectF& a, const QRectF& b) {
	//  TODO:����������
	qreal aw(a.width()), ah(a.height()),
		ax1(a.topLeft().x()), ay1(a.topLeft().y()),
		ax2(a.topRight().x()), ay2(a.topRight().y()),
		ax3(a.bottomLeft().x()), ay3(a.bottomLeft().y()),
		ax4(a.bottomRight().x()), ay4(a.bottomRight().y()),
		acentx(a.center().x()), acenty(a.center().y());
	qreal bw(b.width()), bh(b.height()),
		bx1(b.topLeft().x()), by1(b.topLeft().y()),
		bx2(b.topRight().x()), by2(b.topRight().y()),
		bx3(b.bottomLeft().x()), by3(b.bottomLeft().y()),
		bx4(b.bottomRight().x()), by4(b.bottomRight().y()),
		bcentx(b.center().x()), bcenty(b.center().y());
	/*�Һ������Ѳ����ӽ�xgboost����qaq*/
	//  ������ֵ
	qreal thresh(10);
	qreal thresh_2(2 * thresh);
	QRectF bigA(ax1 - thresh, ay1 - thresh, aw + thresh_2, ah + thresh_2);
	QRectF bigB(bx1 - thresh, by1 - thresh, bw + thresh_2, bh + thresh_2);
	if (bigA.contains(b) || bigB.contains(a))
		return 'm';
	//  ������ֵ
	qreal k = 0.1;
	//  ������ֵ
	qreal lineWidth = panel->height() / 3;
	//  �����ж�

	return 'l';
}

const std::vector<std::vector<std::string>>& RawScript::recognize() {
	results.clear();
	if (yoloImg.size() != panel->size()) {
		yoloImg = QImage(panel->size(), QImage::Format::Format_RGB888);
	}
	yoloImg.fill(Qt::white);
	QPainter painter(&yoloImg);
	painter.setPen(QPen(Qt::black, 4));
	for (auto& i : script) {
		painter.drawPath(i);
	}
	detector.predictSingle(yoloImg.scaled(yoloBaseSize, Qt::IgnoreAspectRatio));

	//  STEP1: ��ȡĿ����ı߿�
	/*���ﲻ�������͸��ʣ�ֻ����߿�*/
	QList<QRectF> objRects;
	double
		kw(1.0 * panel->width() / yoloBaseSize.width()),
		kh(1.0 * panel->height() / yoloBaseSize.height());
	for (const int i : detector.indices) {
		objRects.push_back(QRect(
			detector.boxes[i].x * kw - 4, detector.boxes[i].y * kh - 4,
			detector.boxes[i].width * kw + 8, detector.boxes[i].height * kh + 8
		));
	}
	qDebug() << "yolov3-tiny����߿������" << objRects.size();

	//  STEP2: ���û�б��������еıʻ���������ǣ��þ�����Ϊ���ǼӼ���
	/*���һ���ʻ��г�������K�����κ�һ���������Ϊ����ʻ�����©��*/
	vector<PainterPath*> leakedScriptIndices;
	for (auto& i : script) {
		int counter(0);
		for (auto& j : objRects) {
			for (int k = 0; k < i.elementCount(); k++) {
				if (j.contains(i.elementAt(k))) {
					counter++;
				}
			}
			if (counter > i.elementCount()* K_leak) {
				break;
			}
		}
		if (counter <= i.elementCount() * K_leak) {
			leakedScriptIndices.emplace_back(&i);
		}
	}
	for (size_t i = 0; i < leakedScriptIndices.size(); i++) {
		QRectF tmp = leakedScriptIndices.at(i)->boundingRect();

		objRects.push_back(QRectF(tmp.x() - 4, tmp.y() - 4, tmp.width() + 8, tmp.height() + 8));
	}
	//  STEP3: �þ���������������ıʼ�������û�г��ֺϲ��������⣬����У������������Ѽ���

	//  STEP4: ������С���������հ�����

	//  STEP5: �������е�����д���׼�������ύ������
	sort(objRects.begin(), objRects.end(),
		[=](const QRectF& a, const QRectF& b) {
			int centXa(a.center().x()), centYa(a.center().y()),
				centXb(b.center().x()), centYb(b.center().y());
			if (fabs(centYa - centYb) < panel->height() / 5) {
				return centXa < centXb;
			}
			else {
				return centYa < centYb;
			}
		}
	);
	fdeepImgs.resize(objRects.size(), QImage(fdeepBaseSize, QImage::Format::Format_RGB666));
	for (auto& i : fdeepImgs) {
		i.fill(Qt::white);
	}
	if (blankImg.size() != panel->size()) {
		blankImg = QPixmap(panel->size());
	}
	for (size_t i = 0; i < fdeepImgs.size(); i++) {
		QPainter painter(&fdeepImgs[i]);
		QPainter rpainter(&blankImg);
		rpainter.setPen(QPen(Qt::black, 6));
		blankImg.fill(Qt::white);
		for (auto& j : script) {
			int counter = 0;
			for (int k = 0; k < j.elementCount(); k++) {
				if (objRects.at(i).contains(j.elementAt(k))) {
					counter++;
				}
			}
			if (counter > j.elementCount() * 0.3) {
				rpainter.drawPath(j);
			}
		}
		if (objRects.at(i).width() > objRects.at(i).height()) {
			double k = 1.0 / objRects.at(i).width() * fdeepBaseSize.width();
			painter.drawPixmap(//���������
				QRect(0, (-objRects.at(i).height() * k + fdeepBaseSize.height()) / 2,
					fdeepBaseSize.width(), objRects.at(i).height() * k), //  target rect
				blankImg,
				objRects.at(i));//  source rect
		}
		else {//�������㳤
			double k = 1.0 / objRects.at(i).height() * fdeepBaseSize.height();
			painter.drawPixmap(//���������
				QRect((-objRects.at(i).width() * k + fdeepBaseSize.width()) / 2, 0,
					objRects.at(i).width() * k, fdeepBaseSize.height()), //  target rect
				blankImg,
				objRects.at(i));//  source rect
		}
	}
	classifier.predict(fdeepImgs);

	//  STEP6: ��������Ԥ�⵽��ǰtopk����ύ�����ֵ����������ģ��
	//indices.at(i)������һ��ͼƬ����������ĸ�����������
	srcWords.resize(classifier.indices.size());
	int index;
	for (size_t i = 0; i < classifier.indices.size(); i++) {
		for (auto& j : classifier.indices.at(i)) {//  j���������
			if (classifier.confidences[i][j] > K_allowIn) {
				index = corrector.getCnnIndex(j);
				if (index < 0) {
					continue;
				}
				for (auto& k : SpellCorrector::similarWords.at(index)) {
					srcWords.at(i).emplace_back(k);
				}
				srcWords.at(i).emplace_back("");
			}
			else {
				break;
			}
		}
	}
	auto it = srcWords.begin();
	while (it != srcWords.end()) {
		if (it->empty()) {
			it = srcWords.erase(it);
		}
		else {
			it++;
		}
	}
	results.resize(1);
	//qDebug() << "srcWords.size() = " << srcWords.size();
	//for (auto& i : srcWords) {
	//	cout << "***" << endl;
	//	for (auto& j : i) {
	//		qDebug() << j.c_str();
	//	}
	//	cout << "---" << endl;
	//}
	corrector.getBestResult(srcWords, results.at(0));
	results.resize(srcWords.size() + 1);
	for (size_t i = 0; i < srcWords.size(); i++) {
		for (auto& j : srcWords.at(i)) {
			results[i + 1].emplace_back(j);
		}
	}
	srcWords.clear();
	//for (auto& i : results) {
	//	cout << "***" << endl;
	//	for (auto& j : i) {
	//		qDebug() << j.c_str();
	//	}
	//}
	return results;
}
