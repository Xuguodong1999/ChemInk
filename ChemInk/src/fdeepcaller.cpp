#include "stdafx.h"
#include "fdeepcaller.h"
using namespace fdeep;
#include <thread>
#include <stdexcept>
using namespace std;
#pragma execution_character_set("UTF-8")

FdeepCaller::FdeepCaller()
	:loaded(false) {
	kerasModel = (model*)calloc(1, sizeof(model));
	if (!kerasModel) {
		throwErrorBox("�ڴ����ʧ��", "��FdeepCaller::FdeepCaller��");
		exit(-1);
	}
}

FdeepCaller::~FdeepCaller()
{
	delete kerasModel;
}


bool FdeepCaller::isLoaded() {
	return loaded;
}

void FdeepCaller::loadModel(const char* filename) {
	try {
		*kerasModel = load_model(filename);
	}
	catch (runtime_error err) {
		throwErrorBox("ģ�ͼ���ʧ��", err.what());
		loaded = false;
	}
	loaded = true;
}


void FdeepCaller::predicts(fdeep::tensor5s_vec& _input, fdeep::tensor5s_vec& _output) {
	_output = kerasModel->predict_multi(_input, true);
}

