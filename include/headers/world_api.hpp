#pragma once

#include "defs.hpp"
#include "core.hpp"


class WorldAPI
{
	public:
		WorldAPI(Core& core);		
		EntityID CreateCamera(CameraType camera_type, glm::vec3 init_position, glm::vec3 rotation);
		EntityID CreateGeometry(std::string model_filename, glm::vec3 init_position, glm::vec3 rotation, glm::vec3 init_scale);
	

	private:
		Core& core;
};