#include "stdafx.h"
#include "spellcorrector.h"
#include <iostream>
#include <QFile>
using namespace std;

vector<string> SpellCorrector::validWords;

SpellCorrector::SpellCorrector() {
	validWords.clear();
	QFile freader(":/Resources/dictionary.txt");
	freader.open(QIODevice::ReadOnly | QIODevice::Text);
	if (freader.isOpen()) {
		while (!freader.atEnd()) {
			validWords.push_back(freader.readLine().toStdString());
			validWords.back().pop_back();
		}
	}
	else {
		throwErrorBox("��Դ�ļ��򿪴���", "�޷����ֵ��ļ�");
	}
	freader.close();
	//for (auto& i : validWords) {
	//	cout << i << endl;
	//}
}

SpellCorrector::~SpellCorrector() {

}

int SpellCorrector::getCnnIndex(int outIndex) {
	switch (outIndex) {
	case  0:case  26:// 3 �� (�� ��)
		return 49;
	case  1:
		return 50;
	case  2:
		return 51;
	case  3:
		return 75;
	case  4:
		return 52;
	case  5:
		return 21;
	case  6:
		return 53;
	case  7:
		return 18;
	case  8:
		return 54;
	case  9:
		return 55;
	case  10:case 31:// #��H
		return 56;
	case  11:
		return 57;
	case  12:
		return 58;
	case  13:
		return 59;
	case  14:
		return 60;
	case  15:
		return 61;
	case  16:
		return 19;
	case  17:
		return 14;
	case  18:
		return 29;
	case  19:
		return 5;
	case  20:
		return -1;
	case  21:
		return 4;
	case  22:
		return 62;
	case  23:
		return 34;
	case  24:
		return 42;
	case  25:
		return 63;
		//case  26:
		//	return 20;
	case  27:
		return 26;
	case  28:
		return 71;
	case  29:
		return 17;
	case  30:
		return 64;
		//case  31:
		//	return 36;
	case  32:
		return 65;
	case  33:
		return 66;
	case  34:
		return 67;
	case  35:
		return 7;
	case  36:
		return 0;
	case  37:
		return 72;
	case  38:
		return 45;
	case  39:
		return 40;
	case  40:
		return 23;
	case  41:
		return 25;
	case  42:
		return 43;
	case  43:
		return 47;
	case  44:
		return 13;
	case  45:
		return 24;
	case  46:
		return 33;
	case  47:
		return 38;
	case  48:
		return 27;
	case  49:
		return 35;
	case  50:
		return 30;
	case  51:
		return 68;
	case  52:case  53:case  65:case  66:// ����O���ҡ���
		return 3;
		//case  53:
		//	return 74;
	case  54:
		return 8;
	case  55:
		return 15;
	case  56:
		return 32;
	case  57:
		return 6;
	case  58:
		return 46;
	case  59:
		return 39;
	case  60:
		return 37;
	case  61:
		return 69;
	case  62:
		return 44;
	case  63:
		return 48;
	case  64:
		return 2;
		//case  65:
		//	return 14;
		//case  66:
		//	return 22;
	case  67:
		return 70;
	case  68:
		return 9;
	case  69:
		return 41;
	case  70:
		return 12;
	case  71:
		return 10;
	case  72:
		return 28;
	case  73:
		return -2;
	case  74:
		return 11;
	case  75:
		return 31;
	case  76:
		return 16;
	case  77:
		return 1;
	default:
		return -3;
	}
}

int SpellCorrector::getYoloIndex(int outIndex) {
	switch (outIndex) {
	default:
		return outIndex;
	}
}

string SpellCorrector::getChemAscii(const std::string& _src) {
	map<string, string>::iterator iter = unicode2chemAsciiMap.find(_src);
	if (iter != unicode2chemAsciiMap.end()) {
		return iter->second;
	}
	else {
		return "[]";
	}
}

map<std::string, std::string> SpellCorrector::unicode2chemAsciiMap = {
	{"��","/"},
	{"��","=/="},
	{"��","<="},
	{"��",">="},
	{"��","$"},
	{"��","->"},
	{"��","<-"},
	{"��","(g)"},
	{"��","(s)"},
	{"��","#"},
	{"��","RMB"},
	{"��","%"},
	{"��","&"},
	{"��","("},
	{"��",")"},
	{"��","*"},
	{"��","+"},
	{"��","-"},
	{"��","0"},
	{"��","1"},
	{"��","2"},
	{"��","3"},
	{"��","4"},
	{"��","5"},
	{"��","6"},
	{"��","7"},
	{"��","8"},
	{"��","9"},
	{"��","<"},
	{"��","="},
	{"��",">"},
	{"��","?"},
	{"��","@"},
	{"��","A"},
	{"��","B"},
	{"��","C"},
	{"��","D"},
	{"��","E"},
	{"��","F"},
	{"��","C"},
	{"��","H"},
	{"��","I"},
	{"��","J"},
	{"��","K"},
	{"��","L"},
	{"��","M"},
	{"��","N"},
	{"��","O"},
	{"��","P"},
	{"��","O"},
	{"��","R"},
	{"��","S"},
	{"��","T"},
	{"��","U"},
	{"��","V"},
	{"��","W"},
	{"��","X"},
	{"��","Y"},
	{"��","Z"},
	{"��","["},
	{"��","]"},
	{"��","a"},
	{"��","b"},
	{"��","c"},
	{"��","d"},
	{"��","e"},
	{"��","f"},
	{"��","g"},
	{"��","h"},
	{"��","i"},
	{"��","j"},
	{"��","k"},
	{"��","l"},
	{"��","m"},
	{"��","n"},
	{"��","o"},
	{"��","p"},
	{"��","q"},
	{"��","r"},
	{"��","s"},
	{"��","t"},
	{"��","u"},
	{"��","v"},
	{"��","w"},
	{"��","x"},
	{"��","y"},
	{"��","z"},
	{"��","{"},
	{"��","}"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","alpha"},
	{"��","beta"},
	{"��","..."},
	{"��","8"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","lambda"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","O"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","nor"}
};

const vector<vector<std::string>> SpellCorrector::similarWords = {
	//  ���Ӳ��� ����Ҫ��
	{"��","��","��"},
	{"��","��","��" },
	{"��","��","��"},
	{"��","��","��"},
	{"��","��"},
	{"��","��"},
	{"��","��","��"},
	{"��","��"},
	{"��","��","��"},
	{"��","��","��"},
	{"��","��","��"},
	{"��","��"},
	{"��","��"},
	{"��","��"},
	{"��","��","��"},
	{"��","��"},
	{"��","��","��"},
	{"��","��","��","��"},
	{"��","��"},
	{"��","��"},
	{"��","��"},
	{"��","��","��","��"},
	//  �򵥲���
	{"��"}, { "��" }, { "��" }, { "��" }, { "��" }, { "��" }, { "��" },
	{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},
	{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},
	{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"}, {"��"},{"��"},{"��"},
	{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},
	{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��","��"}
};
/*��*\��Ϣ��ǣ������֣���*\Сд��ĸ��
��*\��Ϣ��ǣ���Сд��ĸ������
��*\��Ϣ��ǣ�����д��ĸ������
��*\�ָ��������ָ���������
�����֡�Сд��ĸ����д��ĸ������Ϣ��ǣ����ָ�����
3���˹��趨�ķּ����
��ʽ����xxx -> x����xxx : x����xxx->x��*/

// �˹��ּ����������Ҽƻ����ü����򵥵Ĺ���ѳ���������
// ����ģ��֮ǰû�Ӵ�������Ҳûʱ�����ű�ѵ����c++����������
// �պ�������

vector<string> SpellCorrector::getResult(const vector<vector<string>>& _src) {
	vector<string> result;
	//  _src��������ascii�ַ�
	if (_src.size() == 1) {
		for (auto& i : _src.at(0)) {
			int tmp = getWordType(i);
			if (tmp == DIGIT || tmp == CAPITAL || tmp == LITTLE) {
				result.push_back(i);
				return result;
			}
		}
	}
	//  �������
	for (size_t i = 1; i < _src.size(); i++) {
		for (auto& j : _src.at(i)) {
			switch (getWordType(result.at(i - 1))) {
			case DIGIT:
				break;
			case LITTLE:
				break;
			case CAPITAL:
				break;
			case INFO:
				break;
			case EXPLICTCUT:
				break;
			case LB:
				break;
			case RB:
				break;
			default:
				break;
			}
		}
	}
	//  �������

	//  ˫�����
	return result;
}

//map<string, int> SpellCorrector::chemAscii2typeMap = { };
int SpellCorrector::getWordType(const std::string& _word) {
	if (_word.length() == 1) {
		if (_word.at(0) >= '0' && _word.at(0) <= '9') {
			return DIGIT;
		}
		else if (_word.at(0) >= 'A' && _word.at(0) <= 'Z') {
			return CAPITAL;
		}
		else if (_word.at(0) >= 'a' && _word.at(0) <= 'z') {
			return LITTLE;
		}
		else if (_word.at(0) == '(' || _word.at(0) == '{' || _word.at(0) == '[') {
			return LB;
		}
		else if (_word.at(0) == ')' || _word.at(0) == '}' || _word.at(0) == ']') {
			return RB;
		}
		else if (_word.at(0) == '#' || _word.at(0) == '=' || _word.at(0) == '+'
			|| _word.at(0) == '-' || _word.at(0) == '>' || _word.at(0) == '<') {
			return EXPLICTCUT;
		}
	}
	else if (_word.length() == 2) {
		if (_word == "->" || _word == "<-" || _word == "<=" || _word == ">=") {
			return EXPLICTCUT;
		}
	}
	else if (_word.length() == 3) {
		if (_word == "(g)" || _word == "(s)") {
			return INFO;
		}
	}
	return NONE;
}


string SpellCorrector::getValidWord(const vector<vector<string>>& _src,
	int start, int end) {
	/*������ܺͶ������ͬǰ׺�ĵ���ƥ��*/
	/*������ܺͳ�����ͬ������ĸ��ͬ�ĵ���ƥ��*/
	/*����ĵ�����Ȼ�Ǽ�Ȩ��*/
	map<string, double> scores;
	double reduced;
	int coveredLen;
	double score, baseScore;
	const size_t objLen = end - start + 1;
	for (size_t i = 0; i < validWords.size(); i++) {
		const string& dicWord = validWords.at(i);
		coveredLen = std::min(dicWord.length(), objLen);
		if (coveredLen < objLen) {
			continue;
		}
		score = 0;
		baseScore = 100.0 / coveredLen;
		//if (objLen == coveredLen) {
		//	score += baseScore;
		//}
		for (int j = 0; j < coveredLen; j++) {
			reduced = 1.0;
			for (auto& k : _src.at(j + start)) {
				if (k == "")
					reduced -= 0.05;
				if (k.length() == 1 && k.at(0) == dicWord.at(j)) {
					score += baseScore * reduced;
					break;
				}
			}
		}
		string curPrefix = dicWord.substr(0, objLen);
		auto it = scores.find(curPrefix);
		if (it == scores.end()) {
			scores[curPrefix] = score;
		}
		else {
			it->second += 0.5;
		}
	}
	map<string, double>::iterator it = scores.begin();
	for (auto i = scores.begin(); i != scores.end(); i++) {
		if (i->second > it->second) {
			it = i;
		}
	}
	if (it->second > 80) {
		return it->first;
	}
	else {
		string tmp;
		for (int i = start; i <= end; i++) {
			tmp += _src[i].at(0);
		}
		return tmp;
	}
}

void SpellCorrector::getBestResult(const vector<vector<string>>& _src,
	vector<string>& result) {
	result.clear();
	vector<vector<string>> src;
	for (auto& i : _src) {
		src.push_back(vector<string>());
		for (auto& j : i) {
			src.back().push_back(getChemAscii(j));
		}
	}
	vector<int> divPos;
	divPos.push_back(-1);
	for (size_t i = 0; i < src.size(); i++) {
		bool isDiv(false);
		for (auto& j : src.at(i)) {
			if (getWordType(j) == EXPLICTCUT) {
				isDiv = true;
				break;
			}
		}
		if (isDiv) {
			divPos.push_back(i);
		}
	}
	divPos.push_back(src.size());
	cout << "divPos.size()=" << divPos.size() << endl;
	int start, end;
	for (size_t i = 1; i < divPos.size(); i++) {
		start = divPos.at(i - 1) + 1; end = divPos.at(i) - 1;
		if (start <= end) {
			result.push_back(
				getValidWord(src, start, end)
			);
		}
		if (i != divPos.size() - 1) {
			result.push_back(src.at(divPos.at(i)).at(0));
		}
	}
	/*for (auto& i : result) {
		cout << i << " ";
	}*/
}
