#include "input_system.hpp"

InputSystem::InputSystem() {}

void InputSystem::Update(EngineState& engine_state, World& world, Window& window, RenderConfigs& configs)
{
	transform_component& transform_cmpt = GetComponent<transform_component>(world.component_store.transforms, world.render_state.active_camera_entity_id);
	velocity_component& velocity_cmpt = GetComponent<velocity_component>(world.component_store.velocities, world.render_state.active_camera_entity_id);
	camera_component& camera_cmpt = GetComponent<camera_component>(world.component_store.cameras, world.render_state.active_camera_entity_id);
	
	float& delta_time = world.time_state.delta_time;

	glm::vec3 locked_direction = glm::normalize(glm::vec3(camera_cmpt.direction.x, camera_cmpt.direction.y, 0.0f));
	glm::vec3 left = glm::normalize(glm::cross(camera_cmpt.up, camera_cmpt.direction));
	glm::vec3 right = glm::normalize(glm::cross(camera_cmpt.direction, camera_cmpt.up));

	auto key_states = SDL_GetKeyboardState(NULL);
	
	if (camera_cmpt.freelook == false)
	{
		if (key_states[SDL_SCANCODE_W])
		{
			transform_cmpt.position += locked_direction * velocity_cmpt.forward_speed * delta_time;
			velocity_cmpt.has_changed = 1;

		}

		if (key_states[SDL_SCANCODE_A])
		{
			transform_cmpt.position += left * velocity_cmpt.strafe_speed * delta_time;
			velocity_cmpt.has_changed = 1;
		}

		if (key_states[SDL_SCANCODE_S])
		{
			transform_cmpt.position -= locked_direction * velocity_cmpt.backwards_speed * delta_time;
			velocity_cmpt.has_changed = 1;

		}

		if (key_states[SDL_SCANCODE_D])
		{
			transform_cmpt.position += right * velocity_cmpt.strafe_speed * delta_time;
			velocity_cmpt.has_changed = 1;
		}
	}
	
	else if (camera_cmpt.freelook == true)
	{
		if (key_states[SDL_SCANCODE_W])
		{
			/*velocity_cmpt.velocity += camera_cmpt.direction * velocity_cmpt.forward_speed * delta_time;*/
			transform_cmpt.position += camera_cmpt.direction * velocity_cmpt.forward_speed * delta_time;

			std::cout << transform_cmpt.position.z << std::endl;
			velocity_cmpt.has_changed = 1;

		}

		if (key_states[SDL_SCANCODE_A])
		{
			glm::vec3 left_vector = glm::normalize(glm::cross(camera_cmpt.direction, camera_cmpt.up));
			transform_cmpt.position -= left_vector * velocity_cmpt.strafe_speed * delta_time;
			velocity_cmpt.has_changed = 1;
		}

		if (key_states[SDL_SCANCODE_S])
		{
			transform_cmpt.position -= camera_cmpt.direction * velocity_cmpt.backwards_speed * delta_time;
			std::cout << transform_cmpt.position.z << std::endl;
			velocity_cmpt.has_changed = 1;

		}

		if (key_states[SDL_SCANCODE_D])
		{
			glm::vec3 right_vector = glm::normalize(glm::cross(camera_cmpt.direction, camera_cmpt.up));
			transform_cmpt.position += right_vector * velocity_cmpt.strafe_speed * delta_time;
			velocity_cmpt.has_changed = 1;
		}
	}


	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		ImGui_ImplSDL3_ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_EVENT_KEY_DOWN:
		{
			switch (event.key.key)
			{
				case SDLK_F7:
					*engine_state.engine_quit = true;
					break;

				case SDLK_E:
					world.render_state.scene_window_active = !(world.render_state.scene_window_active);
					std::cout << "CAMERA FREELOOK STATE AFTER E" << camera_cmpt.freelook << std::endl;
					break;

				#ifndef NDEBUG
				case SDLK_R:
					*engine_state.editor_mode = !(*engine_state.editor_mode);
					std::cout << "CAMERA FREELOOK STATE AFTER R" << camera_cmpt.freelook << std::endl;
					break;
				#endif		
			}
			break;
		}
		case SDL_EVENT_MOUSE_MOTION:
		{
			if (!world.render_state.scene_window_active)
			{
				SDL_SetWindowRelativeMouseMode(window.SDLwindow, false);
			}

			else if (world.render_state.scene_window_active)
			{
				SDL_SetWindowRelativeMouseMode(window.SDLwindow, true);
				float sensitivity = 0.1f;

				float x_mouse_offset = event.motion.xrel * sensitivity;
				float y_mouse_offset = event.motion.yrel * sensitivity;

				camera_cmpt.yaw -= x_mouse_offset;
				camera_cmpt.pitch -= y_mouse_offset;

				if (camera_cmpt.pitch > 89.0f)
				{
					camera_cmpt.pitch = 89.0f;
				}

				if (camera_cmpt.pitch < -89.0f)
				{
					camera_cmpt.pitch = -89.0f;
				}

				glm::vec3 updated_direction;

				updated_direction.x = cos(glm::radians(camera_cmpt.yaw)) * cos(glm::radians(camera_cmpt.pitch));
				updated_direction.z = sin(glm::radians(camera_cmpt.pitch));
				updated_direction.y = sin(glm::radians(camera_cmpt.yaw)) * cos(glm::radians(camera_cmpt.pitch));

				camera_cmpt.direction = glm::normalize(updated_direction);
				break;
			}
		}

		default:
			break;

		}
	}

};