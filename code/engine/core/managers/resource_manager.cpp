#include "resource_manager.hpp"

ResourceManager::ResourceManager()
{

}

void ResourceManager::LoadBatchOfTextures(POINT::hashmap<std::string, float> batch_map)
{
	for (const auto& key_pair : batch_map)
	{
		std::string texture_filename = key_pair.first;
		float texture_repeat_scale = key_pair.second;

		Texture texture_from_disk = GetTexture(texture_filename);
		available_textures[texture_filename] = texture_from_disk;
	}
}

void ResourceManager::LoadBatchOfModels(POINT::vector<std::string> batch_vector)
{
	for (const auto& filename : batch_vector)
	{
		std::string model_filename = filename;

		Model model_from_disk = GetModel(model_filename);
		available_models[model_filename] = model_from_disk;
	}
}



Texture ResourceManager::GetTexture(std::string texture_filename)
{
	if (available_textures.find(texture_filename) != available_textures.end())
	{
		std::cout << "Texture found" << std::endl;
		return available_textures.at(texture_filename);
	
	}
	else
	{
		std::cout << "Texture not found, loading from disk" << std::endl;
		Texture texture_from_disk = LoadTextureFromDisk(texture_filename);
		available_textures[texture_filename] = texture_from_disk;
		return texture_from_disk;
	}
}

Model ResourceManager::GetModel(std::string model_filename)
{
	if (available_models.find(model_filename) != available_models.end())
	{
		std::cout << "Model found" << std::endl;
		return available_models.at(model_filename);
	}
	else
	{
		std::cout << "Model not found, loading from disk" << std::endl;
		Model model_from_disk = LoadModelFromDisk(model_filename);
		available_models[model_filename] = model_from_disk;
		return model_from_disk;	
	}
}


Model ResourceManager::LoadModelFromDisk(std::string filename)
{
	Model new_model;

	std::string filepath = "../../../assets/models/" + filename;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Assimp error" << importer.GetErrorString() << std::endl;
	}

	for (int m = 0; m < scene->mNumMeshes; m++)
	{
		// For each mesh in glb scene:
		aiMesh* mesh = scene->mMeshes[m];

		Mesh new_mesh;


		// For each vertice in the mesh:
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex new_vertex;

			new_vertex.position.x = mesh->mVertices[i].x;
			new_vertex.position.y = mesh->mVertices[i].y;
			new_vertex.position.z = mesh->mVertices[i].z;

			if (mesh->mTextureCoords[0])
			{
				new_vertex.texture_coordinates = glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z);
			}
			else
			{
				new_vertex.texture_coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			new_vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);

			new_mesh.vertices.push_back(new_vertex);
		}

		// For each face of the mesh:
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				new_mesh.indices.push_back(face.mIndices[j]);
			}
		}
		
		new_model.mesh_data.push_back(new_mesh);
	}
	return new_model;
}



Texture ResourceManager::LoadTextureFromDisk(std::string texture_filename)
{
	std::string full_texture_path = "../../../assets/textures/" + texture_filename;
	
	unsigned int textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	// Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels, width, height;
	unsigned char* data = stbi_load(full_texture_path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Texture failed to load" << std::endl;
	}

	//std::cout << "Texture loaded!" << std::endl;

	stbi_image_free(data);

	Texture texture;

	texture.texture_id = textureID;

	return texture;
}

