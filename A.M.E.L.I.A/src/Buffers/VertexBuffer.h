#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__
#include <glew.h>
#include <glfw3.h>

class VertexBuffer
{
private:
	GLuint m_vertexBufferID;
	GLuint m_componentCount;

public:
	VertexBuffer(GLfloat* _vertices, GLsizei _count, GLuint _componentCount);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;

	inline GLuint GetComponentCount() const { return m_componentCount; }
};
#endif // !__VERTEX_BUFFER__