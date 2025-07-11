#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../utils/u_tags.hpp"
#include "../utils/u_models.hpp"
#include "../utils/u_components.hpp"
#include "../utils/u_serialization.hpp"
#include "../utils/u_textures.hpp"

#include "../third_party/stb_image/stb_image.h"


class ResourceManager
{
	public:
		ResourceManager();
		
	/*	void CreateNewWorld(std::string project_name, std::string world_filename);
		void LoadWorldData(World& world, std::string project_name, std::string world_filename);
		void SaveWorldData(World& world, std::string project_name, std::string world_filename);*/

		void LoadBatchOfTextures(POINT::hashmap<std::string, float> batch_map);
		void LoadBatchOfModels(POINT::vector<std::string> batch_vector);



		Texture GetTexture(std::string texture_filename);
		Model GetModel(std::string model_filename);
		//ShaderID GetShader(std::string shader_filename);

	private:
		POINT::hashmap<std::string, Texture> available_textures;
		POINT::hashmap<std::string, Model> available_models;
		POINT::hashmap<std::string, ShaderID> available_shaders;

		// You should always check if texture is available in resource manager first, if it's not there then the manager will fetch from disk.
		Texture LoadTextureFromDisk(std::string texture_filename);
		Model LoadModelFromDisk(std::string model_filename);
};
