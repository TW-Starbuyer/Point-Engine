#include "editor.hpp"



Editor::Editor(Core& core)
{
	InitializeUI(core);
	StyleUI();	
}

void Editor::InitializeUI(Core& core)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	SDL_Window* SDLwindow = core.window_manager.window.SDLwindow;
	SDL_GLContext GLContext = core.window_manager.window.GLContext;

	ImGui_ImplSDL3_InitForOpenGL(SDLwindow, GLContext);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Editor::Update(Core& core, EngineState& engine_state)
{
	UpdateUI(core, engine_state);
	DrawUI();
}

void Editor::StyleUI()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 black = ImVec4(0.173, 0.157, 0.149, 255);

	style.Colors[ImGuiCol_TitleBgActive] = black;
	style.Colors[ImGuiCol_Border] = ImVec4(0.831, 0.831, 0.831, 255);

	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.169, 0.169, 0.169, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.341, 0.341, 0.341, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.500, 0.500, 0.500, 255);

	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.882, 0.851, 0.616, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.882, 0.851, 0.616, 255);

	style.Colors[ImGuiCol_Button] = ImVec4(0.169, 0.169, 0.169, 255); 	
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.341, 0.341, 0.341, 255);

	style.WindowRounding = 2.0f;
}

void Editor::UpdateUI(Core& core, EngineState& engine_state)
{
	camera_component& active_camera_cmpt = GetComponent<camera_component>(core.world.component_store.cameras, core.world.render_state.active_camera_entity_id);
	velocity_component& active_velocity_cmpt = GetComponent<velocity_component>(core.world.component_store.velocities, core.world.render_state.active_camera_entity_id);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(1920, 80), ImGuiCond_Always);

	ImGui::Begin("Point Engine", nullptr, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Engine"))
		{
			if (ImGui::MenuItem("Quit")) 
			{ 
				*engine_state.engine_quit = true; 
			}

			if (ImGui::MenuItem("Restart")) 
			{ 
				
			}

			ImGui::EndMenu();
		}
	
		if (ImGui::BeginMenu("World"))
		{
			if (ImGui::MenuItem("Open")) 
			{ 
				std::cout << "test" << std::endl; 
			}

			if (ImGui::MenuItem("Save")) 
			{ 
				std::cout << "test" << std::endl; 
			}
			
			if (ImGui::MenuItem("Save As")) 
			{
				std::cout << "test" << std::endl; 
			}

			ImGui::EndMenu();


		}
		ImGui::EndMenuBar();

	}
	ImGui::End();	

	// Performance settings menu


	ImGui::SetNextWindowPos(ImVec2(1500, 100), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 45), ImGuiCond_Always);

	ImGui::Begin("Performance Data");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(1500, 155), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 90), ImGuiCond_Always);

	ImGui::Begin("Graphics Settings");
	ImGui::Checkbox("VSync", &core.configs.vsync);
	ImGui::Checkbox("Depth testing", &core.configs.gl_depth_test);
	ImGui::End();

	// Camera settings menu
	ImGui::SetNextWindowPos(ImVec2(1500, 255), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 180), ImGuiCond_Always);

	ImGui::Begin("Active Camera Settings");
	ImGui::SliderFloat("FOV", &(active_camera_cmpt.fov), 25.0f, 140.0f);

	ImGui::BeginTable("Cameras Table", 1);
	{
		ImGui::TableSetupColumn("NAME");
		/*ImGui::TableSetupColumn("MANAGE");*/

		ImGui::TableHeadersRow();

		for (EntityID entity_id : core.world.element_registry.entities_w_camera)
		{
			std::string entity_id_str = "Camera | EntityID = " + std::to_string(entity_id);
			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			if (ImGui::Button(entity_id_str.c_str()))
			{
				core.world.render_state.active_camera_entity_id = entity_id;
			}
		}
		ImGui::EndTable();
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(1500, 445), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 90), ImGuiCond_Always);

	ImGui::Begin("Active Velocity Settings");
	ImGui::SliderFloat("Forward Speed", &(active_velocity_cmpt.forward_speed), 0.1f, 40.0f);
	ImGui::SliderFloat("Backward Speed", &(active_velocity_cmpt.backwards_speed), 0.1f, 40.0f);
	ImGui::SliderFloat("Strafe Speed", &(active_velocity_cmpt.strafe_speed), 0.1f, 40.0f);
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(1500, 545), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 275), ImGuiCond_Always);

	ImGui::Begin("Entities Table");
	ImGui::BeginTable("Entities Table", 4);
	{
		ImGui::TableSetupColumn("ID");
		ImGui::TableSetupColumn("TYPE");
		ImGui::TableSetupColumn("TRANSFORM");
		ImGui::TableSetupColumn("DELETE");

		ImGui::TableHeadersRow();

		static EntityID active_object = -1;

		for (const auto& key_pair : core.world.entities_map)
		{
			std::string archetype = GetEntityArchetype(core.world, key_pair.first);

			transform_component& transform_cmpt = GetComponent<transform_component>(core.world.component_store.transforms, key_pair.first);
			velocity_component& velocity_cmpt = GetComponent<velocity_component>(core.world.component_store.velocities, key_pair.first);

			float ui_editor_move_entity_speed_x = 1;
			float ui_editor_move_entity_speed_y = 1;
			float ui_editor_move_entity_speed_z = 1;

			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			ImGui::Text("%d", key_pair.first);

			ImGui::TableNextColumn();
			ImGui::Text("%s", archetype.c_str());

			ImGui::TableNextColumn();
			std::string unique_label_transform = "TRANSFORM##TRANSFORMS_LABEL" + std::to_string(key_pair.first);
			if (ImGui::Button(unique_label_transform.c_str()))
			{
				active_object = key_pair.first;
				ImGui::OpenPopup("ElementPopup");

			}

			ImGui::TableNextColumn();
			std::string unique_label_delete = "DELETE##DELETE_LABEL" + std::to_string(key_pair.first);
			if (ImGui::Button(unique_label_delete.c_str()))
			{
				
				
			}


			
		}

		if (ImGui::BeginPopup("ElementPopup"))
		{
			if (active_object != -1)
			{
				transform_component& transform_cmpt = GetComponent<transform_component>(core.world.component_store.transforms, active_object);

					ImGui::TableNextColumn();

					if (ImGui::DragFloat("position x", &(transform_cmpt.position.x), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					if (ImGui::DragFloat("scale x", &(transform_cmpt.scale.x), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					
					if (ImGui::DragFloat("rotation x", &(transform_cmpt.rotation.x), 1.0, 0.0f, 0.0, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					ImGui::TableNextColumn();


					if (ImGui::DragFloat("position y", &(transform_cmpt.position.y), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					if (ImGui::DragFloat("scale y", &(transform_cmpt.scale.y), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					};

					if (ImGui::DragFloat("rotation y", &(transform_cmpt.rotation.y), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					ImGui::TableNextColumn();

					if (ImGui::DragFloat("position z", &(transform_cmpt.position.z), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}

					if (ImGui::DragFloat("scale z", &(transform_cmpt.scale.z), 1.0, 0.0f, 0.0f, "%.5f"))
					{
						transform_cmpt.has_changed = 1;
					}
				
			}
			ImGui::EndPopup();
		}
		ImGui::EndTable();
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(200, 100), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Always);

	ImGui::Begin("Scene Viewer");

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		core.world.render_state.scene_window_active = true;
	} 
		
	float scene_window_width = ImGui::GetContentRegionAvail().x;
	float scene_window_height = ImGui::GetContentRegionAvail().y;

	//core.world.render_state.active_framebuffer = core.renderer.CreateFramebuffer(scene_window_width, scene_window_height);
	core.renderer.ResizeFramebuffer(core.world.render_state.active_framebuffer, scene_window_width, scene_window_height);
	
	core.renderer.BindFramebuffer(core.world.render_state.active_framebuffer);
	core.renderer.Predraw(core.world);
	core.renderer.Draw(core.world, core.world.render_state, core.window_manager.window, core.configs, scene_window_width, scene_window_height);
	core.renderer.UnbindFramebuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		
	ImGui::Image((ImTextureID)core.world.render_state.active_framebuffer.texture_id, ImVec2(scene_window_width, scene_window_height), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void Editor::DrawUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}