#include "point.hpp"

Point::Point() 
	: 
	core(POINT_engine_state),
	T_editor(core),
	intr(core)
{

}


void Point::Run()
{	
	core.world.render_state.active_framebuffer = core.renderer.CreateFramebuffer(1920, 1080);

	while (!(*POINT_engine_state.engine_quit))
	{
		// Cache references to frequent data access paths
		auto& ref_engine_state = core.engine_state;
		auto& ref_configs = core.configs;
		auto& ref_world = core.world;
		auto& ref_window = core.window_manager.window;
	
		core.Timestep();
		
		core.UpdateConfigs();
		core.entities_manager.Update(ref_world);
		core.ECS_movement_system.Update(ref_world);
		core.ECS_camera_system.Update(ref_world, ref_world.render_state);

		scripting.Update(ref_world);

		core.input_system.Update(ref_engine_state, ref_world, ref_window, ref_configs);

		if(*POINT_engine_state.editor_mode)
		{
			T_editor.Update(core, ref_engine_state);
		}
		else
		{
			core.renderer.Predraw(ref_world);
			core.renderer.Draw(ref_world, ref_world.render_state, ref_window, ref_configs,std::nullopt, std::nullopt);
		}

		SDL_GL_SwapWindow(core.window_manager.window.SDLwindow);
	}
}

void Point::Quit()
{
	*POINT_engine_state.engine_quit = true;
}

void Point::Restart()
{
	Quit();
	Run();
}
