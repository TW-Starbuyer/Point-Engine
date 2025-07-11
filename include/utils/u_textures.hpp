#pragma once

#include "../third_party/stb_image/stb_image.h"


inline TextureID create_texture(int width, int height, int nrChannels, unsigned char* image_data)
{
		unsigned int texture_id;

		glGenTextures(1, &texture_id);

		glBindTexture(GL_TEXTURE_2D, texture_id);

		// Texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Texture mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint internal_format = GL_RGB;
		GLenum data_format = GL_RGB;

		if (nrChannels == 4)
		{
			internal_format = GL_RGBA;
			data_format = GL_RGBA;
		}
		else if (nrChannels == 3)
		{
			internal_format = GL_RGB;
			data_format = GL_RGB;

		}
		else if (nrChannels == 1)
		{
			internal_format = GL_RED;
			data_format = GL_RED;
		}

		glTexImage2D(GL_TEXTURE_2D, 0,  internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image_data);
		

		glGenerateMipmap(GL_TEXTURE_2D);


		return texture_id;
}

inline TextureID load_texture(std::string texture_filename)
{
	
	std::string full_texture_path = "../../../assets/textures/" + texture_filename;
	
	TextureID texture_id = -1;
	int nrChannels, width, height;
	unsigned char* image_data = stbi_load(full_texture_path.c_str(), &width, &height, &nrChannels, 0);

	if (image_data)
	{
		texture_id = create_texture(width, height, nrChannels, image_data);
	}
	else
	{
		std::cerr << "Texture failed to load" << std::endl;
	}

	std::cout << "Texture loaded!" << std::endl;


	return texture_id;
}

