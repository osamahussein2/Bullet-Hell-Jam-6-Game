#include "Shader.h"

Shader::Shader() : shaderProgram(NULL)
{
}

Shader::~Shader()
{
}

void Shader::InitializeShaders(const char* vertexSource, const char* fragmentSource)
{
	unsigned int sVertex, sFragment, gShader;

	// vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);

	CompileErrors(sVertex, "VERTEX");

	// fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);

	CompileErrors(sFragment, "FRAGMENT");

	// shader program
	shaderProgram = glCreateProgram();

	if (!shaderProgram)
	{
		cerr << "Cannot create gl program" << endl;
	}

	glAttachShader(shaderProgram, sVertex);
	glAttachShader(shaderProgram, sFragment);

	glLinkProgram(shaderProgram);
	CompileErrors(shaderProgram, "PROGRAM");

	// Delete the shaders once they're linked into the created program
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Shader::CompileErrors(unsigned int object, string type)
{
	int success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Compile-time error: \nType: " << type << "\n"
				<< infoLog << "\n \n \n"
				<< std::endl;
		}
	}

	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::Shader: Link-time error: \nType: " << type << "\n"
				<< infoLog << "\n \n \n"
				<< std::endl;
		}
	}
}
