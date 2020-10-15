#include "input.h"

CInput* gInput;

void CKeyFunc::bind() {

	return;
}

CKeyFunc::CKeyFunc() {

}

CInput::CInput() {
	keyFuncs.clear();
}

void CInput::inKey(int key) {

}

void CInput::defineKeyInputToFunction(int key, void* function) {

}

void CInput::runKeyFunc(int key) {

}

bool CInput::getKeyFunc(int key) {

}