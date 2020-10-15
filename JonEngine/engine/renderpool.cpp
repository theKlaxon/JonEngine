#include "renderpool.h"
#include <iostream>

CRenderPool* renderPool = new CRenderPool();

CRenderObject::CRenderObject() {
	rendered = NULL;
}

void CRenderObject::render() {

	return;
}

void CRenderObject::SetRenderID(int id) {
	renderID = id;
}

int CRenderObject::GetRenderID() {
	return renderID;
}

CRenderPool::CRenderPool() {
	objects.clear();
}

CRenderPool::~CRenderPool() {
	objects.clear();
}

void CRenderPool::init() {
	clear();
}

void CRenderPool::clear() {
	objects.clear();
}

void CRenderPool::addToRenderPool(CRenderObject* renderObject) {
	objects.insert(objects.end(), renderObject);
	printf("Object added to render pool. \n");
}

void CRenderPool::removeFromRenderPool(CRenderObject* renderObject) {

}

void CRenderPool::renderEntirePool() {
	for (int j = 0; j < objects.capacity(); j++) {
		objects[j]->render();
		objects[j]->SetRenderID(j);
	}
}

void CRenderPool::renderSpecific(CRenderObject* renderObject) {

}