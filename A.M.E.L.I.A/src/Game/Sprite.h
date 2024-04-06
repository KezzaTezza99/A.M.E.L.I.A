#ifndef __SPRITE__
#define __SPRITE__
#include "../Loaders/Shader.h"
#include "../Loaders/Texture.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

//Class will basically create a quad and then assign a texture to that quad to render a "sprite"
class Sprite
{
private:
	VertexArray* vao = nullptr;
	VertexBuffer* vbo = nullptr;
	IndexBuffer* ibo = nullptr;
	Shader* shader = nullptr;
	Texture* texture = nullptr;

public:
	Sprite() = default;
	
	Sprite(const char* _texturePath)
	{
		//Creating a shader to use 
		shader = new Shader();
		shader->LoadShaders("src/GLSL/vertex.vert", "src/GLSL/fragment.frag");
		shader->UseShader();

		//Creating a texture
		texture = new Texture(_texturePath, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
		//texture->TextureUnit(shader, "texture_diffuse1", 0);

		//Configuring a QUAD
		float vertices[] =
		{
			//Coords				//UVs
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		// top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		// bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f		// top left 
		};

		GLuint indices[] =
		{
			0, 1, 3,			// first triangle
			1, 2, 3				// second triangle
		};

		//Creating the Buffers needed
		vao = new VertexArray;
		vbo = new VertexBuffer(vertices, sizeof(vertices), 3);
		ibo = new IndexBuffer(indices, sizeof(indices));

		//Linking the attributes
		vao->LinkAttributes(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
		vao->LinkAttributes(*vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void Draw()
	{
		/*
		//Activating the shader
		shader.UseShader();

		//Binding the VAO, IBO and then drawing the elements
		woodTexture.Bind();
		vao.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetComponentCount(), GL_UNSIGNED_INT, 0);
		*/

		shader->UseShader();
		texture->Bind();
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetComponentCount(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
		ibo->Unbind();
	}
};
#endif // !__SPRITE__