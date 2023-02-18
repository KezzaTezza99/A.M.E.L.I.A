//#ifndef __MESH__
//#define __MESH__
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <string>
//#include <vector>
//#include "../Loaders/Shader.h"
//#include "../Loaders/Image.h"
//#include "../buffers/IndexBuffer.h"
//#include "../buffers/VertexArray.h"
//#include "../buffers/VertexBuffer.h"
//
////Stores vertex info
//struct Vertex 
//{
//	glm::vec3 position;
//	glm::vec3 normals;
//	glm::vec2 uvs;
//};
//
//struct Texture
//{
//	unsigned int id;
//	std::string type;
//	std::string path;
//};
//
//class Mesh
//{
//public:
//	//Mesh Data
//	std::vector<Vertex> m_vertices;
//	std::vector<unsigned int> m_indices;
//	std::vector<Texture> m_textures;
//	
//	//Render Data
//	//VertexArray m_VAO;
//	//VertexBuffer m_VBO;
//	//IndexBuffer m_IBO;
//	unsigned int m_VAO, m_VBO, m_IBO;
//
//public:
//	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
//	void Draw(Shader &shader);
//	void SetupMesh();
//};
//#endif // !__MESH__