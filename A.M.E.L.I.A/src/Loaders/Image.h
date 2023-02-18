#ifndef __IMAGE__
#define __IMAGE__
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include "Shader.h"

//An image is just a texture and this class will load textures for me 
class Image
{
private:
	GLuint m_textureID;
	GLenum m_textureType;
	
public:
	Image(const char* _imageLoc, GLenum _textureType, GLenum _slot, GLenum _format, GLenum _pixelType);
	~Image();
	void TextureUnit(Shader& _shader, const char* _uniform, GLuint _unit);
	void Bind() const;
	void Unbind() const;
};
#endif // !__IMAGE__
