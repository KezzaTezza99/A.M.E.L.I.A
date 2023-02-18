#ifndef __GAME_WINDOW__
#define __GAME_WINDOW__
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include "Camera.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class GameWindow
{
private:
	//Window variables
	const char* m_title;																																//The game window title
	int m_width, m_height;																																//The width and height of the game window
	GLFWwindow* m_window;																																//Pointer to the window
	bool m_closed;																																		//Flag to close the window
	Camera& m_camera;																																	//Reference to the camera to allow for movement inside the window

	//User input
	bool m_keys[MAX_KEYS];																																//Keys that have been pressed
	bool m_mouseButtons[MAX_BUTTONS];																													//Mouse buttons that have been pressed
	double m_x, m_y;																																	//The mouses X,Y coords

public:
	//Methods for the window
	GameWindow(const char* _title, int _width, int _height, Camera& _camera);																			//Creates a GLFW Window 
	~GameWindow();																																		//Destroys the GLFW window
	bool Closed() const;																																//Close the window
	void Update();																																		//Update the window (poll events and swap buffers)
	void Clear() const;																																	//Clear the screen
	void SetBackgroundColour(glm::vec3 _colour);																										//Set a background colour for the window

	//Methods for user input
	bool IsKeyPressed(unsigned int _keyCode) const;																										//Check to see if a keyboard key has been pressed
	bool IsMouseButtonPressed(unsigned int _button) const;																								//Check to see if a mouse button has been pressed
	void GetMousePosition(double& _x, double& _y) const;																								//Gets the mouse cursor

	//Useful getter methods
	inline int GetWidth() const { return m_width; }																										//Get the windows width
	inline int GetHeight() const { return m_height; }																									//Get the windows height
	inline Camera& GetCamera() const { return m_camera; }

private:
	bool InitialisedGLFW();																																//Initialise GLFW
	//Callback functions required by GLFW
	friend static void window_resize(GLFWwindow* _window, int _width, int _height);																		//Resize a window
	friend static void key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);												//Responsible for handling keyboard input
	friend static void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods);													//Handle mouse clicks
	friend static void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos);														//Handle cursor input

	//Camera stuff
	friend static void ProcessMouse(GLFWwindow* _window, Camera* _camera, double _xPos, double _yPos);
};
#endif // !__GAME_WINDOW__