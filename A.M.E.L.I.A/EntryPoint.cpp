#include <iostream>
#include <glm.hpp>
#include "src/Graphics/GameWindow.h"
#include "src/Graphics/Camera.h"
#include "src/Graphics/Renderer2D.h"
#include "src/Loaders/Shader.h"
#include "src/Loaders/Image.h"
#include "src/Buffers/VertexBuffer.h"
#include "src/Buffers/VertexArray.h"
#include "src/Buffers/IndexBuffer.h"

//GOALS, TASKS AND GENERAL INFO
#pragma region Info
// Tasks: 2D Renderer (render basic 2D primitives)
// Should the renderer be responsible for creating all the buffers and matrices?
// Should the game window be responsible for creating and destroying the camera? 

// Tasks: 2D Collision
// Tasks: Load Models
// Tasks: Go 3D
// Tasks: Basic Lighting
//TODO: Decouple the game window from input?
#pragma endregion
//!

const int WIDTH = 800;
const int HEIGHT = 800;

int main()
{
	//Creating the camera first as it needs to be passed into the game window
	Camera camera(WIDTH, HEIGHT);

	//Creating a window
	GameWindow window("A.M.E.L.I.A", WIDTH, HEIGHT, camera);

	//Creating and loading the vertex / fragment shader
	//Shader shader;
	//shader.LoadShaders("src/GLSL/vertex.vert", "src/GLSL/fragment.frag");
	
#if 0
	//Until model loading is implemented using a basic quad with a wood texture
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

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//Game Loop
	while (!window.Closed())
	{
		window.Clear();
		window.SetBackgroundColour(glm::vec3(1.0f, 1.0f, 1.0f));

		// --- PERFORMANCE ---
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

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
		window.Update(deltaTime);
	}
	return 0;
#else
	Renderer2D renderer;
	//Image woodTexture("./Assets/Textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	//woodTexture.TextureUnit(shader, "texture_diffuse1", 0);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//Game Loop
	while (!window.Closed())
	{
		window.Clear();
		window.SetBackgroundColour(glm::vec3(1.0f, 1.0f, 1.0f));

		// --- PERFORMANCE ---
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// --- RENDER ---
		//Activating the shader
		//shader.UseShader();
		renderer.DrawSprite();

		//Updating the window
		window.Update(deltaTime);
	}
	return 0;
#endif
}