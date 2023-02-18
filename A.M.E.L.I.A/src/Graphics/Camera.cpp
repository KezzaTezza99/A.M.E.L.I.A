#include "Camera.h"

Camera::Camera(const float& _WIDTH, const float& _HEIGHT)
{
	//Setting some default camera paramaters
	m_position = glm::vec3(0.0f, 1.0f, 10.0f);
	m_front = glm::vec3(0.0f, 0.0f, 0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	//Want the camera to be positioned at the centre of the screen 
	m_lastX = _WIDTH / 2;
	m_lastY = _WIDTH / 2;
	m_firstMouse = true;

	m_yaw = -90.0f;
	m_pitch = 0.0f;
}

void Camera::MoveCamera(glm::vec3 _newPosition)
{
	m_position = glm::vec3(_newPosition);
}

void Camera::RotateCamera(double& _xPos, double& _yPos)
{
	//The mouse has already been initialised need to reset some paramas
	if (m_firstMouse)
	{
		m_lastX = _xPos;
		m_lastY = _yPos;
		m_firstMouse = false;
	}

	float xOffset = _xPos - m_lastX;
	float yOffset = _yPos - m_lastY;

	m_lastX = _xPos;
	m_lastY = _yPos;

	const float SENSITIVITY = 0.1f;
	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	m_yaw += SENSITIVITY;
	m_pitch += SENSITIVITY;

	//Capping the users ability to look up and down to an extend
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	//Working out Euler Angle
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(direction);
}