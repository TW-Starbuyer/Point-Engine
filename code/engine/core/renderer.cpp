#include "renderer.hpp"

Renderer::Renderer()
{

}

Framebuffer Renderer::CreateFramebuffer(int width, int height)
{
	Framebuffer fb;
	glGenFramebuffers(1, &fb.FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, fb.FBO);

	glGenTextures(1, &fb.texture_id);
	glBindTexture(GL_TEXTURE_2D, fb.texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb.texture_id, 0);

	glGenRenderbuffers(1, &fb.RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, fb.RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb.RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return fb;
}

void Renderer::ResizeFramebuffer(Framebuffer& fb, int width, int height)
{
	BindFramebuffer(fb);

	glBindTexture(GL_TEXTURE_2D, fb.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb.texture_id, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, fb.RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb.RBO);

	UnbindFramebuffer();
}

void Renderer::BindFramebuffer(Framebuffer fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.FBO);
}

void Renderer::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Predraw(World& world)
{
	glm::vec4 background_color = glm::vec4(0.161, 0.161, 0.153, 1);
	glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(
	World& world, 
	RenderState& render_state, 
	Window& window, 
	RenderConfigs& configs, 
	std::optional<int> width = std::nullopt,
	std::optional<int> height = std::nullopt)
{
	int window_width = 0;
	int window_height = 0;

	if (!width || !height)
	{
		std::tuple<int, int> window_dimensions = GetWindowDimensions(window);
		window_width = std::get<0>(window_dimensions);
		window_height = std::get<1>(window_dimensions);
	}
	else
	{
		window_width = *width;
		window_height = *height;
	}

	if (render_state.scene_window_active)
	{
		SDL_SetWindowRelativeMouseMode(window.SDLwindow, true);
	}

	else if (!render_state.scene_window_active)
	{
		SDL_SetWindowRelativeMouseMode(window.SDLwindow, false);
	}

	glViewport(0, 0, window_width, window_height);
	
	camera_component& active_camera_cmpt = GetComponent<camera_component>(world.component_store.cameras, render_state.active_camera_entity_id);
	
	for (EntityID entity_id : world.element_registry.entities_w_model)
	{
	
		model_component& model_cmpt = GetComponent<model_component>(world.component_store.models, entity_id);	
		transform_component& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, entity_id);

		float vector_sum = transform_cmpt.scale.x + transform_cmpt.scale.y + transform_cmpt.scale.z;
		bool has_changed_condition = model_cmpt.has_changed == 1 || transform_cmpt.has_changed == 1;


		if (has_changed_condition)
		{
			model_cmpt.model.model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform_cmpt.position));															// Translate model to world space.
			model_cmpt.model.model_matrix = glm::rotate(model_cmpt.model.model_matrix, glm::radians(transform_cmpt.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));	
			model_cmpt.model.model_matrix = glm::rotate(model_cmpt.model.model_matrix, glm::radians(transform_cmpt.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));	
			model_cmpt.model.model_matrix = glm::rotate(model_cmpt.model.model_matrix, glm::radians(transform_cmpt.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));		// Rotate model matrix.
			model_cmpt.model.model_matrix = glm::scale(model_cmpt.model.model_matrix, glm::vec3(transform_cmpt.scale.x, transform_cmpt.scale.y, transform_cmpt.scale.z));

			transform_cmpt.has_changed = 0;
		}

		for (Mesh& mesh : model_cmpt.model.mesh_data)
		{
			if (mesh.material.shader_program_id > 0)
			{
				glUseProgram(mesh.material.shader_program_id);

				render_state.model_matrix_location = glGetUniformLocation(mesh.material.shader_program_id, "u_ModelMatrix");
				render_state.view_matrix_location = glGetUniformLocation(mesh.material.shader_program_id, "u_ViewMatrix");
				render_state.projection_location = glGetUniformLocation(mesh.material.shader_program_id, "u_Projection");
				render_state.texture_repeat_scale_location = glGetUniformLocation(mesh.material.shader_program_id, "u_TextureRepeatScale");
			
				glUniformMatrix4fv(render_state.model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_cmpt.model.model_matrix));
				glUniformMatrix4fv(render_state.projection_location, 1, GL_FALSE, glm::value_ptr(active_camera_cmpt.projection_matrix));
				glUniformMatrix4fv(render_state.view_matrix_location, 1, GL_FALSE, glm::value_ptr(active_camera_cmpt.view_matrix));

			}

			for (int i = 0; i < mesh.material.textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, mesh.material.textures.at(i).texture_id);
				std::string uniform_name = "texture1";
				glUniform1i(glGetUniformLocation(mesh.material.shader_program_id, uniform_name.c_str()), i);
				glUniform1f(render_state.texture_repeat_scale_location, mesh.material.textures.at(i).texture_repeat_scale);
			}

			glBindVertexArray(mesh.VAO);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		}
	}
}

void Renderer::SetViewport(float vp_width, float vp_height)
{
	glViewport(0, 0, vp_width, vp_height);
}
