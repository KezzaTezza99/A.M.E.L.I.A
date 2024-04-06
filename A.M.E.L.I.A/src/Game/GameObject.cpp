#include "GameObject.h"

//TO ADD: Texture default constructor needed
GameObject::GameObject()
	: m_position(0.0f, 0.0f), m_size(1.0f, 1.0f), m_velocity(0.0f), m_rotation(0.0f), m_texture(), m_isCollidable(false), m_isActive(false) { }

GameObject::GameObject(glm::vec2 _position, glm::vec2 _size, Texture _texture, glm::vec2 _velocity)
	: m_position(_position), m_size(_size), m_texture(m_texture), m_velocity(_velocity), m_rotation(0.0f), m_isCollidable(false), m_isActive(false) { }

void GameObject::Draw(Renderer2D& _renderer)
{
	_renderer.DrawSprite(&m_texture, m_position, m_size, m_rotation);
}