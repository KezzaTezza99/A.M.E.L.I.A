#include <iostream>
#include <glm.hpp>
#include "src/Graphics/GameWindow.h"
#include "src/Graphics/Camera.h"
#include "src/Loaders/Shader.h"
#include "src/Loaders/Image.h"
#include "src/Buffers/VertexBuffer.h"
#include "src/Buffers/VertexArray.h"
#include "src/Buffers/IndexBuffer.h"

const int WIDTH = 800;
const int HEIGHT = 800;

//TEMP 
Camera camera(WIDTH, HEIGHT);

int main()
{
	//Creating a window
	GameWindow window("A.M.E.L.I.A", WIDTH, HEIGHT);

	//Shaders
	Shader shader;
	shader.LoadShaders("src/GLSL/basic.vert", "src/GLSL/basic.frag");

	//Quad
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

	//TODO: Change how VAO links attributes
	VertexArray vao;
	VertexBuffer vbo(vertices, sizeof(vertices), 3);
	IndexBuffer ibo(indices, sizeof(indices));

	//TODO: Check if the image format is RGB or RGBA
	Image woodTexture("./Assets/Textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	woodTexture.TextureUnit(shader, "tex0", 0);

	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.LinkAttributes(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// TODO: CAMERA STUFF
	

	//Game Loop
	while (!window.Closed())
	{
		window.Clear();
		window.SetBackgroundColour(glm::vec3(1.0f, 1.0f, 1.0f));

		// --- RENDER ---
		//Activating the shader
		shader.UseShader();

		//Binding the VAO, IBO and then drawing the elements
		woodTexture.Bind();
		vao.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetComponentCount(), GL_UNSIGNED_INT, 0);
		
		//Unbinding the buffers
		ibo.Unbind();
		vao.Unbind();

		//Updating the window
		window.Update();
	}

	return 0;
}