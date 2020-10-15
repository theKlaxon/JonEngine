#pragma once
#include "engine_global.h"

class CTriangle : public CRenderObject {
public:

	CTriangle();

	void init(); //don't run manually, this is run at the end of the constructor
	void render() override;

	void SetScale(int scale);
	int GetScale();

	void SetRenderSmall(bool truefalse);

private:

	int renderScale;

	bool renderSmall;

	GLuint VertexArrayID;
	GLuint vertexbuffer;

	static GLfloat g_vertex_buffer_data[];
	static GLfloat g_vertex_buffer_data_small[];
};