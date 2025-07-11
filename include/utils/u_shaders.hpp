#pragma once

#include "../../include/headers/defs.hpp"

inline std::string load_shader_src(ShaderType shader_type, std::string shader_filename)
{
	std::string shader_type_to_string = "";

	switch (shader_type)
	{
		case SHDR_VERTEX:
			shader_type_to_string = "vert";
			break;
		case SHDR_FRAGMENT:
			shader_type_to_string = "frag";
			break;
		default:
			std::cerr << "Invalid shader type" << std::endl;
			break;
	}

	std::string shader_file_path = "../../../assets/shaders/" + shader_type_to_string + "/" + shader_filename;
	std::string shader_file_src = "";
	std::string line = "";
	
	std::ifstream shader_file(shader_file_path);
	if (shader_file.is_open())
	{
		while (std::getline(shader_file, line))
		{
			shader_file_src += line + '\n';
		}
		shader_file.close();
	}

	if (std::filesystem::exists(shader_file_path))
	{
		std::cout << ".frag file exists at path [" << shader_file_path << "]" << std::endl;
	}
	else 
	{
		std::cerr << "No.frag file exists at path[" << shader_file_path << "]" << std::endl;
	}

	std::cout << "Contents of shader: [" << shader_file_src << "]" << std::endl;

	return shader_file_src;
}

inline ShaderID compile_shader(ShaderType shader_type, std::string shader_file_src)
{
	std::unordered_map<int, GLenum> shader_type_map;

	shader_type_map[SHDR_VERTEX] = GL_VERTEX_SHADER;
	shader_type_map[SHDR_FRAGMENT] = GL_FRAGMENT_SHADER;

	const char* c_shader_file_src = shader_file_src.c_str();

	int success;
	char infoLog[512];

	ShaderID shader_id; 
	shader_id = glCreateShader(shader_type_map[shader_type]); // Returns ID for shader on GPU.

	glShaderSource(shader_id, 1, &c_shader_file_src, NULL); // Load shader source code to object.

	// COMPILATION AND ERROR HANDLING 
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cerr << "ERROR S-1: Shader compilation failed" << infoLog << std::endl;
	}

	std::cout << "shader compiled succesfully" << std::endl;

	return shader_id;
}


