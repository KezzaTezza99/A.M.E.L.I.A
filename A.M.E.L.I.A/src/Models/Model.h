//#ifndef __MODEL__
//#define __MODEL__
//#include <glew.h>
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <stb_image.h>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <map>
//#include <vector>
//#include "Mesh.h"
//#include "../Loaders/Shader.h"
//
//class Model
//{
//private:
//	//Model Datas
//	std::vector<Mesh> m_meshes;
//	std::vector<Texture> m_loadedTextures;
//	std::string m_fileDir;
//
//	void LoadModel(std::string filePath);
//	void ProcessNode(aiNode* node, const aiScene* scene);
//	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
//	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
//public:
//	Model(GLchar* filePath);
//	void Draw(Shader shader);
//
//	//Helpful method for loading a texture from a file
//	GLint TextureFromFile(const char* filePath, std::string fileDirectory);
//};
//#endif // !__MODEL__