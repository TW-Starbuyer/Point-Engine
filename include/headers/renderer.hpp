#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"
#include "window_manager.hpp"
#include "configs.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "../utils/u_components.hpp"
#include "../utils/u_tags.hpp"
#include "../utils/u_windows.hpp"

class Renderer
{
	public:
		Renderer();
		
		Framebuffer CreateFramebuffer(int width, int height);
		void ResizeFramebuffer(Framebuffer& fb, int width, int height);

		void BindFramebuffer(Framebuffer fbo);
		void UnbindFramebuffer();

		void Predraw(World& world);
		void Draw(World& world, RenderState& render_state, Window& window, RenderConfigs& configs, std::optional<int> width, std::optional<int> height);
		

		void SetViewport(float vp_width, float vp_height);	
};
