#pragma once
#include "renderpool.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CEngineGlobal {
public:

	CEngineGlobal();
	~CEngineGlobal();

	void Load(int width, int height, const char* name);
	void RunFrame(); //runs every frame

	void SetInputAllowed(bool truefalse);
	bool InputAllowed();
	
	CRenderPool* renderPool;
	GLuint LoadShaders(GLuint vertexShader, GLuint fragShader, const char* vertex_file_path, const char* fragment_file_path);

private:

	//opengl
	void loadGL(int width, int height, const char* name);
	void unloadGL();

	bool allowInput;

};

extern CEngineGlobal* gEngine;
extern GLFWwindow* glWindow;
