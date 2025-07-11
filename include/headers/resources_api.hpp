#pragma once

#include "defs.hpp"
#include "core.hpp"


class ResourcesAPI
{
	public:
		ResourcesAPI(Core& core);

		Texture GetTexture(std::string texture_filename);
		Model GetModel(std::string model_filename);
	

		void SubmitTextureBatch(POINT::hashmap<std::string, float> batch_map);
		void SubmitModelsBatch(POINT::vector<std::string> batch_vector);

	private:
		Core& core;
};

