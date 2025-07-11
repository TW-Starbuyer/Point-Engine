#include "materials_system.hpp"


MaterialsSystem::MaterialsSystem() {}

void MaterialsSystem::Update()
{
	
}

Material MaterialsSystem::CreateMaterial(World& world, RenderState& render_state, std::string vertex_shader_filename, std::string fragment_shader_filename, Texture texture, float texture_repeat_scale)
{
	texture.texture_repeat_scale = texture_repeat_scale;

	Material material;

	AddTextureToMaterial(world, material, texture);

	ShaderID vertex_shader_id = CreateShader(world, SHDR_VERTEX, vertex_shader_filename);
	ShaderID fragment_shader_id = CreateShader(world, SHDR_FRAGMENT, fragment_shader_filename);
	ShaderID shader_program_id = CreateShaderProgram(world, render_state, vertex_shader_id, fragment_shader_id);

	AddShaderToMaterial(world, material, shader_program_id);

	return material;
}

Material MaterialsSystem::CreateMaterial(World& world, RenderState& render_state, std::string vertex_shader_filename, std::string fragment_shader_filename)
{
	Material material;

	ShaderID vertex_shader_id = CreateShader(world, SHDR_VERTEX, vertex_shader_filename);
	ShaderID fragment_shader_id = CreateShader(world, SHDR_FRAGMENT, fragment_shader_filename);
	ShaderID shader_program_id = CreateShaderProgram(world, render_state, vertex_shader_id, fragment_shader_id);

	AddShaderToMaterial(world, material, shader_program_id);

	return material;

}


ShaderID MaterialsSystem::CreateShader(World& world, ShaderType shader_type, std::string shader_filename) 
{
	std::string shader_file_src = load_shader_src(shader_type, shader_filename);
	
	ShaderID shader = compile_shader(shader_type, shader_file_src);
	
	return shader;
};


GLint MaterialsSystem::CreateShaderProgram(World& world, RenderState& render_state, ShaderID& vertex_shader, ShaderID& fragment_shader)
{
	GLint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glValidateProgram(shader_program);


	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}



void MaterialsSystem::AddShaderToMaterial(World& world, Material& mat, ShaderID& shader_program_id) 
{
	mat.shader_program_id = shader_program_id;
	/*std::cout << "Added shader program to material" << std::endl;*/
};

void MaterialsSystem::AddTextureToMaterial(World& world, Material& mat, Texture& texture)
{
	if (texture.texture_id >= 0)
	{
		mat.textures.push_back(texture);
	}
	//std::cout << "Added texture to material" << std::endl;
}

void MaterialsSystem::ApplyMaterialToEachMeshInModel(World& world, Material& mat, EntityID entity_id)
{
	model_component& model_cmpt = GetComponent<model_component>(world.component_store.models, entity_id);

	for (Mesh& mesh : model_cmpt.model.mesh_data)
	{
		mesh.material = mat;
		//std::cout << "material applied to component" << std::endl;
	}
}

