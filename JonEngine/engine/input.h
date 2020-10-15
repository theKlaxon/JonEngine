#pragma once
#include "engine_global.h"
#include <vector>

class CKeyFunc {
public:
	CKeyFunc();

	virtual void bind();
};

class CInput {
public:

	CInput();

	void inKey(int key);
	void defineKeyInputToFunction(int key, void* function);
	void runKeyFunc(int key);

	bool getKeyFunc(int key);

private:

	std::vector<CKeyFunc> keyFuncs;
};

extern CInput* gInput;