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
	inline void SetMat4(const std::string& _uniformName, glm::mat4 _value) const { glUniformMatrix4fv(m_shaderID, 1, GL_FALSE, glm::value_ptr(_value)); }
};
#endif // !__SHADER__