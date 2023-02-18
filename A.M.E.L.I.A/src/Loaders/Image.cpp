#include "Image.h"

Image::Image(const char* _imageLoc, GLenum _textureType, GLenum _slot, GLenum _format, GLenum _pixelType)
	: m_textureType(_textureType)
{
	//Info about the loaded image
	int width, height, numOfColChannels;

	//Flipping the image to work with OpenGLs coordinate system
	stbi_set_flip_vertically_on_load(true);

	//Loading the image using stb.h
	unsigned char* data = stbi_load(_imageLoc, &width, &height, &numOfColChannels, 0);

	//Generating the texture
	glGenTextures(1, &m_textureID);
	glActiveTexture(_slot);
	glBindTexture(_textureType, m_textureID);

	//Configuring some OpenGL texture params
	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Assinging the loaded image data with the texture object created
	glTexImage2D(_textureType, 0, GL_RGB, width, height, 0, _format, _pixelType, data);

	//Generating the mipmaps for the texture
	glGenerateMipmap(_textureType);

	//Deleting the image and free resources
	stbi_image_free(data);
	glBindTexture(_textureType, 0);
}

Image::~Image()
{
	glDeleteTextures(1, &m_textureID);
}

void Image::TextureUnit(Shader& _shader, const char* _uniform, GLuint _unit)
{
	//Getting the location of the uniform from the Vertex Shader
	GLuint uniform = glGetUniformLocation(_shader.GetShaderID(), _uniform);
	_shader.UseShader();
	glUniform1i(uniform, _unit);
}

void Image::Bind() const
{
	glBindTexture(m_textureType, m_textureID);
}

void Image::Unbind() const
{
	glBindTexture(m_textureType, 0);
}