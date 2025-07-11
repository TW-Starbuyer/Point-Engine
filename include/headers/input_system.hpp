#pragma once

#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"
#include "window_manager.hpp"
#include "configs.hpp"

#include "../utils/u_components.hpp"

class InputSystem
{
	public:
		InputSystem();
		void Update(EngineState& engine_state, World& world, Window& window, RenderConfigs& configs);
};