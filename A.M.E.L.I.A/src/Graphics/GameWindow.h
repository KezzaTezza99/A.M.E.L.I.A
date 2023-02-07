#ifndef __GAME_WINDOW__
#define __GAME_WINDOW__
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class GameWindow
{
private:
	//Window variables
	const char* m_title;								//The game window title
	int m_width, m_height;								//The width and height of the game window
	GLFWwindow* m_window;								//Pointer to the window
	bool m_closed;										//Flag to close the window

	//User input
	bool m_keys[MAX_KEYS];								//Keys that have been pressed
	bool m_mouseButtons[MAX_BUTTONS];					//Mouse buttons that have been pressed
	double m_x, m_y;									//The mouses X,Y coords

public:
	//Methods for the window
	GameWindow(const char* _title, int _width, int _height);
	~GameWindow();
	bool Closed() const;
	void Update();
	void Clear() const;
	void SetBackgroundColour(glm::vec3 _colour);

	//Methods for user input
	bool IsKeyPressed(unsigned int _keyCode) const;
	bool IsMouseButtonPressed(unsigned int _button) const;
	void GetMousePosition(double& _x, double& _y) const;

	//Useful getter methods
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	bool InitialisedGLFW();
	//Callback functions required by GLFW
	friend static void window_resize(GLFWwindow* _window, int _width, int _height);
	friend static void key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	friend static void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods);
	friend static void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos);
};
#endif // !__GAME_WINDOW__