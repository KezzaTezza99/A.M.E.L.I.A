#ifndef __VERTEX_ARRAY__
#define __VERTEX_ARRAY__
#include <glew.h>
#include <vector>
#include "VertexBuffer.h"

class VertexArray
{
private:
	GLuint m_vertexArrayID;
	std::vector<VertexBuffer*> m_vertexBuffers;

public:
	VertexArray();
	~VertexArray();

	void AddVertexBuffer(VertexBuffer* _VBO, GLuint _index);
	void LinkAttributes(VertexBuffer& _VBO, GLuint _layout, GLuint _numOfComponents, GLenum _type, GLsizeiptr _stride, void* _offset);
	void Bind() const;
	void Unbind() const;
};
#endif // !__VERTEX_ARRAY__
