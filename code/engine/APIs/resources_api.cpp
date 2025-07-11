#include "resources_api.hpp"


ResourcesAPI::ResourcesAPI(Core& core) : core(core)
{

}

Texture ResourcesAPI::GetTexture(std::string texture_filename)
{
	Texture texture = core.resource_manager.GetTexture(texture_filename);
	return texture;
}

Model ResourcesAPI::GetModel(std::string model_filename)
{
	Model model = core.resource_manager.GetModel(model_filename);
	return model;
}

void ResourcesAPI::SubmitTextureBatch(POINT::hashmap<std::string, float> batch_map)
{
	core.resource_manager.LoadBatchOfTextures(batch_map);
}

void ResourcesAPI::SubmitModelsBatch(POINT::vector<std::string> batch_vector)
{
	core.resource_manager.LoadBatchOfModels(batch_vector);
}


