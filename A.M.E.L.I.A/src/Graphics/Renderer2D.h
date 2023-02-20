#ifndef __RENDERER_2D__
#define __RENDERER_2D__
#include "../Loaders/Shader.h"
#include "../Loaders/Image.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

//A simple renderer to render sprites 
class Renderer2D
{
private:
	Shader m_shader;// = nullptr;
	//Image& m_texture;// = nullptr;
	VertexArray* m_vao = nullptr;
	VertexBuffer* m_vbo = nullptr;
	IndexBuffer* m_ibo = nullptr;
public:
	Renderer2D();
	void DrawSprite();
};
#endif // !__RENDERER_2D__
