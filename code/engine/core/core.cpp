#include "core.hpp"

Core::Core(EngineState& engine_state)
	:
	engine_state(engine_state),
	program_name("Engine"),
	init_program_width(1920),
	init_program_height(1080),
	window_manager(WindowManager(program_name, init_program_width, init_program_height))
{
	int ammount = 3000;

	memory_manager.PrealocComponentData(world.component_store.transforms, ammount);
	memory_manager.PrealocComponentData(world.component_store.velocities, ammount);
	memory_manager.PrealocComponentData(world.component_store.cameras, ammount);
	memory_manager.PrealocComponentData(world.component_store.models, ammount);

	memory_manager.PrealocVector(world.element_registry.entities_w_movement, ammount);
	memory_manager.PrealocVector(world.element_registry.entities_w_model, ammount);
	memory_manager.PrealocVector(world.element_registry.entities_w_camera, ammount);

	memory_manager.PrealocHashmap(world.entities_map, ammount);

	InitializeOpenGL();
	InitializeGLAD();
	UpdateConfigs();

	world.time_state.last_time = std::chrono::high_resolution_clock::now();
}

void Core::Timestep()
{
	world.time_state.current_time = std::chrono::high_resolution_clock::now();
	world.time_state.delta_time = std::chrono::duration<float>(world.time_state.current_time - world.time_state.last_time).count();
	world.time_state.last_time = world.time_state.current_time;
}

void Core::UpdateConfigs()
{
	// Vsync
	if (configs.vsync)
	{
		glfwSwapInterval(1);
		SDL_GL_SetSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
		SDL_GL_SetSwapInterval(0);
	}

	// Depth tests
	if (configs.gl_depth_test)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

Core::~Core()
{
	SDL_DestroyWindow(window_manager.window.SDLwindow);
}


