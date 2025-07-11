#pragma once

#include "components.hpp"
#include "defs.hpp"

#include "memory_manager.hpp"
#include "entities_manager.hpp"
#include "materials_system.hpp"
#include "input_system.hpp"
#include "renderer.hpp"
#include "camera_system.hpp"
#include "movement_system.hpp"
#include "window_manager.hpp"
#include "configs.hpp"

#include "../utils/u_initialization.hpp"
#include "../utils/u_components.hpp"


class Core
{
public:

	int init_program_width;
	int init_program_height;

	EngineState& engine_state;

	// Game metadata
	std::string program_name;

	// State
	World world;

	// Configs
	RenderConfigs configs;

	// Managers
	MemoryManager	memory_manager;
	WindowManager	window_manager;
	ResourceManager resource_manager;
	EntitiesManager	entities_manager;

	// Systems
	MaterialsSystem materials_system;
	InputSystem		input_system;
	MovementSystem	ECS_movement_system;
	CameraSystem	ECS_camera_system;

	// Engines
	Renderer	renderer;


	Core(EngineState& engine_state);
	
	void UpdateConfigs();
	void Timestep();

	
	~Core();
};







