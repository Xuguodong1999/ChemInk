#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include <set>

class UnrootedTree {
private:
	std::vector<std::vector<unsigned char>>* utree;
	std::vector<std::string> partSeq, allSeq;
	std::vector<int> son1, son2;
	int n;
	int nodeOfMaxSubTree;
	void dfsCollectSizeOfSon(int x, int father);
	void dfsGetSeq(int x, int father);
	void dfsGetSMILES(int x, int father);
public:
	UnrootedTree();
	~UnrootedTree();
	std::string getSeq(std::vector<std::vector<unsigned char>>& _utree);
	//  ��ȡ����SMILES��ʽ��ʾ�ķ���ʽ
	std::string getSMILES(std::vector<std::vector<unsigned char>>& _utree);
	std::vector<int>* getSubTreeSize(std::vector<std::vector<unsigned char>>& _utree);
	void clearSubTreeSize();
	void display();
	int getMaxSubTree();
};

class AlkaneTopo {
private:
	std::vector<std::vector<std::vector<unsigned char>>>* lastStructs;		//  i-1��̼���������ӷ�ʽ
	std::vector<std::vector<std::vector<unsigned char>>>* newStructs;		//  i��̼���������ӷ�ʽ
	std::vector<std::vector<unsigned char>> curStruct;				//  ��ǰ���ó����Ƚϵ�һ���ṹ ʹ���ڽӱ��ʾ�޸���
	//map<std::string, int> isomers;								//  ������������ map<������,������>
	//unordered_set<std::string> isomers;
	std::set<std::string> isomers;
	std::vector<int> isomerCounter;
	int numberOfCarbon;
	UnrootedTree utreeFunc;

public:
	AlkaneTopo();
	~AlkaneTopo();
	void getAlkaneTopo();
	void getAlkaneTopo(std::vector<std::string>& result, std::vector<int>& targetCarbonNum);
	bool setNumberOfCarbon(int n);									//  ���ò����̼ԭ����
	int getNumberOfCarbon()const;
	const std::vector<std::vector<unsigned char>>* getCurStruct();			//  ���ر�ʾ��ǰ���˵��ڽӱ��ַ
};

inline void getTargetSMILES(std::vector<std::string>& result, std::vector<int>& targetCarbonNum);
