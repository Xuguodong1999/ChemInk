#pragma once
#include <QRunnable>

enum WorkIndex { IDLE, LOAD, PREDICT };

class ThreadSupport :public QRunnable {
public:
	ThreadSupport();
	~ThreadSupport();
	//  ���̣������������������ù������ء��̳߳ص��á���������Ƿ����
	bool isWorking();//  ��Ϊͬһʱ�����ִ��һ������
	void setWorkIndex(WorkIndex _index);//  ӳ�䵽���ܺ���
	WorkIndex getWorkIndex();
	void run()override;//  ���ô��ν�ȥ����������������������
private:
	WorkIndex index;
	bool flag;
protected:// �߳�����Ҫ����֧��������ģ�ͺͷ��Ӷ���ѧģ��
	virtual void load() = 0;
	virtual void predict() = 0;

//	class ThreadSupportInterface {
//	protected:
//		virtual void load() = 0;
//		virtual void predict() = 0;
//	};
//private:
//	ThreadSupportInterface* tsinterface;
//public:
//	void regist(ThreadSupportInterface* _tsinterface) {
//		tsinterface = _tsinterface;
//	}
//	void run()override {
//		if (tsinterface) {
//			//TODO: do sth
//		}
//	}
};

