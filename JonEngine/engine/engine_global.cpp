#include "engine_global.h"
#include "input.h"
#include "triangle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <windows.h>
#define GetCurrentDir _getcwd

CEngineGlobal* gEngine;

std::string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

#define REMSTRING 12

const char* getShader(const char* shader) {
	std::string start = get_current_dir().c_str();
	std::string path = "/release/shaders/";
	std::string name = shader;
	start.append(path);
	start.append(name);

	char result[MAX_PATH];
	char remove[REMSTRING];
	std::string maxpath = result;
	maxpath.erase(REMSTRING);
	maxpath.append(path);
	maxpath.append(shader);

	return maxpath.c_str();
}

void createSmallTriangle() {
    CTriangle* smallTriangle = new CTriangle();
    smallTriangle->SetRenderSmall(true);
    renderPool->addToRenderPool(smallTriangle);
}

void setBinds() {

}

CEngineGlobal::CEngineGlobal() {
	renderPool = new CRenderPool();
    gInput = new CInput();
    
    allowInput = NULL;
}

CEngineGlobal::~CEngineGlobal() {

}

void CEngineGlobal::Load(int width, int height, const char* name) {
    setBinds();
    loadGL(width, height, name);
}

void CEngineGlobal::RunFrame() {

	renderPool->renderEntirePool();
}

void CEngineGlobal::SetInputAllowed(bool truefalse) {
    
    allowInput = truefalse;
}

bool CEngineGlobal::InputAllowed() {
    return allowInput;
}

GLuint CEngineGlobal::LoadShaders(GLuint vertexShader, GLuint fragShader, const char* vertex_file_path, const char* fragment_file_path) {

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);

	// Check Vertex Shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragShader, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragShader);

	// Check Fragment Shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, fragShader);
	glAttachShader(ProgramID, fragShader);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, fragShader);
	glDetachShader(ProgramID, fragShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	
	return ProgramID;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_T) createSmallTriangle();
}

void CEngineGlobal::loadGL(int width, int height, const char* name) {

    SetInputAllowed(false);

    if (!glfwInit())
    {
        printf("OpenGL failed to load! \n");
        return;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glWindow = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!glWindow)
    {
        // Window or OpenGL context creation failed
    }
    glfwMakeContextCurrent(glWindow);
    glfwSetKeyCallback(glWindow, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("No GLAD!. \n");
        return;
    }

    if (!renderPool) {
        renderPool = new CRenderPool();
        renderPool->init();
    }
    renderPool->init();

    CTriangle* triangle = new CTriangle();
    renderPool->addToRenderPool(triangle);

	get_current_dir().c_str();

    SetInputAllowed(true);
	GLuint vertextShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);;
	GLuint shaderProgram = LoadShaders(vertextShader, fragmentShader,
		getShader("vertex_triangle.glsl"), getShader("fragment_triangle.glsl"));

    while (!glfwWindowShouldClose(glWindow))
    {

        // Keep running
        int width, height;
        glfwGetFramebufferSize(glWindow, &width, &height);
        glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

        RunFrame();

        glfwSwapBuffers(glWindow);
        glfwPollEvents();

    }

    unloadGL();

}

void CEngineGlobal::unloadGL() {

    renderPool->clear();

    glfwDestroyWindow(glWindow);
    glfwTerminate();

    return;
}