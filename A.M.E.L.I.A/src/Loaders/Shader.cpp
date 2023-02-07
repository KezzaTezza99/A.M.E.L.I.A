#include "Shader.h"
#include <iostream>

void Shader::LoadShaders(const char* _vertexSrc, const char* _fragmentSrc)
{
	//Using the filepath provided to open shader src files and then read into a string
	std::string vertexSrcCode;
	std::string fragmentSrcCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	//Error Handling
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//Opening the file at the provided location
		vertexFile.open(_vertexSrc);
		fragmentFile.open(_fragmentSrc);

		//Reading the files into a buffer
		std::stringstream vertexBuffer, fragmentBuffer;
		vertexBuffer << vertexFile.rdbuf();
		fragmentBuffer << fragmentFile.rdbuf();

		//Closing the file handlers
		vertexFile.close();
		fragmentFile.close();

		//Converting the buffer stream into a string
		vertexSrcCode = vertexBuffer.str();
		fragmentSrcCode = fragmentBuffer.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: Failure during shader file reading" << std::endl;
	}

	//Converting the string into const char* - also allows me to access it throughout Shader
	m_vertexShader = vertexSrcCode.c_str();
	m_fragmentShader = fragmentSrcCode.c_str();

	//Used to check for any compile errors
	unsigned int vertex, fragment;
	int success;
	char compileInfo[256];

	//Compiling the vertex shader first
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &m_vertexShader, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 256, NULL, compileInfo);
		std::cout << "ERROR: Vertex shader failed to compile" << std::endl << compileInfo << std::endl;
	}

	//Vertex shader has successfully compiled now to compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &m_fragmentShader, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 256, NULL, compileInfo);
		std::cout << "ERROR: Fragment shader failed to compile" << std::endl << compileInfo << std::endl;
	}

	//Both shaders compiled successfully time to create a shader program
	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertex);
	glAttachShader(m_shaderID, fragment);
	glLinkProgram(m_shaderID);

	//Check for linking errors
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(m_shaderID, 256, NULL, compileInfo);
		std::cout << "ERROR: Shader program linking failed to compile" << std::endl << compileInfo << std::endl;
	}

	//Deleting the shaders as they have been sucessfully linked to the shader program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::UseShader()
{
	glUseProgram(m_shaderID);
}

void Shader::DeleteShader()
{
	glUseProgram(0);
}
