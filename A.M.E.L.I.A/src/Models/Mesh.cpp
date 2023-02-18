//#include "Mesh.h"
//
//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
//{
//	m_vertices = vertices;
//	m_indices = indices;
//	m_textures = textures;
//
//	//Initialising the necessary buffers
//	SetupMesh();
//}
//
//void Mesh::Draw(Shader& shader)
//{
//	//Binding the appropriate textures
//	unsigned int diffuse = 1;
//	unsigned int specular = 1;
//	unsigned int normal = 1;
//	unsigned int height = 1;
//
//	for (unsigned int i = 0; i < m_textures.size(); i++)
//	{
//		//Activating the proper texture unit before binding and retrieving the texture number 
//		glActiveTexture(GL_TEXTURE0 + i);
//		
//		std::string number;
//		std::string name = m_textures[i].type;
//
//		if (name == "texture_diffuse")
//			number = std::to_string(diffuse++);
//		else if (name == "texture_specular")
//			number = std::to_string(specular++);
//		else if (name == "texture_normal")
//			number = std::to_string(normal++);
//		else if (name == "texture_height")
//			number = std::to_string(height++);
//
//		//Now setting the sampler to the correct texture unit number
//		unsigned int shaderID = shader.GetShaderID();
//		//TODO: Is this not just setInt etc in shader class
//		glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
//
//		//Binding the texture
//		glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
//	}
//
//	//Drawing the mesh
//	glBindVertexArray(m_VAO);
//	//m_VAO.Bind();
//	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
//	
//	//Unbinding the VAO and texture
//	//m_VAO.Unbind();
//	glActiveTexture(GL_TEXTURE0);
//
//	////Draw the mesh
//	//m_VAO.Bind();
//	//glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
//	//m_VAO.Unbind();
//}
//
//void Mesh::SetupMesh()
//{
//	// create buffers/arrays
//	glGenVertexArrays(1, &m_VAO);
//	glGenBuffers(1, &m_VBO);
//	glGenBuffers(1, &m_IBO);
//	//m_VAO.Generate();
//	//m_VBO.Generate();
//	//m_IBO.Generate();
//
//	glBindVertexArray(m_VAO);
//	//m_VAO.Bind();
//
//	// load data into vertex buffers
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	//m_VBO.Bind();
//
//	// A great thing about structs is that their memory layout is sequential for all its items.
//	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
//	// again translates to 3/2 floats which translates to a byte array.
//	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//	//m_IBO.Bind();
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
//
//	// set the vertex attribute pointers
//	// vertex Positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	// vertex normals
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
//	// vertex texture coords
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvs));
//
//	glBindVertexArray(0);
//}