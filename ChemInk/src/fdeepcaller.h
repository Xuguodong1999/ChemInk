#pragma once
#include "stdafx.h"
#include <fdeep/fdeep.hpp>


class FdeepCaller :public QObject {
	Q_OBJECT
public:
	FdeepCaller();
	~FdeepCaller();
	bool isLoaded();
protected:
	void loadModel(const char* filename);
	void predicts(fdeep::tensor5s_vec& _input, fdeep::tensor5s_vec& _output);
private:
	fdeep::model* kerasModel;
	bool loaded;
};