#include "alkanetopo.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;


void UnrootedTree::dfsCollectSizeOfSon(int x, int father) {		//  ��ȡ������С ������
	son1[x] = 1, son2[x] = 0;
	for (size_t i = 0; i < utree->at(x).size(); i++) {
		int p = utree->at(x).at(i);
		if (p == father)
			continue;
		dfsCollectSizeOfSon(p, x);
		son1[x] += son1[p];
		son2[x] = max(son2[x], son1[p]);
	}
	son2[x] = max(son2[x], n - son1[x]);
	nodeOfMaxSubTree = max(son2[x], nodeOfMaxSubTree);
}

void UnrootedTree::dfsGetSeq(int x, int father) {
	allSeq[x] = "(";
	for (size_t i = 0; i < utree->at(x).size(); i++) {
		int p = utree->at(x).at(i);
		if (p != father)
			dfsGetSeq(p, x);
	}
	int now = 0;
	for (size_t i = 0; i < utree->at(x).size(); i++) {
		int p = utree->at(x).at(i);
		if (p != father)
			partSeq[now++] = allSeq[p];
	}
	sort(partSeq.begin(), partSeq.begin() + now);
	for (int i = 0; i < now; i++)
		allSeq[x] += partSeq[i];
	allSeq[x] += ")";
}

UnrootedTree::UnrootedTree() :utree(nullptr), n(0), nodeOfMaxSubTree(-1) { ; }

UnrootedTree::~UnrootedTree() {
	utree = nullptr;
	son1.clear();		son2.clear();
	partSeq.clear();	allSeq.clear();
}

string UnrootedTree::getSeq(vector<vector<unsigned char>>& _utree) {	//  ��ȡ��������
	utree = &_utree;
	n = utree->size();							//  ��̼ԭ������һ�� 0,1-n
	son1.resize(n, 0);			son2.resize(n, 0);
	partSeq.resize(n, "");		allSeq.resize(n, "");
	nodeOfMaxSubTree = -1;						//  ��������Ľڵ���
	dfsCollectSizeOfSon(1, 0);
	string finalSeq = "";
	for (int i = 1; i <= n; i++) {				//  ������������
		if (son2[i] == nodeOfMaxSubTree) {		//  ������������Ľڵ���
			dfsGetSeq(i, 0);
			if (allSeq[i] > finalSeq)
				finalSeq = allSeq[i];
		}
	}
	utree = nullptr;
	son1.clear();		son2.clear();
	partSeq.clear();	allSeq.clear();
	return finalSeq;
}

int UnrootedTree::getMaxSubTree() {
	return nodeOfMaxSubTree;
}

vector<int>* UnrootedTree::getSubTreeSize(vector<vector<unsigned char>>& _utree) {
	utree = &_utree;
	n = utree->size();							//  ��̼ԭ������һ�� 0,1-n
	son1.resize(n, 0);			son2.resize(n, 0);
	partSeq.resize(n, "");		allSeq.resize(n, "");
	nodeOfMaxSubTree = -1;						//  ��������Ľڵ���
	dfsCollectSizeOfSon(1, 0);
	return &son2;
}

void UnrootedTree::clearSubTreeSize() {
	son1.clear();
	son2.clear();
	utree = nullptr;
}

void UnrootedTree::display() {
	if (utree == nullptr) {
		cout << "δ��ʼ���ڽӱ��޷���ӡ" << endl;
		return;
	}
	for (size_t i = 0; i < utree->size(); i++) {
		cout << i << " --> ";
		for (size_t j = 0; j < utree->at(i).size(); j++) {
			cout << utree->at(i).at(j) << ", ";
		}
		cout << endl;
	}
}

AlkaneTopo::AlkaneTopo() :lastStructs(nullptr), newStructs(nullptr), numberOfCarbon(1) {
	curStruct.clear();
	isomers.clear();
	isomerCounter.resize(2, 0);
	isomerCounter[1] = 1;
}

AlkaneTopo::~AlkaneTopo() {
	if (lastStructs != nullptr) {
		delete lastStructs;
		lastStructs = nullptr;
	}
	if (newStructs != nullptr) {
		delete newStructs;
		newStructs = nullptr;
	}
	curStruct.clear();
	isomers.clear();
	isomerCounter.clear();
}
static inline bool hasTargetNum(vector<int>& targetNum, int a) {
	for (int i : targetNum) {
		if (a == i)
			return true;
	}
	return false;
}
void AlkaneTopo::getAlkaneTopo() {
	if (numberOfCarbon == 1) {										//  һ�����
		newStructs = new vector<vector<vector<unsigned char>>>();
		newStructs->resize(2);										//  ���ؿ��ڽӱ�
		isomerCounter[1] = 1;
		return;
	}
	else if (numberOfCarbon == 2) {									//  �������
		newStructs = new vector<vector<vector<unsigned char>>>();
		newStructs->resize(1);
		newStructs->at(0).resize(3);								//  C2�ĵ�һ��Ҳ��Ψһһ����������
		newStructs->at(0).at(1).push_back(2);						//  C1-C2
		newStructs->at(0).at(2).push_back(1);						//  C2-C1
		isomerCounter[2] = 1;
		return;
	}
	//  ���������Ͻ�㣬��������
	lastStructs = new vector<vector<vector<unsigned char>>>();			//  Ϊ��¼����i-1��̼�Ľṹ���ٿռ�
	lastStructs->resize(1);										//  C2ֻ��һ�����˽ṹ ̼ԭ�ӱ�Ŵ�1��ʼ
	lastStructs->at(0).resize(3);								//  C2�ĵ�һ��Ҳ��Ψһһ����������
	lastStructs->at(0).at(1).push_back(2);						//  C1-C2
	lastStructs->at(0).at(2).push_back(1);						//  C2-C1
	string tmp;
	clock_t start, end;
	for (int i = 3; i <= numberOfCarbon; i++) {
		start = clock();
		newStructs = new vector<vector<vector<unsigned char>>>();			//  Ϊ��¼����i��̼���½ṹ���ٿռ�										
		for (size_t j = 0; j < lastStructs->size(); j++) {		//  ����i-1��̼���������ӷ�ʽ
			for (int k = 1; k <= i - 1; k++) {					//  �������˽ṹj�ϵ�����̼ԭ��
				if (lastStructs->at(j).at(k).size() > 3)		//  һ��̼�������4��̼
					continue;
				curStruct.clear();
				curStruct = lastStructs->at(j);					//  ����ԭ���Ľṹ
				curStruct.resize(i + 1);
				curStruct.at(k).push_back(i);					//  ����ԭ������k��̼
				curStruct.at(i).push_back(k);
				tmp = utreeFunc.getSeq(curStruct);				//  ��ȡcurStruct�޸�������������
				//if (isomers.find(tmp) == isomers.end()) {		//  ��һ��û�б���¼���Ľṹ ���������½ṹ��
				//	isomerCounter.at(i)++;						//  i��̼�ǹ�ѧͬ���칹��������һ
				//	isomers[tmp] = newStructs->size();			//  �ӽ��½ṹ�б�
				//	newStructs->push_back(curStruct);
				//}
				if (isomers.insert(tmp).second == true) {
					isomerCounter.at(i)++;
					newStructs->push_back(curStruct);
					cout << utreeFunc.getSMILES(curStruct) << endl;
				}
			}
		}
		cout << "i=" << i << ", count=" << isomerCounter.at(i) << endl;
		end = clock();
		double endtime = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "�����������˽ṹ��ʱ:" << endtime << "��" << endl;		//  sΪ��λ
		start = end;
		isomers.clear();										//  ���i��̼�����кϷ���������
		delete lastStructs;										//  �黹�ɽṹռ�õĿռ�
		lastStructs = newStructs;								//  ��ָ��ת��
		newStructs = nullptr;
	}
}

void AlkaneTopo::getAlkaneTopo(vector<string>& result, vector<int>& targetCarbonNum) {
	setNumberOfCarbon(targetCarbonNum.back());
	if (numberOfCarbon == 1) {										//  һ�����
		newStructs = new vector<vector<vector<unsigned char>>>();
		newStructs->resize(2);										//  ���ؿ��ڽӱ�
		isomerCounter[1] = 1;
		result.push_back("C");
		return;
	}
	else if (numberOfCarbon == 2) {									//  �������
		newStructs = new vector<vector<vector<unsigned char>>>();
		newStructs->resize(1);
		newStructs->at(0).resize(3);								//  C2�ĵ�һ��Ҳ��Ψһһ����������
		newStructs->at(0).at(1).push_back(2);						//  C1-C2
		newStructs->at(0).at(2).push_back(1);						//  C2-C1
		isomerCounter[2] = 1;
		return;
	}
	if (targetCarbonNum.at(0) == 1) {//  ����������Ȼ����
		result.push_back("C");
	}
	if (targetCarbonNum.at(0) == 2 ||
		(targetCarbonNum.size() > 1 && targetCarbonNum.at(1) == 2)) {
		result.push_back("C(C)");
	}
	//  ���������Ͻ�㣬��������
	lastStructs = new vector<vector<vector<unsigned char>>>();			//  Ϊ��¼����i-1��̼�Ľṹ���ٿռ�
	lastStructs->resize(1);										//  C2ֻ��һ�����˽ṹ ̼ԭ�ӱ�Ŵ�1��ʼ
	lastStructs->at(0).resize(3);								//  C2�ĵ�һ��Ҳ��Ψһһ����������
	lastStructs->at(0).at(1).push_back(2);						//  C1-C2
	lastStructs->at(0).at(2).push_back(1);						//  C2-C1
	string tmp;
	bool allowAdd = false;
	for (int i = 3; i <= numberOfCarbon; i++) {
		allowAdd = hasTargetNum(targetCarbonNum, i);
		newStructs = new vector<vector<vector<unsigned char>>>();			//  Ϊ��¼����i��̼���½ṹ���ٿռ�										
		int cc = 0;
		for (size_t j = 0; j < lastStructs->size(); j++) {		//  ����i-1��̼���������ӷ�ʽ
			for (int k = 1; k <= i - 1; k++) {					//  �������˽ṹj�ϵ�����̼ԭ��
				if (lastStructs->at(j).at(k).size() > 3)		//  һ��̼�������4��̼
					continue;
				curStruct.clear();
				curStruct = lastStructs->at(j);					//  ����ԭ���Ľṹ
				curStruct.resize(i + 1);
				curStruct.at(k).push_back(i);					//  ����ԭ������k��̼
				curStruct.at(i).push_back(k);
				tmp = utreeFunc.getSeq(curStruct);				//  ��ȡcurStruct�޸�������������
				if (isomers.insert(tmp).second == true) {
					cc++;
					if (cc > 2000)
						goto L;
					isomerCounter.at(i)++;
					newStructs->push_back(curStruct);
					if (allowAdd)
						result.push_back(utreeFunc.getSMILES(curStruct));
				}
			}
		}
	L:;
		isomers.clear();										//  ���i��̼�����кϷ���������
		delete lastStructs;										//  �黹�ɽṹռ�õĿռ�
		lastStructs = newStructs;								//  ��ָ��ת��
		newStructs = nullptr;
	}
}


bool AlkaneTopo::setNumberOfCarbon(int n) {
	if (n < 3 || n > 2500)
		return false;
	numberOfCarbon = n;
	isomerCounter.resize(n + 1, 0);
	isomerCounter[1] = isomerCounter[2] = 1;
	return true;
}

int AlkaneTopo::getNumberOfCarbon() const{
	return numberOfCarbon;
}

const vector<vector<unsigned char>>* AlkaneTopo::getCurStruct() {
	return &curStruct;
}

void UnrootedTree::dfsGetSMILES(int x, int father) {
	allSeq[x] = "(C";
	for (size_t i = 0; i < utree->at(x).size(); i++) {
		int p = utree->at(x).at(i);
		if (p != father)
			dfsGetSMILES(p, x);
	}
	int now = 0;
	for (size_t i = 0; i < utree->at(x).size(); i++) {
		int p = utree->at(x).at(i);
		if (p != father)
			partSeq[now++] = allSeq[p];
	}
	sort(partSeq.begin(), partSeq.begin() + now);
	for (int i = 0; i < now; i++) {
		allSeq[x] += partSeq[i];
	}
	allSeq[x] += ")";
}

string UnrootedTree::getSMILES(vector<vector<unsigned char>>& _utree) {	//  ��ȡ��������
	utree = &_utree;
	n = utree->size();							//  ��̼ԭ������һ�� 0,1-n
	son1.resize(n, 0);			son2.resize(n, 0);
	partSeq.resize(n, "");		allSeq.resize(n, "");
	nodeOfMaxSubTree = -1;						//  ��������Ľڵ���
	dfsCollectSizeOfSon(1, 0);
	string finalSeq = "";
	for (int i = 1; i <= n; i++) {				//  ������������
		if (son2[i] == nodeOfMaxSubTree) {		//  ������������Ľڵ���
			dfsGetSMILES(i, 0);
			if (allSeq[i] > finalSeq)
				finalSeq = allSeq[i];
		}
	}
	utree = nullptr;
	son1.clear();		son2.clear();
	partSeq.clear();	allSeq.clear();
	finalSeq.pop_back();
	finalSeq.erase(finalSeq.begin());
	return finalSeq;
}

//  ��������������Ҫ�������̼ԭ������ͬ���칹���SMILES�ṹʽ������ַ�������
inline void getTargetSMILES(vector<string>& result, vector<int>& targetCarbonNum) {
	int maxC = std::numeric_limits<int>::min(), minC = std::numeric_limits<int>::max(), tmp;
	//  Ŀ������ȥ��
	sort(targetCarbonNum.begin(), targetCarbonNum.end());
	for (size_t i = 0; i < targetCarbonNum.size() - 1; i++) {
		tmp = targetCarbonNum.at(i);
		for (size_t j = i + 1; j < targetCarbonNum.size(); j++) {
			if (tmp == targetCarbonNum.at(j))
				targetCarbonNum.erase(targetCarbonNum.begin() + j);
			else {
				break;
			}
		}
	}
	for (size_t i = 0; i < targetCarbonNum.size(); i++) {
		maxC = targetCarbonNum.at(i) > maxC ? targetCarbonNum.at(i) : maxC;
		minC = targetCarbonNum.at(i) < minC ? targetCarbonNum.at(i) : minC;
	}
	result.clear();
	if (minC <= 0 || maxC >= 20) {
		cout << "Ŀ��̼ԭ�����������Ϸ��Լ���������[1,20]" << endl;
		return;
	}

}
