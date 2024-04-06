#include "Renderer2D.h"

Renderer2D::Renderer2D()
{
    //TODO: Game Object Class 
    //Then create a "player" class that holds this info and then see if I can render that
    //If I can do that then try to fix the textures for this way of rendering 
    //once all that is done I will have enough to start implementing basic collisions

    m_shader.LoadShaders("src/GLSL/vertex.vert", "src/GLSL/fragment.frag");

    //Texture m_texture("./Assets/Textures/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    //m_texture.TextureUnit(m_shader, "texture_diffuse1", 0);

    //Configuring a quad 
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

    //Buffers
    m_vao = new VertexArray;
    m_vbo = new VertexBuffer(vertices, sizeof(vertices), 3);
    m_ibo = new IndexBuffer(indices, sizeof(indices));

    m_vao->LinkAttributes(*m_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    //m_vao->LinkAttributes(*m_vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Renderer2D::DrawSprite()
{
    m_vao->Bind();
    m_ibo->Bind();
    glDrawElements(GL_TRIANGLES, m_ibo->GetComponentCount(), GL_UNSIGNED_INT, 0);
    m_vao->Unbind();
    m_ibo->Unbind();
}

void Renderer2D::DrawSprite(Texture* _texture, glm::vec2& _position, glm::vec2& _size, float& _rotation)
{
    _texture->Bind();
    m_vao->Bind();
    m_ibo->Bind();
    glDrawElements(GL_TRIANGLES, m_ibo->GetComponentCount(), GL_UNSIGNED_INT, 0);
    m_vao->Unbind();
    m_ibo->Unbind();
}
