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
	GameWindow window("A.M.E.L.I.A", WIDTH, HEIGHT, camera);

	//Shaders
	Shader shader;
	shader.LoadShaders("src/GLSL/vertex.vert", "src/GLSL/fragment.frag");

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
	woodTexture.TextureUnit(shader, "texture_diffuse1", 0);

	//Position
	vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	//UVs
	vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//VIEW MATRIX ETC
	//Game Loop
	while (!window.Closed())
	{
		window.Clear();
		window.SetBackgroundColour(glm::vec3(1.0f, 1.0f, 1.0f));

		// --- PERFORMANCE ---
		
		//Matrices
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);

		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		viewMatrix = glm::lookAt(camera.GetCameraPosition(), camera.GetCameraPosition() + camera.GetCameraFront(), camera.GetCameraUp());
		projectionMatrix = glm::perspective(glm::radians(45.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);

		//Getting the location of the matrices in the Vertex Shader
		unsigned int model = glGetUniformLocation(shader.GetShaderID(), "model");
		unsigned int view = glGetUniformLocation(shader.GetShaderID(), "view");
		unsigned int projection = glGetUniformLocation(shader.GetShaderID(), "projection");

		//Passing the matrices to the Vertex Shader as we have the location
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(view, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

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