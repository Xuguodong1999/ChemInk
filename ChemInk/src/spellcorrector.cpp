#include "spellcorrector.h"
#include <iostream>
#include <QFile>
using namespace std;

//LETTERTYPE getType(vector<LETTERTYPE> _env) {
//	switch (_env.size()) {
//	case 0:
//		return LETTERTYPE::NONE;
//	case 1:
//		break;
//	case 2:
//		break;
//	default:
//		break;
//	}
//	switch (_index){
//	case 0:
//		return LETTERTYPE::DIGIT; break;		//  ����
//	case 0:
//		return LETTERTYPE::CAPITAL; break;	//  ��д��ĸ
//	case 0:
//		return LETTERTYPE::LITTLE; break;		//  Сд��ĸ
//	case 0:
//		return LETTERTYPE::GREEK; break;		//  ϣ����ĸ
//	case 0:
//		return LETTERTYPE::MATH; break;		//  ��ѧ�����
//	case 0:
//		return LETTERTYPE::INFO; break;		//  ע�ͷ������¼�ͷ
//	case 0:
//		return LETTERTYPE::SYMBOL; break;		//  ������
//	case 0:
//		return LETTERTYPE::NONE; break;		//  �������ַ�
//	default:
//		break;
//	}
//	return LETTERTYPE::NONE;
//}
//
////  similarWords[...]={x1,x2,...xn};
////  handle x1,...,xn
//vector<string> dim2Precise(vector<vector<int>>& _inputWords) {
//	vector<string> results;
//	//  ������ģ�����õ�ģ�����С���ֲ�����ģ��������ַ����ͣ����������
//	for (auto& probs : _inputWords) {
//		;
//	}
//
//
//	for (auto& i : similarWords) {
//		for (auto& j : i) {
//			cout << j << endl;
//		}
//	}
//	return results;
//}

vector<string> SpellCorrector::validWords;

SpellCorrector::SpellCorrector() {
	if (validWords.empty()) {
		QFile freader(":/Resources/language/dictionary.txt");
		freader.open(QIODevice::ReadOnly | QIODevice::Text);
		char tmp[50];
		if (freader.isOpen()) {
			freader.readLine(tmp, 50);
			while (true) {
				validWords.push_back(tmp);
				validWords.back().pop_back();
				freader.readLine(tmp, 50);
				if (freader.atEnd())
					break;
			}
		}
		else {
			std::cout << "�޷����ֵ��ļ�" << std::endl;
		}
		freader.close();
	}
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
	case  52:
		return 3;
	case  53:
		return 74;
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
	case  65:
		return 14;
	case  66:
		return 22;
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
	{"��","G"},
	{"��","H"},
	{"��","I"},
	{"��","J"},
	{"��","K"},
	{"��","L"},
	{"��","M"},
	{"��","N"},
	{"��","O"},
	{"��","P"},
	{"��","Q"},
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
	{"��","delta"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","lambda"},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","..."},
	{"��","sigma"},
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
	vector<int> scores;
	int cmplen;
	int score, baseScore;
	const size_t targetlen = end - start + 1;
	for (size_t i = 0; i < validWords.size(); i++) {
		string& word = validWords.at(i);
		cmplen = std::min(word.length(), targetlen);
		score = 0;
		baseScore = 100;
		if (targetlen == cmplen) {
			score += baseScore;
		}
		for (int j = 0; j < cmplen; j++) {
			for (auto& k : _src.at(j + start)) {
				if (k.length() == 1 && k.at(0) == word.at(j)) {
					score += baseScore;
					break;
				}
			}
		}
		scores.push_back(score);
	}
	size_t index = 0;
	for (size_t i = 1; i < scores.size(); i++) {
		if (scores.at(index) < scores.at(i)) {
			index = i;
		}
	}
	cout << "validWords.at(index)=" << validWords.at(index) << endl;
	return validWords.at(index).substr(0, targetlen);
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
