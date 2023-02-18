#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__
#include <glew.h>

class IndexBuffer
{
private:
	GLuint m_indexBufferID;
	GLuint m_componentCount;

public:
	IndexBuffer(GLushort* _indices, GLsizei _componentCount);
	IndexBuffer(GLuint* _indices, GLsizei _componentCount);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint GetComponentCount() const { return m_componentCount; }
};
#endif // !__INDEX_BUFFER__