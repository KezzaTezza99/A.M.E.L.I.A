#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__
#include <glm.hpp>
#include "../Loaders/Texture.h"
#include "../Graphics/Renderer2D.h"

class GameObject
{
public:
	//Storing the game objects current state
	glm::vec2 m_position, m_size, m_velocity;
	float m_rotation;
	bool m_isCollidable;
	bool m_isActive;

	//Storing information for the renderer
	Texture m_texture;

	GameObject();
	GameObject(glm::vec2 _position, glm::vec2 _size, Texture _texture, glm::vec2 _velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(Renderer2D& _renderer);
};
#endif // !__GAME_OBJECT__