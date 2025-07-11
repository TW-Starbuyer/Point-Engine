#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"
#include "../utils/u_shaders.hpp"
#include "../utils/u_textures.hpp"

#include "../utils/u_components.hpp"

class MaterialsSystem
{
	public:
		MaterialsSystem();

		void Update();

	
		Material CreateMaterial(World& world, RenderState& render_state, std::string vertex_shader_filename, std::string fragment_shader_filename, Texture texture, float texture_repeat_scale);
		Material CreateMaterial(World& world, RenderState& render_state, std::string vertex_shader_filename, std::string fragment_shader_filename);
		
		ShaderID CreateShader(World& world, ShaderType shader_type, std::string shader_filename);
		GLint CreateShaderProgram(World& world, RenderState& render_state, ShaderID& vertex_shader, ShaderID& fragment_shader);

		void AddShaderToMaterial(World& world, Material& mat, ShaderID& shader_program_id);
		void AddTextureToMaterial(World& world, Material& mat, Texture& texture);

		void ApplyMaterialToEachMeshInModel(World& world, Material& mat, EntityID entity_id);
};