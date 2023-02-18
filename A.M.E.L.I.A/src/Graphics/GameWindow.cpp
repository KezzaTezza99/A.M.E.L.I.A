#include "GameWindow.h"
#include <iostream>

//Redefining the GLFW callbacks defined as friends to keep compiler happy
void window_resize(GLFWwindow* _window, int _width, int _height);
void key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods);
void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos);


void ProcessMouse(GLFWwindow* _window, Camera* _camera, double _xPos, double _yPos);

GameWindow::GameWindow(const char* _title, int _width, int _height, Camera& _camera)
    : m_title(_title), m_width(_width), m_height(_height)
{
    if (!InitialisedGLFW())
        glfwTerminate;

    //Initialising the arrays used for Input
    for (int i = 0; i < MAX_KEYS; i++) { m_keys[i] = false; }
    for (int i = 0; i < MAX_BUTTONS; i++) { m_mouseButtons[i] = false; }
}

GameWindow::~GameWindow()
{
    glfwTerminate();
}

bool GameWindow::Closed() const
{
    return glfwWindowShouldClose(m_window);
}

void GameWindow::Update()
{
    //Update
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void GameWindow::Clear() const
{
    //Clearing the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameWindow::SetBackgroundColour(glm::vec3 _colour)
{
    glClearColor(_colour.x, _colour.y, _colour.z, 1.0f);
}

bool GameWindow::IsKeyPressed(unsigned int _keyCode) const
{
    if (_keyCode >= MAX_KEYS)
        return false;
    return m_keys[_keyCode];
}

bool GameWindow::IsMouseButtonPressed(unsigned int _button) const
{
    if (_button >= MAX_BUTTONS)
        return false;
    return m_mouseButtons[_button];
}

void GameWindow::GetMousePosition(double& _x, double& _y) const
{
    _x = m_x;
    _y = m_y;
}

bool GameWindow::InitialisedGLFW()
{
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile

    // Checking to see if GLFW was initialised sucessfully
    if (!glfwInit())
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating a window 
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    //Checking to see if the window was created succesfully or not
    if (!m_window)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        return false;
    }

    //Creating the current window context
    glfwMakeContextCurrent(m_window);
    glfwMakeContextCurrent(m_window);
    //Need a pointer to window for key handling
    glfwSetWindowUserPointer(m_window, this);
    //Allows for window resizing
    glfwSetWindowSizeCallback(m_window, window_resize);
    //Allows for keyboard call backs 
    glfwSetKeyCallback(m_window, key_callback);
    //Allows for mouse call backs 
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    //Allows for mouse cursor callbacks
    glfwSetCursorPosCallback(m_window, cursor_position_callback);

    //Disabling VSYNC
    glfwSwapInterval(0);

    //Checking to see if GLEW initialised correctly
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return false;
    }
    return true;
}

//GLFW Callback functions
void window_resize(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

void key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(_window);
    gameWindow->m_keys[_key] = _action != GLFW_RELEASE;

    if (_key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(_window, true);
    
}

void mouse_button_callback(GLFWwindow* _window, int _button, int _action, int _mods)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(_window);
    gameWindow->m_mouseButtons[_button] = _action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* _window, double _xpos, double _ypos)
{
    GameWindow* gameWindow = (GameWindow*)glfwGetWindowUserPointer(_window);
    gameWindow->m_x = _xpos;
    gameWindow->m_y = _ypos;
}

//CAM
void ProcessMouse(GLFWwindow* _window, Camera* _camera, double _xPos, double _yPos)
{
    _camera->RotateCamera(_xPos, _yPos);
}
