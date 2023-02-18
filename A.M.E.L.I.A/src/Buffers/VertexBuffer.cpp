#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* _vertices, GLsizei _count, GLuint _componentCount)
	: m_componentCount(_componentCount)
{
	//Generating the buffer
	glGenBuffers(1, &m_vertexBufferID);
	//Binding the inital buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	//Packing the buffer with the data
	glBufferData(GL_ARRAY_BUFFER, _count * sizeof(GLfloat), _vertices, GL_STATIC_DRAW);
	//Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vertexBufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
