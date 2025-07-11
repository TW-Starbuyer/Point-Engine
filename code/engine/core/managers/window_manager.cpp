#include "window_manager.hpp"

WindowManager::WindowManager(std::string program_name, int width, int height)
{
		const char* title = program_name.c_str();

		window.SDLwindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
		if (window.SDLwindow == nullptr)
		{
			std::cerr << "ERROR W-1: Failed to initialize SDL window" << std::endl;
			exit(1);
		}

		std::cout << "SUCCESS W-1: SDL3 Window initialized" << std::endl;
	
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		window.GLContext = SDL_GL_CreateContext(window.SDLwindow);
		
		if (window.GLContext == nullptr)
		{
			std::cerr << "ERROR W-02: Failed to initialize OpenGL context" << std::endl;
			exit(1);
		}

		
		std::cout << "SUCCESS W-02: OpenGL Context initialized" << std::endl;

}