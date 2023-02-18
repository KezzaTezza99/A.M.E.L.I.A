#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLushort* _indices, GLsizei _componentCount)
	: m_componentCount(_componentCount)
{
	//Generating the IBO
	glGenBuffers(1, &m_indexBufferID);
	//Binding the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	//Packing the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _componentCount * sizeof(GLushort), _indices, GL_STATIC_DRAW);
	//Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(GLuint* _indices, GLsizei _componentCount)
	: m_componentCount(_componentCount)
{
	//Generating the IBO
	glGenBuffers(1, &m_indexBufferID);
	//Binding the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	//Packing the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _componentCount * sizeof(GLuint), _indices, GL_STATIC_DRAW);
	//Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	//Deleting the IBO
	glDeleteBuffers(1, &m_indexBufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
