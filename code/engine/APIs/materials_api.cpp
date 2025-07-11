#include "materials_api.hpp"


MaterialsAPI::MaterialsAPI(Core& core) : core(core)
{

}

Material MaterialsAPI::CreateMaterial(std::string vertex_shader_filename, std::string fragment_shader_filename)
{
		auto material = core.materials_system.CreateMaterial(
		core.world, 
		core.world.render_state, 
		vertex_shader_filename, 
		fragment_shader_filename
	);

	return material;
}

Material MaterialsAPI::CreateMaterial(std::string vertex_shader_filename, std::string fragment_shader_filename, Texture texture, float texture_repeat_scale)
{
	auto material = core.materials_system.CreateMaterial(
		core.world, 
		core.world.render_state, 
		vertex_shader_filename, 
		fragment_shader_filename, 
		texture, 
		texture_repeat_scale
	);

	return material;
}