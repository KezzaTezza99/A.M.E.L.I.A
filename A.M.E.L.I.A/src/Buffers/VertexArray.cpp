#include "VertexArray.h"

VertexArray::VertexArray()
{
	//Generating the VAO
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	//Deleting all the VBOs stored in the vector
	for (int i = 0; i < m_vertexBuffers.size(); i++)
		delete m_vertexBuffers[i];
	//Deleting the VAO
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::AddVertexBuffer(VertexBuffer* _VBO, GLuint _index)
{
	//Adding a VBO to the list of buffers already stored
	Bind();
	_VBO->Bind();

	glEnableVertexAttribArray(_index);
	glVertexAttribPointer(_index, _VBO->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);


	_VBO->Unbind();
	Unbind();
}

void VertexArray::LinkAttributes(VertexBuffer& _VBO, GLuint _layout, GLuint _numOfComponents, GLenum _type, GLsizeiptr _stride, void* _offset)
{
	Bind();
	_VBO.Bind();
	glVertexAttribPointer(_layout, _numOfComponents, _type, GL_FALSE, _stride, _offset);
	glEnableVertexAttribArray(_layout);
	_VBO.Unbind();
	Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
