#include "triangle.h"
#include "engine_global.h"

// An array of 3 vectors which represents 3 vertices
GLfloat CTriangle::g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

GLfloat CTriangle::g_vertex_buffer_data_small[] = {
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

CTriangle::CTriangle() {
	VertexArrayID = NULL;
	vertexbuffer = NULL;

	renderSmall = false;
	init();
}

void CTriangle::init() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.

	if (!renderSmall) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		return;
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_small), g_vertex_buffer_data_small, GL_STATIC_DRAW);
	}

}

void CTriangle::render() {
	printf("Object rendered. \n");

	// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0.5f,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

}

void CTriangle::SetScale(int scale) {

	renderScale = scale;
}

int CTriangle::GetScale() {
	
	return renderScale;
}

void CTriangle::SetRenderSmall(bool truefalse) {

	renderSmall = truefalse;
}