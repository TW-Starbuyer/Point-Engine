#pragma once

#include "defs.hpp"
#include "core.hpp"


class MaterialsAPI
{
	public:
		MaterialsAPI(Core& core);
		Material CreateMaterial(std::string vertex_shader_filename, std::string fragment_shader_filename);
		Material CreateMaterial(std::string vertex_shader_filename, std::string fragment_shader_filename, Texture texture, float texture_repeat_scale);

	private:
		Core& core;
};