#include <iostream>
#include <glm.hpp>
#include "src/Graphics/GameWindow.h"
#include "src/Loaders/Shader.h"

const int WIDTH = 800;
const int HEIGHT = 800;

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
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	GLuint indices[] =
	{
		0, 1, 3,			// first triangle
		1, 2, 3				// second triangle
	};

	//VBO, VAO and IBO
	unsigned int VBO, VAO, IBO;
	//Generating the VAO / VBO / IBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Binding
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Linking vertex atrributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Game Loop
	while (!window.Closed())
	{
		window.Clear();
		window.SetBackgroundColour(glm::vec3(1.0f, 1.0f, 1.0f));

		//Render here
		shader.UseShader();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Update
		window.Update();
	}

	return 0;
}