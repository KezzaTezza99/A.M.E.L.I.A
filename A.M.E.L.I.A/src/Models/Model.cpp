//#include "Model.h"
//
//void Model::LoadModel(std::string filePath)
//{
//    std::cout << "Model: (LoadModel)" << std::endl;
//
//    //Using ASSIMP to read the file
//    Assimp::Importer importer;
//    
//    //Importing the whole model as a scene object to access the data
//    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//    //Error checking
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        std::cout << "ERROR: Assimp:: " << importer.GetErrorString() << std::endl;
//        return;
//    }
//
//    //Getting the directory path from the given file path
//    m_fileDir = filePath.substr(0, filePath.find_last_of('/'));
//
//    ProcessNode(scene->mRootNode, scene);
//}
//
//void Model::ProcessNode(aiNode* node, const aiScene* scene)
//{
//    std::cout << "Model: (ProcessNode)" << std::endl;
//
//    //Process all the nodes meshes
//    for (GLuint i = 0; i < node->mNumMeshes; i++)
//    {
//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        m_meshes.push_back(this->ProcessMesh(mesh, scene));
//    }
//
//    //Doing the same but for all the children
//    for (GLuint i = 0; i < node->mNumChildren; i++)
//        this->ProcessNode(node->mChildren[i], scene);
//}
//
//Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
//{
//    std::cout << "Model: (ProcessMesh)" << std::endl;
//
//    //Temp variables that will store the necessary data before transferring to glm
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//
//    //Going through the each of the meshes vertices
//    for (GLuint i = 0; i < mesh->mNumVertices; i++)
//    {
//        //Processing the vertexes position, normals and uvs 
//        Vertex vertex;
//        glm::vec3 vector;
//
//        //Position
//        vector.x = mesh->mVertices[i].x;
//        vector.y = mesh->mVertices[i].y;
//        vector.z = mesh->mVertices[i].z;
//        vertex.position = vector;
//
//        //Normals
//        vector.x = mesh->mNormals[i].x;
//        vector.y = mesh->mNormals[i].y;
//        vector.z = mesh->mNormals[i].z;
//        vertex.normals = vector;
//        
//        //Texture Coords
//        if (mesh->mTextureCoords[0])
//        {
//            glm::vec2 vec;
//            vec.x = mesh->mTextureCoords[0][i].x;
//            vec.y = mesh->mTextureCoords[0][i].y;
//            vertex.uvs = vec;
//        }
//        else
//            vertex.uvs = glm::vec2(0.0f, 0.0f);
//
//        vertices.push_back(vertex);
//    }
//
//    //Now going through all of the meshes faces (triangles) and getting indices
//    for (GLuint i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//
//        for (GLuint j = 0; j < face.mNumIndices; j++)
//            indices.push_back(face.mIndices[j]);
//    }
//
//    //Time to go through materials (if the model has any)
//    if (mesh->mMaterialIndex >= 0)
//    {
//        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//        
//        //Diffuse Maps
//        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//        //Specular Maps
//        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    }
//
//    return Mesh(vertices, indices, textures);
//}
//
//std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
//{
//    std::vector<Texture> textures;
//
//    for (GLuint i = 0; i < material->GetTextureCount(type); i++)
//    {
//        aiString str;
//        material->GetTexture(type, i, &str);
//        GLboolean skip = false;
//
//        //Going through all the loaded textures (if any)
//        for (GLuint j = 0; j < m_loadedTextures.size(); j++)
//        {
//            if (m_loadedTextures[j].path == str.C_Str())
//            {
//                textures.push_back(m_loadedTextures[j]);
//                skip = true;                            //A texture with same location already exists
//                break;
//            }
//        }
//
//        if (!skip)
//        {
//            //Texture(s) haven't been loaded yet so need to load
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), m_fileDir);
//            texture.type = typeName;
//            texture.path = str.C_Str();
//            
//            //Adding the loaded texture to the vector so its not loaded again
//            m_loadedTextures.push_back(texture);
//        }
//    }
//    return textures;
//}
//
//Model::Model(GLchar* filePath)
//{
//    LoadModel(filePath);
//}
//
//void Model::Draw(Shader shader)
//{
//    //Goes through all the meshes and calls their respective Draw function (mesh.cpp)
//    for (GLuint i = 0; i < m_meshes.size(); i++)
//        m_meshes[i].Draw(shader);
//}
//
//GLint Model::TextureFromFile(const char* filePath, std::string fileDirectory)
//{
//    std::string fileName = std::string(filePath);
//    fileName = fileDirectory + '/' + fileName;
//
//    //TODO: Use the actual texture class here
//    GLuint textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
//
//    //Assinging the texture 
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    //Setting the params
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    stbi_image_free(data);
//    
//    return textureID;
//}