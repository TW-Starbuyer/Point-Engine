#pragma once

#include "world_api.hpp"
#include "resources_api.hpp"
#include "materials_api.hpp"

class Interface
{
	public:

		Interface(Core& core);

		WorldAPI		POINT_world;
		MaterialsAPI	POINT_materials;
		ResourcesAPI	POINT_resources;

};