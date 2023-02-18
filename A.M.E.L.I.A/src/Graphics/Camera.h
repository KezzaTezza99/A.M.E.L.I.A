#ifndef __CAMERA__
#define __CAMERA__
#include <glm.hpp>

class Camera
{
private:
	glm::vec3 m_position, m_front, m_up;

	float m_lastX, m_lastY;
	bool m_firstMouse;
	float m_yaw, m_pitch;

public:
	Camera(const float& _WIDTH, const float& _HEIGHT);
	virtual void MoveCamera(glm::vec3 _newPosition);
	virtual void RotateCamera(double& _xPos, double& _yPos);

	inline glm::vec3 GetCameraPosition() const { return m_position; }
	inline glm::vec3 GetCameraFront() const { return m_front; }
	inline glm::vec3 GetCamerUp() const { return m_up; }
};
#endif // !__CAMERA__