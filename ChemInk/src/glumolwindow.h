#pragma once

#include "molecule.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGLWidget>
#include <QPoint>
#include <Eigen/Core>

class GLUquadric;
//  ��Ⱦһ��ģ����Ҫ������
//  Ϊ��ͬ��װ�̶ȵ���άͼ�ο����ר�ŵ����ݽṹ
class GluMolecule {
public:
	GluMolecule(const Molecule& molecule);
	//  �������ꡢ��뾶��������ɫ
	std::vector<std::tuple<Eigen::Vector3d, double, float*>> nodes;
	Eigen::Vector3d& getSphereCenter(int i);
	double& getSphereRadius(int i);
	float*& getSphereColor(int i);
	//  Բ��ָ���Ĭ��ָ��ķ���������ת�Ƕȣ����ȣ�����ԭ�ӱ��
	//  ΪʲôҪ���򣿵��õ�glu��άͼԪ����Ĭ�Ϸ��򡪡�Z��������
	//  ��Ϊ����glu��Ĭ��ͼԪ����Ч�ʺܵ������Կռ任ʱ��
	std::vector<std::tuple<Eigen::Vector3d, double, double, int>> links;
	Eigen::Vector3d& getCylinderDirection(int i);
	double& getCylinderRotateAngle(int i);
	double& getCylinderLength(int i);
	int& getCylinderAtom(int i);
};
//  ֻ������Ⱦ���������ϲ��view�����ӽǱ任��view����仯
class GluMolWindow :public QGLWidget {
	Q_OBJECT
public:
	GluMolWindow(QWidget* parent = nullptr);
	~GluMolWindow()override;
	void createMol3d(const Molecule& _molecule);
private:
	GLUquadric* quadric;
	GluMolecule* molecule;
	double rX, rY, dZ;
	QPoint lastPoint;
	void zoomIn();
	void zoomOut();
protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	//void keyPressEvent(QKeyEvent* event)override;
	void wheelEvent(QWheelEvent* event)override;
	//void closeEvent(QCloseEvent* event)override;
	void initializeGL()override;
	void paintGL()override;
	void resizeGL(int width, int height)override;
};
