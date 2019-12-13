#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

class SpellCorrector {
public:
	SpellCorrector();
	~SpellCorrector();
	//  �˹�����ַ�����
	enum LETTERTYPE {
		DIGIT,		//  ����
		CAPITAL,	//  ��д��ĸ
		LITTLE,		//  Сд��ĸ
		INFO,		//  ע�ͷ������¼�ͷ
		EXPLICTCUT,	//  �ָ���+��=
		LB,			//  ������
		RB,			//  ������
		NONE,		//  �������ַ�
	};

	static std::string getChemAscii(const std::string& _src);
	int getCnnIndex(int outIndex);
	int getYoloIndex(int outIndex);
	static const std::vector<std::vector<std::string>> similarWords;
	std::vector<std::string> getResult(const std::vector<std::vector<std::string>>& _src);
	void getBestResult(const std::vector<std::vector<std::string>>& _src, std::vector<std::string>& result);
	static int getWordType(const std::string& _word);
private:
	static std::map<std::string, std::string> unicode2chemAsciiMap;
	//  static std::map<std::string, int> chemAscii2typeMap;
	static std::vector<std::string> validWords;
	std::string getValidWord(const std::vector<std::vector<std::string>>& _src,
		int start, int end);
};
