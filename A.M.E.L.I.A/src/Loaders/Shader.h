#ifndef __SHADER__
#define __SHADER__
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
private:
	GLuint m_shaderID;
	const char* m_vertexShader;
	const char* m_fragmentShader;

public:
	void LoadShaders(const char* _vertexSrc, const char* _fragmentSrc);
	void UseShader();
	void DeleteShader();

	inline GLuint GetShaderID() { return m_shaderID; }
};
#endif // !__SHADER__