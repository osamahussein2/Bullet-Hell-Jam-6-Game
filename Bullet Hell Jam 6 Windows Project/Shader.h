#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Include the GLM header files (OpenGL Mathematics Library)
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader();
	~Shader();

	void InitializeShaders(const char* vertexSource_, const char* fragmentSource_);

	void CompileErrors(unsigned int object_, string type_);

	unsigned int shaderProgram;
};

#endif