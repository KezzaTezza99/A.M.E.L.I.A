#ifndef __RENDERER_2D__
#define __RENDERER_2D__
#include "../Loaders/Shader.h"
#include "../Loaders/Texture.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

//A simple renderer to render sprites 
class Renderer2D
{
private:
	Shader m_shader;// = nullptr;
	//Texture& m_texture;// = nullptr;
	VertexArray* m_vao = nullptr;
	VertexBuffer* m_vbo = nullptr;
	IndexBuffer* m_ibo = nullptr;
public:
	Renderer2D();
	void DrawSprite();
	void DrawSprite(Texture* _texture, glm::vec2& _position, glm::vec2& _size, float& _rotation);
};
#endif // !__RENDERER_2D__
