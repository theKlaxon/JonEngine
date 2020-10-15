#pragma once
#include <vector>

enum RenderFlags {
	RENDER_TRUE,
	RENDER_FALSE,
	RENDER_EVERY_FRAME,
	RENDERED
};

class CRenderObject {
public:

	CRenderObject();

	virtual void render();
	bool rendered;

	void SetRenderID(int id);
	int GetRenderID();
	
private:

	int renderID;
};

class CRenderPool {
public:

	CRenderPool();
	~CRenderPool();

	void init();
	void clear();

	void addToRenderPool(CRenderObject* renderObject);
	void removeFromRenderPool(CRenderObject* renderObject);

	void renderEntirePool();
	void renderSpecific(CRenderObject* renderObject);

private:

	std::vector<CRenderObject*> objects;
};

extern CRenderPool* renderPool;